#pragma once

#include <memory>
#include "ExpressionFactory.h"

#define DLLEXPORT __declspec(dllexport) 

struct SinusDef : ExpressionDef {
  SinusDef() {
    precedence = MUL_PRECEDENCE + 2;
    argNumber = 1;
    notation = Notation::PREFIX;
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
  DLLEXPORT void getExpressionInfo(ExpressionInfo& info) {
    info.prototype = new Sinus;
    info.name = "sin";
  }
}

