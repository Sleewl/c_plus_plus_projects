#ifndef CONVERTATIONFUNCTIONS_H
#define CONVERTATIONFUNCTIONS_H

#include <stack.h>
#include <queue.h>
#include "element.h"
#include "operations.h"

namespace gruzdev {
  gruzdev::Queue< gruzdev::ExpressionPart > convertStringToInfix(std::string str);
  gruzdev::Queue< gruzdev::ExpressionPart > convertInfixToPostfix(Queue< gruzdev::ExpressionPart >& infix);
  long long int convertPostfixToResult(Queue< gruzdev::ExpressionPart >& postfix);
}

#endif
