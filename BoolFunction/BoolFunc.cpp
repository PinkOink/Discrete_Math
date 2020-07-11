#include "BoolFunc.h"
#include "ErrorAnalysis.h"
#include <new>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

BoolFunc::BoolFunc() {
  n = 0;

  TV_size = 1;
  TV = new uint[TV_size];
  TV[0] = 0x0;

  PDNF_size = 0;
  PDNF = new uint[PDNF_size];

  PCNF_size = 1;
  PCNF = new uint[PCNF_size];
  PCNF[0] = 0x0;

  RDNF_size = 0;
  RDNF = new uint *[RDNF_size];

  ZP_size = 0;
  ZP = new uint[ZP_size];

  KM_lines = 1;
  KM_uints_in_line = 1;
  KM_coloumns_in_uint = 1;
  KM = new uint*[KM_lines];
  KM[0] = new uint[KM_uints_in_line];
  KM[0][0] = 0x0;
}

BoolFunc::BoolFunc(bool val) 
  :BoolFunc()
{
  if (val) {
    this->~BoolFunc();

    n = 0;

    TV_size = 1;
    TV = new uint[TV_size];
    TV[0] = 0x1;

    PDNF_size = 1;
    PDNF = new uint[PDNF_size];
    PDNF[0] = 0x0;

    PCNF_size = 0;
    PCNF = new uint[PCNF_size];

    RDNF_size = 1;
    RDNF = new uint *[RDNF_size];
    RDNF[0] = new uint[2];
    RDNF[0][0] = 0x0;
    RDNF[0][1] = 0x0;

    ZP_size = 1;
    ZP = new uint[ZP_size];
    ZP[0] = 0x0;

    KM_lines = 1;
    KM_uints_in_line = 1;
    KM_coloumns_in_uint = 1;
    KM = new uint*[KM_lines];
    KM[0] = new uint[KM_uints_in_line];
    KM[0][0] = 0x1;
  }
}

BoolFunc::BoolFunc(byte N, uint *vec, BoolFuncInitType type, byte M) {
  if (N >= 32)
    throw NoutOfRange;

  n = N;
  TV_size = (n <= 5) ? 1U : 1U << (n - 5);
  try {
    TV = new uint[TV_size];
  }
  catch (std::bad_alloc) {
    throw BadAlloc;
  }

  switch (type) {
  case TruthVectorType:
    for (size_t i = 0; i != TV_size; ++i)
      TV[i] = vec[i];

    ConvertTVtoPDNF();
    ConvertTVtoPCNF();
    ConvertTVtoRDNF();
    ConvertTVtoZP();
    ConvertTVtoKM();
    break;
  case PDNFtype:
    for (size_t i = 0; i != TV_size; ++i)
      TV[i] = vec[i];

    ConvertTVtoPDNF();
    ConvertTVtoPCNF();
    ConvertTVtoRDNF();
    ConvertTVtoZP();
    ConvertTVtoKM();
    break;
  case PCNFtype:
    PCNF_size = TV_size;
    PCNF = new uint[PCNF_size];

    for (size_t i = 0; i != TV_size; ++i)
      PCNF[i] = vec[i];

    if (n < 5)
      TV[0] = ~vec[0] & ((1u << (1U << n)) - 1);
    else
      for (size_t i = 0; i != TV_size; ++i)
        TV[i] = ~vec[i];

    ConvertTVtoPDNF();
    ConvertTVtoRDNF();
    ConvertTVtoZP();
    ConvertTVtoKM();
    break;
  case RDNFtype:
    RDNF_size = M;
    RDNF = new uint *[RDNF_size];

    for (size_t i = 0; i != 2 * RDNF_size; i += 2) {
      RDNF[i / 2] = new uint[2];
      RDNF[i / 2][0] = vec[i];
      RDNF[i / 2][1] = vec[i + 1];
    }

    for (uint x = 0; x != 1 << n; ++x)
      if (ValRDNF(x))
        TV[x / 32] |= 1 << (x % 32);
      else
        TV[x / 32] &= ~(1 << (x % 32));

    ConvertTVtoPDNF();
    ConvertTVtoPCNF();
    ConvertTVtoZP();
    ConvertTVtoKM();
    break;
  case ZhegalkinPolynomType:
    ZP_size = TV_size;
    ZP = new uint[ZP_size];

    for (size_t i = 0; i != ZP_size; ++i)
      ZP[i] = vec[i];

    for (uint x = 0; x != (1 << n); ++x)
      if (ValZP(x))
        TV[x / 32] |= 1 << (x % 32);
      else
        TV[x / 32] &= ~(1 << (x % 32));

    ConvertTVtoPDNF();
    ConvertTVtoPCNF();
    ConvertTVtoRDNF();
    ConvertTVtoKM();
    break;
  default:
    throw WrongBFtype;
  }
}

