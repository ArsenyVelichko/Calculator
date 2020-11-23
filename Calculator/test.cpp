#include <iostream>
#include "ExpressionParser.h"

using namespace std;

int main()
{
  ExpressionFactory* factory = ExpressionFactory::createFromDll("plugins");
  ExpressionParser parser(factory);

  cout << "Please, write spaces between tokens." << endl;

  string buf;
  getline(cin, buf);

  while (buf[0]) {

    Expression* expr = parser.parse(buf, " ");
    if (expr) {
      cout << expr->evaluate() << endl;
    }

    delete expr;
    getline(cin, buf);
  }
  return 0;
}
