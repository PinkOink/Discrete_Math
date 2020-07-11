#ifndef ERROR_ANALYSIS_H_INCLUDED__
#define ERROR_ANALYSIS_H_INCLUDED__
#pragma once
#include <iostream>

enum ErrorTypes {
  NoutOfRange, BadAlloc, WrongBFtype, XoutOfRange
};

class ErrorAnalysis {
public:
  ErrorAnalysis(ErrorTypes);
  ErrorAnalysis() = delete;
  ~ErrorAnalysis() = default;

  friend void PrintErrorMessage(std::ostream &, const ErrorAnalysis &);

private:
  ErrorTypes type_;
};

#endif