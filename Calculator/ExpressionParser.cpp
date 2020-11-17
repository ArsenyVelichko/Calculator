#include <iostream>
#include "ExpressionParser.h"
#include "CalcEngine.h"

ExpressionParser::ExpressionParser(const ExpressionFactory* factory)
  : mFactory(factory) {}

ExpressionParser::~ExpressionParser() {
  delete mFactory;
}

vector<string> ExpressionParser::split(const string& str, const string& delimiter) const {
  vector<string> substrings;
  string copy = str;

  size_t pos;
  while ((pos = copy.find(delimiter)) != std::string::npos) {
    substrings.push_back(copy.substr(0, pos));
    copy.erase(0, pos + delimiter.length());
  }
  substrings.push_back(copy);
  return substrings;
}

Expression* ExpressionParser::parse(const string& str, const string& delimiter) const {
  vector<string> tokens = split(str, delimiter);

  CalcEngine engine;
  for (auto token : tokens) {

    try {
      if (token == "(") {
        engine.openSubExpr();

      } else if (token == ")") {
        engine.closeSubExpr();

      } else {
        Expression* newExpr = mFactory->getExpression(token);
        if (!newExpr) { return nullptr; }

        engine.pushExpr(newExpr);
      }

    } catch (const char* msg) {
      cout << msg << endl;
      return nullptr;
    }
  }

  return engine.popOutputExpr();
}