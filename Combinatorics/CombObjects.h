#ifndef COMB_OBJECTS_H_INCLUDED__
#define COMB_OBJECTS_H_INCLUDED__
#pragma once
#include "UINT32.h"

//����� ������������ P(n)
UINT32 Permutation(byte n);

//����� ����� B(n)
UINT32 BellNumber(byte n);

//����� ��������� C(m, n)
UINT32 Combination(byte m, byte n);

//����� ��������� ������� ���� S(m, n)
UINT32 StirlingNumberSecondKind(byte m, byte n);

//����� ���������� U(m, n)
UINT32 Placing(byte m, byte n);

//����� ���������� ��� ���������� A(m, n)
UINT32 PlacingWithoutRepeat(byte m, byte n);

#endif