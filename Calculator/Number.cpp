#include "Number.h"

Number::Number(double value) : m_value(value), Expression(NumberDef()) {}

double Number::evaluate() const {
  return m_value;
}

Expression* Number::clone() const {
  return new Number(*this);
}