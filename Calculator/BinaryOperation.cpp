#include "BinaryOperation.h"

BinaryOperation::BinaryOperation(const BinaryDef& def)
  : Expression(def) {}

void BinaryOperation::pushArg(const Expression* expr) {
  if (mCurrArgIndex < 2) {
    mArgs[mCurrArgIndex] = expr;
    mCurrArgIndex++;

  } else {
    throw "Too many arguments";
  }
}

BinaryOperation::~BinaryOperation() {
  delete mArgs[0];
  delete mArgs[1];
}

Addition::Addition() : BinaryOperation(AdditionDef()) {}

double Addition::evaluate() const {
  return mArgs[0]->evaluate() + mArgs[1]->evaluate();
}

Expression* Addition::clone() const {
  return new Addition(*this);
}

Subtraction::Subtraction() : BinaryOperation(AdditionDef()) {}

double Subtraction::evaluate() const {
  return mArgs[0]->evaluate() - mArgs[1]->evaluate();
}

Expression* Subtraction::clone() const {
  return new Subtraction(*this);
}

Multiplication::Multiplication() : BinaryOperation(MultiplicationDef()) {}

double Multiplication::evaluate() const {
  return mArgs[0]->evaluate() * mArgs[1]->evaluate();
}

Expression* Multiplication::clone() const {
  return new Multiplication(*this);
}

Division::Division() : BinaryOperation(MultiplicationDef()) {}

double Division::evaluate() const {
  return mArgs[0]->evaluate() / mArgs[1]->evaluate();
}

Expression* Division::clone() const {
  return new Division(*this);
}