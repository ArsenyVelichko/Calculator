#include <iostream>

#include "ExpressionParser.h"

constexpr size_t buffSize = 256;

using namespace std;

int main()
{
  ExpressionFactory* factory = ExpressionFactory::createFromDll("plugins");
  ExpressionParser parser(factory);

  char buf[buffSize];
  cin.getline(buf, buffSize);
  Expression* expr = parser.parse(buf, " ");
  if (expr) {
    cout << expr->evaluate() << endl;
  }

  system("pause");
  delete expr;

  return 0;
}
