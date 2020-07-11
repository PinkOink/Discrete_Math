#include "ErrorAnalysis.h"
#include <iostream>

ErrorAnalysis::ErrorAnalysis(ErrorTypes type)
  :type_(type)
{}

void PrintErrorMessage(std::ostream &ostr, const ErrorAnalysis &err) {
  switch (err.type_)
  {
  case NoutOfRange:
    ostr << "n is out of range" << std::endl;
    break;
  case BadAlloc:
    ostr << "Bad alloc" << std::endl;
    break;
  case WrongBFtype:
    ostr << "Wrong Bool Function Initialization Type" << std::endl;
    break;
  case XoutOfRange:
    ostr << "x is out of range" << std::endl;
    break;
  default:
    break;
  }
}