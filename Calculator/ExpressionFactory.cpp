#include <filesystem>
#include "ExpressionFactory.h"
#include "BinaryOperation.h"
#include "Number.h"

using infoFunc = void (*)(ExpressionInfo&);

ExpressionFactory::ExpressionFactory() {
  registerExpr("+", new Addition);
  registerExpr("-", new Subtraction);
  registerExpr("*", new Multiplication);
  registerExpr("/", new Division);
}

ExpressionFactory::~ExpressionFactory() {
  for (auto& elem : mRegister) {
    delete elem.second;
  }

  for (auto& dllHandler : mAdditionalDll) {
    FreeLibrary(dllHandler);
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

void ExpressionFactory::registerExpr(const wchar_t* dllName) {
  HINSTANCE hDll = LoadLibrary(dllName);
  if (!hDll) { return; }

  infoFunc getInfo = (infoFunc)GetProcAddress(hDll, "getExpressionInfo");
  if (!getInfo) { return; }

  ExpressionInfo info;
  getInfo(info);
  registerExpr(info.name, info.prototype);

  mAdditionalDll.push_back(hDll);
}

ExpressionFactory* ExpressionFactory::createFromDll(const string& directory) {
  ExpressionFactory* factory = new ExpressionFactory;

  for (auto& p : filesystem::directory_iterator(directory)) {
    if (p.path().extension() != ".dll") { continue; }

    factory->registerExpr(p.path().c_str());
  }
  return factory;
}
