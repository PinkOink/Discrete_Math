#ifndef UINT32_H_INCLUDED__
#define UINT32_H_INCLUDED__
#pragma once
#include <ostream>
#include <limits>

typedef unsigned uint32;
typedef unsigned char byte;

class UINT32 {
public:
  //constructors
  UINT32() = default;
  UINT32(const UINT32 &) = default; //copy-const
  UINT32(uint32);

  //destructor
  ~UINT32() = default; 

  //operations
  UINT32 operator + (const UINT32 &) const;
  UINT32 operator - (const UINT32 &) const;
  UINT32 operator * (const UINT32 &) const;
  UINT32 operator / (const UINT32 &) const;

  UINT32 & operator = (const UINT32 &);
  UINT32 & operator += (const UINT32 &);
  UINT32 & operator -= (const UINT32 &);
  UINT32 & operator *= (const UINT32 &);
  UINT32 & operator /= (const UINT32 &);

  bool operator < (const UINT32 &) const;
  bool operator > (const UINT32 &) const;
  bool operator <= (const UINT32 &) const;
  bool operator >= (const UINT32 &) const;
  bool operator == (const UINT32 &) const;

  friend std::ostream & operator << (std::ostream &, const UINT32 &);

private:
  uint32 value_;
};

void CheckUINT32();
const UINT32 MaxUINT32(std::numeric_limits<uint32>::max());

#endif