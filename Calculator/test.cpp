#include <iostream>
#include "ExpressionParser.h"

constexpr size_t buffSize = 256;

using namespace std;

int main()
{
  ExpressionFactory* factory = ExpressionFactory::createFromDll("plugins");
  ExpressionParser parser(factory);

  cout << "Please, write spaces between tokens." << endl;

  char buf[buffSize];
  cin.getline(buf, buffSize);

  while (buf[0]) {

    Expression* expr = parser.parse(buf, " ");
    if (expr) {
      cout << expr->evaluate() << endl;
    }

    delete expr;
    cin.getline(buf, buffSize);
  }
  return 0;
}
