#ifndef ERROR_ANALYSIS_H_INCLUDED__
#define ERROR_ANALYSIS_H_INCLUDED__
#pragma once
#include <ostream>

enum ErrorTypes {
  ADD_OVERFLOW, SUB_OVERFLOW, MUL_OVERFLOW, DIV_BY_ZERO
};

class ErrorAnalysis {
public:
  ErrorAnalysis(ErrorTypes);
//  ErrorAnalysis() = delete;
//  ~ErrorAnalysis() = default;

  friend void PrintErrorMessage(std::ostream &, const ErrorAnalysis &);

private:
  ErrorTypes type_;
};

#endif