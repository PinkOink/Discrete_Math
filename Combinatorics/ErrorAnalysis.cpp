#include "ErrorAnalysis.h"
#include <iostream>

ErrorAnalysis::ErrorAnalysis(ErrorTypes type)
  :type_(type)
{}

void PrintErrorMessage(std::ostream &ostr, const ErrorAnalysis &err) {
  switch (err.type_)
  {
  case ADD_OVERFLOW:
    ostr << "Addition overflow" << std::endl;
    break;
  case SUB_OVERFLOW:
    ostr << "Subtraction overflow" << std::endl;
    break;
  case MUL_OVERFLOW:
    ostr << "Multiply overflow" << std::endl;
    break;
  case DIV_BY_ZERO:
    ostr << "Divide by zero error" << std::endl;
    break;
  default:
    break;
  }
}