#include "CalcEngine.h"
#include <assert.h>

CalcEngine::CalcEngine() {
  openSubExpr();
}

CalcEngine::~CalcEngine() {
  while (!mOutputStk.empty()) {
    delete mOutputStk.top();
    mOutputStk.pop();
  }

  while (!mProcessStk.empty()) {
    delete mProcessStk.top();
    mProcessStk.pop();
  }
}

void CalcEngine::shiftExpr() {
  Expression* topExpr = mProcessStk.top();
  if (topExpr->mArgNumber > mOutputStk.size()) {
    throw "Not enough arguments";
  }

  for (size_t i = 0; i < topExpr->mArgNumber; i++) {
    topExpr->pushArg(mOutputStk.top());
    mOutputStk.pop();
  }

  mProcessStk.pop();
  mOutputStk.push(topExpr);
}

void CalcEngine::pushExpr(Expression* expr) {
  _ASSERT_EXPR(expr, L"Null pointer");

  if (mProcessStk.empty()) {
    throw "Missing opening parentheses";
  }

  if (expr->mPrecendence == NUM_PRECEDENCE ||
      expr->mNotation == Notation::POSTFIX) {
    mOutputStk.push(expr);
    return;
  }

  if (expr->mNotation == Notation::PREFIX) {
    mProcessStk.push(expr);
    return;
  }

  Expression* topExpr = mProcessStk.top();
  while (topExpr && topExpr->mPrecendence >= expr->mPrecendence) {

    if (topExpr->mPrecendence == expr->mPrecendence &&
        expr->mAssociativity == Associativity::RIGHT_ASSOCIATIVE) {
      break;
    }

    shiftExpr();
    topExpr = mProcessStk.top();
  }
  mProcessStk.push(expr);
}

void CalcEngine::openSubExpr() {
  mProcessStk.push(nullptr);
}

void CalcEngine::closeSubExpr() {
  if (mProcessStk.empty()) {
    throw "Missing opening parentheses";
  }

  while (mProcessStk.top()) {
    shiftExpr();
  }
  mProcessStk.pop();
}

Expression* CalcEngine::popOutputExpr() {
  closeSubExpr();
  if (mOutputStk.size() != 1) {
    throw "Incomplete expression";
  }

  if (mProcessStk.size()) {
    throw "Missing closing parentheses";
  }

  Expression* outputExpr = mOutputStk.top();
  mOutputStk.pop();
  return outputExpr;
}