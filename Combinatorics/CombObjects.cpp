#include "CombObjects.h"
#include "UINT32.h"
#include <iostream>

UINT32 Permutation(byte n) {
  UINT32 P(1);
  for (byte i = 2; i <= n; ++i)
    P *= UINT32(i);
  return P;
}

UINT32 BellNumber(byte n) {
  if (n == 0)
    return UINT32(1);

  UINT32 *A = new UINT32[n];
  A[0] = UINT32(1);
  for (byte k = 1; k != n; ++k) {
    UINT32 buf = A[0];
    A[0] = A[k - 1];
    for (byte i = 1; i != k + 1; ++i) {
      UINT32 buf2 = A[i];
      A[i] = A[i - 1] + buf;
      buf = buf2;
    }
  }
  UINT32 Abuf = A[n - 1];
  delete[] A;
  return Abuf;
}

UINT32 Combination(byte m, byte n) {
  if (n > m)
    return UINT32(0);

  //if (n > m - n) n = m - n;
  n = m < int(n)+n ? m-n : n;

  UINT32 *A = new UINT32[n + 1];
  for (byte i = 0; i != n + 1; ++i)
    A[i] = UINT32(1);

  for (byte i = 0; i != m - n; ++i)
    for (byte j = 1; j != n + 1; ++j)
      A[j] = A[j] + A[j - 1];

  UINT32 Abuf = A[n];
  delete[] A;
  return Abuf;
}

UINT32 StirlingNumberSecondKind(byte m, byte n) {
  //if (n == 0)    return UINT32(0);
  if (n > m)    return UINT32(0);
  if (n ==0 )   return UINT32(1);

  byte d = (m - n + 1 < n) ? (m - n + 1) : n;
  byte L = (m - n + 1 > n) ? (m - n + 1) : n;
  UINT32 *A = new UINT32[d];
  for (byte i = 0; i != d; ++i)
    A[i] = UINT32(1);
  if (d == n)
    for (byte i = 1; i != L; ++i)
      for (byte j = 1; j != d; ++j)
        A[j] = A[j - 1] + A[j] * UINT32(j + 1);
  else
    for (byte i = 1; i != L; ++i)
      for (byte j = 1; j != d; ++j)
        A[j] = A[j] + A[j - 1] * UINT32(i + 1);
  UINT32 Abuf = A[d - 1];
  delete[] A;
  return Abuf;
}

UINT32 Placing(byte m, byte n) {
  UINT32 U(1);
  UINT32 M(m);
  while (n) {
    if (n & 1) {
      U *= M;
      --n;
    }
    else {
      M *= M;
      n >>= 1;
    }
  }
  return U;
}

UINT32 PlacingWithoutRepeat(byte m, byte n) {
  if (n > m)
    return UINT32(0);

  UINT32 A(1);
  for (byte i = m - n + 1; i <= m; ++i)
    A *= i;
  return A;
}