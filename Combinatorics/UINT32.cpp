#include "UINT32.h"
#include "ErrorAnalysis.h"
#include <iostream>

UINT32::UINT32(uint32 a)
  :value_(a)
{}
UINT32::UINT32()
  :value_(0)
{}
UINT32::UINT32(const UINT32 &a)
  :value_(a.value_)
{}

UINT32 UINT32::operator + (const UINT32 &a) const {
  if (MaxUINT32 - a < *this)
    throw ADD_OVERFLOW;
  return UINT32(value_ + a.value_);
}
UINT32 UINT32::operator - (const UINT32 &a) const {
  if (*this < a)
    throw SUB_OVERFLOW;
  return UINT32(value_ - a.value_);
}
UINT32 UINT32::operator * (const UINT32 &a) const {
  if ((double)MaxUINT32.value_ / a.value_ < value_)
    throw MUL_OVERFLOW;
  return UINT32(value_ * a.value_);
}
UINT32 UINT32::operator / (const UINT32 &a) const {
  if (a == UINT32(0u))
    throw DIV_BY_ZERO;
  return UINT32(value_ / a.value_);
}

UINT32 & UINT32::operator = (const UINT32 &a) {
  value_ = a.value_;
  return *this;
}
UINT32 & UINT32::operator += (const UINT32 &a) {
  if (MaxUINT32 - a < *this)
    throw ADD_OVERFLOW;
  value_ += a.value_;
  return *this;
}
UINT32 & UINT32::operator -= (const UINT32 &a) {
  if (*this < a)
    throw SUB_OVERFLOW;
  value_ -= a.value_;
  return *this;
}
UINT32 & UINT32::operator *= (const UINT32 &a) {
  if ((double)MaxUINT32.value_ / a.value_ < value_)
    throw MUL_OVERFLOW;
  value_ *= a.value_;
  return *this;
}
UINT32 & UINT32::operator /= (const UINT32 &a) {
  if (a == UINT32(0u))
    throw DIV_BY_ZERO;
  value_ /= a.value_;
  return *this;
}

bool UINT32::operator < (const UINT32 &a) const {
  return (value_ < a.value_) ? true : false;
}
bool UINT32::operator > (const UINT32 &a) const {
  return (value_ > a.value_) ? true : false;
}
bool UINT32::operator <= (const UINT32 &a) const {
  return (value_ <= a.value_) ? true : false;
}
bool UINT32::operator >= (const UINT32 &a) const {
  return (value_ >= a.value_) ? true : false;
}
bool UINT32::operator == (const UINT32 &a) const {
  return (value_ == a.value_) ? true : false;
}

std::ostream & operator << (std::ostream &stream, const UINT32 &a) {
  stream << a.value_;
  return stream;
}

using std::cout;
using std::endl;

void CheckUINT32() {
  UINT32 hMaxUINT32(0x7FFFFFFFU);
  UINT32 TwoPow16(0x1UL << 16);
  UINT32 TwoPow31(0x1UL << 31);
  UINT32 rMaxUINT32(0xFFFFU);
  UINT32 One(1);
  UINT32 Twopow16(rMaxUINT32 + One);

  cout << "Checking class UINT32 operators:" << endl << endl;
  cout << "MaxUINT32 = " << MaxUINT32 << endl;
  cout << "TwoPow31 = " << TwoPow31 << endl;
  cout << "hMaxUINT32 = " << hMaxUINT32 << endl;
  cout << "rMaxUINT32 = " << rMaxUINT32 << endl;
  cout << "TwoPow16 = " << TwoPow16 << endl;
  cout << "Twopow16 = " << Twopow16 << endl << endl;

  // check `+` overflow: 
  cout << "(hMaxUINT32 + TwoPow31) = ";
  try {
    cout << (hMaxUINT32 + TwoPow31) << endl;
  }
  catch (ErrorTypes type) {
    PrintErrorMessage(std::cout, ErrorAnalysis(type));
  } // hMaxUINT32 + hMaxUINT32

  cout << "(MaxUINT32 + One) = ";
  try {
    cout << (MaxUINT32 + One) << endl;
  }
  catch (ErrorTypes type) {
    PrintErrorMessage(std::cout, ErrorAnalysis(type));
  } // MaxUINT32 + One

    // check `-` overflow: 
  cout << "(hMaxUINT32 - hMaxUINT32) = ";
  try {
    cout << (hMaxUINT32 - hMaxUINT32) << endl;
  }
  catch (ErrorTypes type) {
    PrintErrorMessage(std::cout, ErrorAnalysis(type));
  } // hMaxUINT32 - hMaxUINT32

  cout << "(rMaxUINT32 - TwoPow16) = ";
  try {
    cout << (rMaxUINT32 - TwoPow16) << endl;
  }
  catch (ErrorTypes type) {
    PrintErrorMessage(std::cout, ErrorAnalysis(type));
  } // rMaxUINT32 - TwoPow16

    // check `*` overflow: 
  cout << "(rMaxUINT32 * (TwoPow16 + One)) = ";
  try {
    cout << (rMaxUINT32 * (TwoPow16 + One)) << endl;
  }
  catch (ErrorTypes type) {
    PrintErrorMessage(std::cout, ErrorAnalysis(type));
  } // rMaxUINT32 * (TwoPow16 + One)

  cout << "(TwoPow16 * Twopow16) = ";
  try {
    cout << (TwoPow16 * Twopow16) << endl;
  }
  catch (ErrorTypes type) {
    PrintErrorMessage(std::cout, ErrorAnalysis(type));
  } // TwoPow16 * Twopow16
  cout << endl;
} // CheckUINT32() 