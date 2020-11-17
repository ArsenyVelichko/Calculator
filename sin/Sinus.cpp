#include "Sinus.h"
#include <math.h>

Sinus::Sinus() : Expression(SinusDef()) {}

Sinus::~Sinus() {
  delete mArg;
}

double Sinus::evaluate() const {
  return sin(mArg->evaluate());
}

void Sinus::pushArg(const Expression* expr) {
  if (!mArg) {
    mArg = expr;

  } else {
    throw "Too many arguments";
  }
}

Expression* Sinus::clone() const {
  return new Sinus(*this);
}