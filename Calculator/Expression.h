#pragma once

enum Precedence {
  NUM_PRECEDENCE = 0x0000,
  ADD_PRECEDENCE = 0x1000,
  MUL_PRECEDENCE = 0x2000,
};

struct ExpressionDef {
  ExpressionDef() {
    rightAssociative = false;
    prefix = false;
  }

  size_t precedence;
  size_t argNumber;
  bool rightAssociative;
  bool prefix;
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
  bool mRightAssociative;
  bool mPrefix;
};

inline Expression::Expression(const ExpressionDef& def)
  : mPrecendence(def.precedence),
    mArgNumber(def.argNumber),
    mRightAssociative(def.rightAssociative),
    mPrefix(def.prefix) {}