BoolFunc::BoolFunc(byte N, uint **vec, BoolFuncInitType type, byte M) {
  if (N >= 32)
    throw NoutOfRange;

  n = N;
  TV_size = (n <= 5) ? 1U : 1U << (n - 5);
  try {
    TV = new uint[TV_size];
  }
  catch (std::bad_alloc) {
    throw BadAlloc;
  }

  switch (type) {
  case KarnaughMapType:
    KM_lines = 1 << (n / 2);
    KM_uints_in_line = (n <= 5) ? 1 : (1 << (n / 2 + n % 2)) / 32;
    KM_coloumns_in_uint = (n <= 5) ? (1 << (n / 2 + n % 2)) : 32;

    KM = new uint*[KM_lines];
    for (size_t i = 0; i != KM_lines; ++i)
      KM[i] = new uint[KM_uints_in_line];

    for (size_t i = 0; i != KM_lines; ++i)
      for (size_t j = 0; j != KM_uints_in_line; ++j)
        KM[i][j] = vec[i][j];

    for (uint x = 0; x != 1 << n; ++x)
      if (ValKM(x))
        TV[x / 32] |= 1 << (x % 32);
      else
        TV[x / 32] &= ~(1 << (x % 32));

    ConvertTVtoPDNF();
    ConvertTVtoPCNF();
    ConvertTVtoRDNF();
    ConvertTVtoZP();
    break;
  default:
    throw WrongBFtype;
  }
}

std::ostream& operator<< (std::ostream &out, const BoolFunc &BF) {
  for (size_t i = 0; i != BF.TV_size; ++i)
    out << std::hex << BF.TV[i] << std::endl;
  out << std::endl;

  return out;
}

std::istream& operator>> (std::istream &in, BoolFunc &BF) {
  BF.~BoolFunc();
  int n;
  in >> n;
  BF.n = n;
  BF.TV_size = (BF.n <= 5) ? 1 : (1 << (BF.n - 5));

  BF.TV = new uint[BF.TV_size];

  in >> std::hex;
  for (size_t i = 0; i != BF.TV_size; ++i)
    in >> BF.TV[i];

  BF.ConvertTVtoKM();
  BF.ConvertTVtoPCNF();
  BF.ConvertTVtoPDNF();
  BF.ConvertTVtoRDNF();
  BF.ConvertTVtoZP();

  return in;
}

void BoolFunc::PrintRDNF(std::ostream &out) {
  for (size_t i = 0; i != RDNF_size; ++i)
    out << std::hex << RDNF[i][0] << ' ' << RDNF[i][1] << std::endl;
  out << std::endl;
}

void RDNFfromStream(std::istream &in, BoolFunc &BF) {
  BF.~BoolFunc();

  in >> BF.n;
  BF.n -= '0';
  in >> BF.RDNF_size;

  BF.TV_size = (BF.n <= 5) ? 1U : 1U << (BF.n - 5);
  try {
    BF.TV = new uint[BF.TV_size];
  }
  catch (std::bad_alloc) {
    throw BadAlloc;
  }

  BF.RDNF = new uint *[BF.RDNF_size];

  for (size_t i = 0; i != 2 * BF.RDNF_size; i += 2) {
    BF.RDNF[i / 2] = new uint[2];
    in >> BF.RDNF[i / 2][0];
    in >> BF.RDNF[i / 2][1];
  }

  for (uint x = 0; x != 1 << BF.n; ++x)
    if (BF.ValRDNF(x))
      BF.TV[x / 32] |= 1 << (x % 32);
    else
      BF.TV[x / 32] &= ~(1 << (x % 32));

  BF.ConvertTVtoPDNF();
  BF.ConvertTVtoPCNF();
  BF.ConvertTVtoZP();
  BF.ConvertTVtoKM();
}

