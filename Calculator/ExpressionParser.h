#pragma once

#include <vector>
#include "Expression.h"
#include "ExpressionFactory.h"

class ExpressionParser {
public:
  ExpressionParser(const ExpressionFactory* factory);
  ~ExpressionParser();

  Expression* parse(const string& str, const string& delimiter) const;

private:
  const ExpressionFactory* mFactory;

  vector<string> split(const string& str, const string& delimiter) const;
  Expression* parseTokens(const vector<string>& tokens) const;
};