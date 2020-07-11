#ifndef COMB_OBJECTS_H_INCLUDED__
#define COMB_OBJECTS_H_INCLUDED__
#pragma once
#include "UINT32.h"

//Число перестановок P(n)
UINT32 Permutation(byte n);

//Число Белла B(n)
UINT32 BellNumber(byte n);

//Число сочетаний C(m, n)
UINT32 Combination(byte m, byte n);

//Число Стирлинга второго рода S(m, n)
UINT32 StirlingNumberSecondKind(byte m, byte n);

//Число размещений U(m, n)
UINT32 Placing(byte m, byte n);

//Число размещений без повторений A(m, n)
UINT32 PlacingWithoutRepeat(byte m, byte n);

#endif