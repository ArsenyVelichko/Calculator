#pragma once

#include "ExpressionFactory.h"

#define DLLEXPORT __declspec(dllexport) 

struct PowerDef : ExpressionDef {
  PowerDef() {
    precedence = MUL_PRECEDENCE + 1;
    argNumber = 2;
    rightAssociative = true;
  }
};

class Power : public Expression {
public:
  Power();
  ~Power();

  double evaluate() const override;
  void pushArg(const Expression* expr) override;
  Expression* clone() const override;

private:
  const Expression* mArgs[2] = {0};
  int mCurrArgIndex = 1;
};

extern "C" {
  DLLEXPORT void getExpressionInfo(ExpressionInfo& info) {
    info.prototype = new Power;
    info.name = "^";
  }
}