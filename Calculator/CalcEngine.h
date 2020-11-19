#pragma once

#include <stack>
#include "Expression.h"

using namespace std;

class CalcEngine {
private:
  stack<Expression*> mProcessStk;
  stack<Expression*> mOutputStk;

  void shiftExpr();

public:
  CalcEngine();
  ~CalcEngine();

  void pushExpr(Expression* expr);
  void openSubExpr();
  void closeSubExpr();
  Expression* popOutputExpr();
};