#include "Power.h"

Power::Power() : Expression(PowerDef()) {}

Power::~Power() {
  delete mArgs[0];
  delete mArgs[1];
}

double Power::evaluate() const {
  return pow(mArgs[0]->evaluate(), mArgs[1]->evaluate());
}

void Power::pushArg(const Expression* expr) {
  if (mCurrArgIndex >= 0) {
    mArgs[mCurrArgIndex] = expr;
    mCurrArgIndex--;

  } else {
    throw "Too many arguments";
  }
}

Expression* Power::clone() const {
  return new Power(*this);
}