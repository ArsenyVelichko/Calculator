#pragma once

#include "Expression.h"

struct BinaryDef : ExpressionDef {
  BinaryDef() {
    argNumber = 2;
  }
};

class BinaryOperation : public Expression {
public:
  BinaryOperation(const BinaryDef& def);

  void pushArg(const Expression* expr) override;

  ~BinaryOperation();

protected:
  const Expression* mArgs[2] = {0};

private:
  int mCurrArgIndex = 0;
};

struct AdditionDef : BinaryDef {
  AdditionDef() {
    precedence = Precedence::ADD_PRECEDENCE;
  }
};

class Addition : public BinaryOperation {
public:
  Addition();

  double evaluate() const override;
  Expression* clone() const override;
};

class Subtraction : public BinaryOperation {
public:
  Subtraction();

  double evaluate() const override;
  Expression* clone() const override;
};

struct MultiplicationDef : BinaryDef {
  MultiplicationDef() {
    precedence = Precedence::MUL_PRECEDENCE;
  }
};

class Multiplication : public BinaryOperation {
public:
  Multiplication();

  double evaluate() const override;
  Expression* clone() const override;
};

class Division : public BinaryOperation {
public:
  Division();

  double evaluate() const override;
  Expression* clone() const override;
};
