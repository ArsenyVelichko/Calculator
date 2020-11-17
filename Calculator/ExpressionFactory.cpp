#include <filesystem>
#include <windows.h>
#include "ExpressionFactory.h"
#include "BinaryOperation.h"
#include "Number.h"

using infoFunc = void (*)(ExpressionInfo*);

ExpressionFactory::ExpressionFactory() {
  registerExpr("+", new Addition);
  registerExpr("-", new Subtraction);
  registerExpr("*", new Multiplication);
  registerExpr("/", new Division);
}

ExpressionFactory::~ExpressionFactory() {
  for (auto elem : mRegister) {
    delete elem.second;
  }
}

Expression* ExpressionFactory::getExpression(const string& grammarToken) const {
  try {
    double value = stod(grammarToken);
    return new Number(value);

  } catch (logic_error e) {

    auto elem = mRegister.find(grammarToken);
    if (elem != mRegister.end()) {
      return elem->second->clone();

    } else {
      return nullptr;
    }
  }
}

void ExpressionFactory::registerExpr(const string& grammarToken, const Expression* prototype) {
  mRegister[grammarToken] = prototype;
}

void ExpressionFactory::registerExpr(const ExpressionInfo& info) {
  registerExpr(info.name, info.prototype);
}

ExpressionFactory* ExpressionFactory::createFromDll(const string& directory) {
  ExpressionFactory* factory = new ExpressionFactory;

  for (auto& p : filesystem::directory_iterator(directory)) {
    if (p.path().extension() != ".dll") { continue; }

    HINSTANCE hDll = LoadLibrary(p.path().c_str());
    if (!hDll) { continue; }

    infoFunc getInfo = (infoFunc)GetProcAddress(hDll, "getExpressionInfo");
    if (!getInfo) { continue; }

    ExpressionInfo info;
    getInfo(&info);
    factory->registerExpr(info);
  }

  return factory;
}