void BoolFunc::PrintZP(std::ostream &out) {
  for (size_t i = 0; i != ZP_size; ++i)
    out << std::hex << ZP[i] << std::endl;
  out << std::endl;
}

void ZPfromStream(std::istream &in, BoolFunc &BF) {
  BF.~BoolFunc();

  in >> BF.n;
  BF.n -= '0';
  BF.TV_size = (BF.n <= 5) ? 1U : 1U << (BF.n - 5);
  try {
    BF.TV = new uint[BF.TV_size];
  }
  catch (std::bad_alloc) {
    throw BadAlloc;
  }

  BF.ZP_size = BF.TV_size;
  BF.ZP = new uint[BF.ZP_size];

  for (size_t i = 0; i != BF.ZP_size; ++i)
    in >> BF.ZP[i];

  for (uint x = 0; x != (1 << BF.n); ++x)
    if (BF.ValZP(x))
      BF.TV[x / 32] |= 1 << (x % 32);
    else
      BF.TV[x / 32] &= ~(1 << (x % 32));

  BF.ConvertTVtoPDNF();
  BF.ConvertTVtoPCNF();
  BF.ConvertTVtoRDNF();
  BF.ConvertTVtoKM();
}

void BoolFunc::PrintKM(std::ostream &out) {
  for (size_t i = 0; i != KM_lines; ++i) {
    for (size_t j = 0; j != KM_uints_in_line; ++j)
      out << std::hex << KM[i][j] << ' ';
    out << std::endl;
  }
}

void KMfromStream(std::istream &in, BoolFunc &BF) {
  BF.~BoolFunc();

  in >> BF.n;
  BF.n -= '0';
  BF.TV_size = (BF.n <= 5) ? 1U : 1U << (BF.n - 5);
  try {
    BF.TV = new uint[BF.TV_size];
  }
  catch (std::bad_alloc) {
    throw BadAlloc;
  }
  BF.KM_lines = 1 << (BF.n / 2);
  BF.KM_uints_in_line = (BF.n <= 5) ? 1 : (1 << (BF.n / 2 + BF.n % 2)) / 32;
  BF.KM_coloumns_in_uint = (BF.n <= 5) ? (1 << (BF.n / 2 + BF.n % 2)) : 32;

  BF.KM = new uint*[BF.KM_lines];
  for (size_t i = 0; i != BF.KM_lines; ++i)
    BF.KM[i] = new uint[BF.KM_uints_in_line];

  for (size_t i = 0; i != BF.KM_lines; ++i)
    for (size_t j = 0; j != BF.KM_uints_in_line; ++j)
      in >> BF.KM[i][j];

  for (uint x = 0; x != 1 << BF.n; ++x)
    if (BF.ValKM(x))
      BF.TV[x / 32] |= 1 << (x % 32);
    else
      BF.TV[x / 32] &= ~(1 << (x % 32));

  BF.ConvertTVtoPDNF();
  BF.ConvertTVtoPCNF();
  BF.ConvertTVtoRDNF();
  BF.ConvertTVtoZP();
}

void BoolFunc::ConvertTVtoPDNF() {
  PDNF_size = TV_size;
  PDNF = new uint[PDNF_size];

  for (size_t i = 0; i != PDNF_size; ++i)
    PDNF[i] = TV[i];
}

void BoolFunc::ConvertTVtoPCNF() {
  PCNF_size = TV_size;
  PCNF = new uint[PCNF_size];

  if (n < 5)
    PCNF[0] = ~TV[0] & ((1U << (1U << n)) - 1);
  else
    for (size_t i = 0; i != PCNF_size; ++i)
      PCNF[i] = ~TV[i];
}

int NumberOfSetBits(uint x) {
  int n = 0;
  while (x) {
    n += x & 1u;
    x >>= +1;
  }
  return n;
}

bool ExistMaskPair(std::vector<uint> & inV, std::vector<uint> & invV, uint in, uint inv)
{
  auto iterInv = std::find(invV.begin(), invV.end(), inv);

  while (iterInv != invV.end())
  {
    int ind = iterInv - invV.begin();
    if (inV[ind] == in)
      return true;
    iterInv = std::find(iterInv + 1, invV.end(), inv);
  }

  return false;
}

