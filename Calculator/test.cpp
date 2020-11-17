#include <iostream>
#include "ExpressionParser.h"

using namespace std;

int main()
{
  try {
    ExpressionFactory* factory = ExpressionFactory::createFromDll("../plugins");
    ExpressionParser parser(factory);
    Expression* expr = parser.parse("sin ( 2 / 4 )", " ");
    cout << expr->evaluate() << endl;
    delete expr;

  } catch (const char* e) {
    cout << e << endl;
  }

  return 0;
}
