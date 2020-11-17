#pragma once

#include "Expression.h"

struct NumberDef : ExpressionDef {
  NumberDef() {
    precedence = NUM_PRECEDENCE;
    argNumber = 0;
  }

  double value;
};

class Number : public Expression {
public:
  Number(double value);

  void pushArg(const Expression* expr) override {}
  double evaluate() const override;
  Expression* clone() const override;

private:
  double m_value;
};