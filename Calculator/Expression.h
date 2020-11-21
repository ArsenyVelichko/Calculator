#pragma once

enum Precedence {
  NUM_PRECEDENCE = 0x0000,
  ADD_PRECEDENCE = 0x1000,
  MUL_PRECEDENCE = 0x2000,
};

enum class Notation {
  INFIX,
  PREFIX,
  POSTFIX,
};

enum class Associativity {
  LEFT_ASSOCIATIVE,
  RIGHT_ASSOCIATIVE,
};

struct ExpressionDef {
  ExpressionDef() {
    associativity = Associativity::LEFT_ASSOCIATIVE;
    notation = Notation::INFIX;
  }

  size_t precedence;
  size_t argNumber;
  Associativity associativity;
  Notation notation;
};

class Expression {
public:
  Expression(const ExpressionDef& def);
  virtual ~Expression() {}

  virtual double evaluate() const = 0;
  virtual void pushArg(const Expression* expr) = 0;
  virtual Expression* clone() const = 0;

  size_t mPrecendence;
  size_t mArgNumber;
  Associativity mAssociativity;
  Notation mNotation;
};

inline Expression::Expression(const ExpressionDef& def)
  : mPrecendence(def.precedence),
    mArgNumber(def.argNumber),
    mAssociativity(def.associativity),
    mNotation(def.notation) {}