void BoolFunc::ConvertTVtoRDNF() {
  std::vector<uint> in_buf;
  std::vector<uint> inv_buf;

  for (uint x = 0; x != (1 << n) - 1; ++x)
    if (ValTV(x)) {
      in_buf.push_back((1 << n) - 1);
      inv_buf.push_back(x);
    }

  std::vector<uint> in_used;
  std::vector<uint> inv_used;

  std::vector<uint> in_res;
  std::vector<uint> inv_res;

  for (size_t i = 0; i != inv_buf.size(); ++i) {
    size_t tempsize = in_buf.size();

    for (size_t j = i + 1; j != inv_buf.size(); ++j) {
      if ((in_buf[j] == in_buf[i]) && (NumberOfSetBits(inv_buf[j] ^ inv_buf[i]) == 1) && (NumberOfSetBits(in_buf[j]) != 1)) {
        in_buf.push_back(in_buf[j] ^ (inv_buf[j] ^ inv_buf[i]));
        inv_buf.push_back((in_buf[j] ^ (inv_buf[j] ^ inv_buf[i])) & inv_buf[j]);

        in_used.push_back(in_buf[i]);
        in_used.push_back(in_buf[j]);
        inv_used.push_back(inv_buf[i]);
        inv_used.push_back(inv_buf[j]);
      }
    }

    if (tempsize == in_buf.size() && !ExistMaskPair(in_used, inv_used, in_buf[i], inv_buf[i]) && !ExistMaskPair(in_res, inv_res, in_buf[i], inv_buf[i])) {
      in_res.push_back(in_buf[i]);
      inv_res.push_back(inv_buf[i]);
    }
  }

  RDNF_size = in_res.size();
  RDNF = new uint *[RDNF_size];

  for (size_t i = 0; i != RDNF_size; ++i) {
    RDNF[i] = new uint[2];
    RDNF[i][0] = in_res[i];
    RDNF[i][1] = inv_res[i];
  }
}

void BoolFunc::ConvertTVtoZP() {
  ZP_size = TV_size;
  ZP = new uint[ZP_size];

  for (size_t i = 0; i < TV_size; ++i)
    ZP[i] = TV[i];

  if (n < 5)
    for (uint i = 0; i != (1 << n); ++i)
      ZP[0] ^= (ZP[0] << 1) & ((1 << (1 << n)) - 1 - ((1 << (i + 1)) - 1));
  else
    for (uint i = 0; i != (1 << n); ++i) {
      size_t j = ZP_size - 1;
      for (; j != i / 32; --j)
        ZP[j] ^= (ZP[j] << 1) + (ZP[j - 1] >> 31);
      if ((i + 1) % 32)
        ZP[j] ^= (ZP[j] << 1) & (~((1 << ((i % 32) + 1)) - 1));
    }
}

uint Grey(uint Ind) { //левый зеркальный код Грея
  return Ind ^ Ind >> 1;
}

uint Grey2Int(uint G) {
  uint d, m, b;												// Most Significant Bit xOR-Accumulator

  for (m = 1U << 31; ~(G & m) & m; m >>= 1);							// Most Significant Bit of G
  for (d = b = 0; m; b ^= G & m, d ^= b, b >>= 1, m >>= 1);			//!!! C/C++ 

  return d;															// Index of G 
}

void BoolFunc::ConvertTVtoKM() {
  KM_lines = 1 << (n / 2);
  KM_uints_in_line = (n <= 5) ? 1 : (1 << (n / 2 + n % 2)) / 32 + 1;
  KM_coloumns_in_uint = (n <= 5) ? (1 << (n / 2 + n % 2)) : 32;

  KM = new uint*[KM_lines];
  for (size_t i = 0; i != KM_lines; ++i) {
    KM[i] = new uint[KM_uints_in_line];

    for (size_t j = 0; j != KM_uints_in_line; ++j)
      KM[i][j] = 0x0;
  }

  for (uint x = 0; x != 1 << n; ++x) {
    size_t line = Grey2Int(x & ((1 << (n / 2)) - 1));
    size_t coloumn = Grey2Int(x >> (n / 2));
    
    if (ValTV(x))
      KM[line][coloumn / 32] ^= 1 << (coloumn % 32);
  }
}

