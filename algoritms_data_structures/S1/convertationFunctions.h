#ifndef CONVERTATIONFUNCTIONS_H
#define CONVERTATIONFUNCTIONS_H

#include <stack.h>
#include <queue.h>
#include "element.h"
#include "operations.h"

namespace bazhenov {
  bazhenov::Queue< bazhenov::ExpressionPart > convertStringToInfix(std::string str);
  bazhenov::Queue< bazhenov::ExpressionPart > convertInfixToPostfix(Queue< bazhenov::ExpressionPart >& infix);
  long long int convertPostfixToResult(Queue< bazhenov::ExpressionPart >& postfix);
}

#endif
