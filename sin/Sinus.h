#pragma once

#include <memory>
#include "ExpressionFactory.h"

#define DLLEXPORT __declspec(dllexport) 

struct SinusDef : ExpressionDef {
  SinusDef() {
    precedence = NUM_PRECEDENCE + 1;
    argNumber = 1;
    prefix = true;
  }
};

class Sinus : public Expression {
public:
  Sinus();
  ~Sinus();

  double evaluate() const override;
  void pushArg(const Expression* expr) override;
  Expression* clone() const override;

private:
  const Expression* mArg = nullptr;
};

extern "C" {
  DLLEXPORT void getExpressionInfo(ExpressionInfo* info) {
    info->prototype = new Sinus;
    info->name = "sin";
  }
}

