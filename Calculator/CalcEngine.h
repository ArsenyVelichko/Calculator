#pragma once

#include <stack>
#include <queue>
#include "Expression.h"

using namespace std;

class CalcEngine {
private:
  stack<Expression*> mProcessStk;
  queue<Expression*> mOutputStk;

  void shiftExpr();

public:
  CalcEngine();

  void pushExpr(Expression* expr);
  void openSubExpr();
  void closeSubExpr();
  Expression* popOutputExpr();
};