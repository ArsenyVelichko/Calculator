#include "CalcEngine.h"
#include <assert.h>

CalcEngine::CalcEngine() {
  openSubExpr();
}

void CalcEngine::shiftExpr() {
  Expression* topExpr = mProcessStk.top();
  if (topExpr->mArgNumber > mOutputStk.size()) {
    throw "Not enough arguments";
  }

  for (size_t i = 0; i < topExpr->mArgNumber; i++) {
    topExpr->pushArg(mOutputStk.front());
    mOutputStk.pop();
  }

  mProcessStk.pop();
  mOutputStk.push(topExpr);
}

void CalcEngine::pushExpr(Expression* expr) {
  _ASSERT_EXPR(expr, L"Null pointer");

  if (mProcessStk.empty()) {
    throw "Missing parentheses";
  }

  if (expr->mPrecendence == NUM_PRECEDENCE) {
    mOutputStk.push(expr);
    return;
  }

  if (expr->mPrefix) {
    mProcessStk.push(expr);
    return;
  }

  Expression* topExpr = mProcessStk.top();
  while (topExpr && topExpr->mPrecendence >= expr->mPrecendence) {

    if (topExpr->mPrecendence == expr->mPrecendence &&
        expr->mRightAssociative) {
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
    throw "Missing parentheses";
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

  Expression* outputExpr = mOutputStk.front();
  mOutputStk.pop();
  return outputExpr;
}