bool BoolFunc::CheckRight() {
  for (uint x = 0; x != (1 << n); ++x) {
    bool right = ValTV(x);
    if (ValPDNF(x) != right || ValPCNF(x) != right || ValRDNF(x) != right || ValZP(x) != right || ValKM(x) != right)
      return false;
  }
  return true;
}

bool BoolFunc::CheckSelfDuality() {
  for (uint x = 0; x != 1 << n; ++x) {
    if (ValTV(x) != !ValTV(~x & ((1 << n) - 1)))
      return false;
  }
  return true;
}

bool BoolFunc::Check0Preserving() {
  return ValTV(0) == 0;
}

bool BoolFunc::Check1Preserving() {
  return ValTV((1 << n) - 1);
}

bool BoolFunc::CheckMonotone() {
  for (uint x = 0; x != 1 << n; ++x)
    if (ValTV(x))
      for (uint i = 0, y = x | (1 << i); i != n; y |= 1 << ++i)
        if (!ValTV(y))
          return false;
  return true;
}

bool BoolFunc::CheckLinearity() {
  for (size_t i = 0; i != ZP_size; ++i)
    for (size_t j = 0; j != 32; ++j)
      if (((ZP[i] >> j) & 1) != 0 && NumberOfSetBits(j + i * 32) != 1)
        return false;
  return true;
}

bool BoolFunc::CheckSymmetry() {
  bool *buf = new bool[n];
  for (uint x = (1 << n) - 1, i = n; i != 0; --i, x >>= 1)
    buf[i - 1] = ValTV(x);

  for (uint x = 0; x != 1 << n; ++x)
    if (buf[NumberOfSetBits(x) - 1] != ValTV(x))
      return false;
  return true;
}

bool BoolFunc::ValTV(uint x) {
  if (x >> n)
    throw XoutOfRange;

  uint d = 0x0;
  for (byte i = 0; i != n; ++i)
    d = d * 2 + ((x >> (n - i - 1)) & 1U);
  return (TV[d / 32] >> (d % 32)) & 1U;
}

bool BoolFunc::ValPDNF(uint x) {
  if (x >> n)
    throw XoutOfRange;

  uint d = 0x0;
  for (byte i = 0; i != n; ++i)
    d = d * 2 + ((x >> (n - i - 1)) & 1U);
  return (PDNF[d / 32] >> (d % 32)) & 1U;
}

bool BoolFunc::ValPCNF(uint x) {
  if (x >> n)
    throw XoutOfRange;

  uint d = 0x0;
  for (byte i = 0; i != n; ++i)
    d = d * 2 + ((x >> (n - i - 1)) & 1U);
  return !((PCNF[d / 32] >> (d % 32)) & 1U);
}

bool BoolFunc::ValRDNF(uint x) {
  if (x >> n)
    throw XoutOfRange;

  for (size_t i = 0; i != RDNF_size; ++i) {
    if ((RDNF[i][0] & RDNF[i][1]) == (RDNF[i][0] & x))
      return true;
  }
  return false;
}

bool BoolFunc::ValZP(uint x) {
  if (x >> n)
    throw XoutOfRange;

  uint ZPval = 0;
  for (uint buf = 0; buf != 1 << n; ++buf)
    if ((ZP[buf / 32] >> (buf % 32)) & 1u)
      ZPval ^= ((buf & x) == buf);

  return !!ZPval;
}

bool BoolFunc::ValKM(uint x) {
  size_t line = Grey2Int(x & ((1 << (n / 2)) - 1));
  size_t coloumn = Grey2Int(x >> (n / 2));

  return ((KM[line][coloumn / 32] >> (coloumn % 32)) & 1U) == 1U;
}

BoolFunc::~BoolFunc() {
  delete[] TV;

  delete[] PDNF;

  delete[] PCNF;

  for (size_t i = 0; i != RDNF_size; ++i)
    delete[] RDNF[i];
  delete[] RDNF;

  delete[] ZP;

  for (size_t i = 0; i != KM_lines; ++i)
    delete[] KM[i];
  delete[] KM;
}