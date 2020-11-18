#include <iostream>

#include "ExpressionParser.h"

using namespace std;

int main()
{
  try {
    ExpressionFactory* factory = ExpressionFactory::createFromDll("plugins");
    ExpressionParser parser(factory);

    char buf[256];
    cin.getline(buf, 256);
    Expression* expr = parser.parse(buf, " ");
    cout << expr->evaluate() << endl;
    system("pause");
    delete expr;

  } catch (const char* e) {
    cout << e << endl;
  }

  return 0;
}
