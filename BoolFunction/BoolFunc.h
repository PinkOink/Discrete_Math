#ifndef BOOL_FUNC_H_INCLUDED__
#define BOOL_FUNC_H_INCLUDED__
#pragma once
#include <iostream>

typedef unsigned char byte;
typedef unsigned int uint;
typedef uint *TruthVector_t;
typedef uint *PDNF_t;
typedef uint *PCNF_t;
typedef uint **RDNF_t;
typedef uint *ZhegalkinPolynom_t;
typedef uint **KarnaughMap_t;
typedef enum { TruthVectorType, PDNFtype, PCNFtype, RDNFtype, ZhegalkinPolynomType, KarnaughMapType} BoolFuncInitType;

class BoolFunc {
private:
  byte n;

  TruthVector_t TV;
  size_t TV_size;

  PDNF_t PDNF;
  size_t PDNF_size;

  PCNF_t PCNF;
  size_t PCNF_size;

  RDNF_t RDNF;
  size_t RDNF_size;

  ZhegalkinPolynom_t ZP;
  size_t ZP_size;

  KarnaughMap_t KM;
  size_t KM_lines;
  size_t KM_uints_in_line;
  size_t KM_coloumns_in_uint;

  void ConvertTVtoPDNF();
  void ConvertTVtoPCNF();
  void ConvertTVtoRDNF();
  void ConvertTVtoZP();
  void ConvertTVtoKM();

public:
  BoolFunc();
  BoolFunc(bool val);
  BoolFunc(byte N, uint *vec, BoolFuncInitType type = TruthVectorType, byte M = 0);
  BoolFunc(byte N, uint **vec, BoolFuncInitType type = KarnaughMapType, byte M = 0);

  friend std::ostream& operator<< (std::ostream &out, const BoolFunc &BF);
  friend std::istream& operator>> (std::istream &in, BoolFunc &BF);
  void PrintRDNF(std::ostream &out);
  friend void RDNFfromStream(std::istream &in, BoolFunc &BF);
  void PrintZP(std::ostream &out);
  friend void ZPfromStream(std::istream &in, BoolFunc &BF);
  void PrintKM(std::ostream &out);
  friend void KMfromStream(std::istream &in, BoolFunc &BF);

  bool CheckRight();
  bool CheckSelfDuality();
  bool Check0Preserving();
  bool Check1Preserving();
  bool CheckMonotone();
  bool CheckLinearity();
  bool CheckSymmetry();

  bool ValTV(uint x);
  bool ValPDNF(uint x);
  bool ValPCNF(uint x);
  bool ValRDNF(uint x);
  bool ValZP(uint x);
  bool ValKM(uint x);

  ~BoolFunc();
};

#endif