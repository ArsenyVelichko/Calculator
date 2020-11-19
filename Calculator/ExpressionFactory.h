#pragma once

#include <windows.h>
#include <vector>
#include <map>
#include <string>
#include "Expression.h"

using namespace std;

struct ExpressionInfo {
  string name;
  Expression* prototype;
};

class ExpressionFactory {
public:
  ExpressionFactory();
  ~ExpressionFactory();

  Expression* getExpression(const string& grammarToken) const;
  void registerExpr(const string& grammarToken, const Expression* prototype);
  void registerExpr(const wchar_t* dllName);

  static ExpressionFactory* createFromDll(const string& directory);

private:
  map<const string, const Expression*> mRegister;
  vector<HMODULE> mAdditionalDll;
};