#include "convertationFunctions.h"

namespace {
  gruzdev::ExpressionPart separationForUnion(const std::string& token)
  {
    if (token.length() == 1 && !std::isdigit(token.at(0))) {
      gruzdev::ExpressionPart part(token.at(0));
      return part;
    } else {
      gruzdev::ExpressionPart part(std::stoll(token));
      return part;
    }
  }
}

gruzdev::Queue< gruzdev::ExpressionPart > gruzdev::convertStringToInfix(std::string str)
{
  gruzdev::Queue< gruzdev::ExpressionPart > infix;
  size_t pos = 0;
  std::string token = "";
  while ((pos = str.find(' ')) != std::string::npos) {
    token = str.substr(0, pos);
    if (token != " ") {
      infix.push(separationForUnion(token));
    }
    str.erase(0, pos + 1);
  }
  infix.push(separationForUnion(str));
  return infix;
}

gruzdev::Queue< gruzdev::ExpressionPart > gruzdev::convertInfixToPostfix(Queue< gruzdev::ExpressionPart >& infix)
{
  gruzdev::Stack< gruzdev::ExpressionPart > conversion;
  gruzdev::Queue< gruzdev::ExpressionPart > postfix;
  while (!infix.empty()) {
    if (infix.front().getType() == gruzdev::ExpressionPartType::OPERAND) {
      postfix.push(infix.front());
    } else {
      if (infix.front() == gruzdev::ExpressionPart('(')) {
        conversion.push(infix.front());
      } else if (infix.front() == gruzdev::ExpressionPart(')')) {
        while (conversion.top() != gruzdev::ExpressionPart('(') && !conversion.empty()) {
          postfix.push(conversion.top());
          conversion.pop();
        }
        if (conversion.empty()) {
          throw std::logic_error("Incorrect arithmetic expression!");
        }
        conversion.pop();
      } else {
        if (conversion.empty() || conversion.top() == gruzdev::ExpressionPart('(')) {
          conversion.push(infix.front());
        } else {
          if (infix.front().getPriority() > conversion.top().getPriority()) {
            conversion.push(infix.front());
          } else {
            while (!conversion.empty() && infix.front().getPriority() <= conversion.top().getPriority()) {
              postfix.push(conversion.top());
              conversion.pop();
            }
            conversion.push(infix.front());
          }
        }
      }
    }
    infix.pop();
  }
  while (!conversion.empty()) {
    if (conversion.top() == ExpressionPart('(')) {
      throw std::logic_error("Invalid arithmetic expression!");
    }
    postfix.push(conversion.top());
    conversion.pop();
  }
  return postfix;
}

long long gruzdev::convertPostfixToResult(Queue< gruzdev::ExpressionPart >& postfix)
{
  gruzdev::Stack< long long int > calculation;
  long long int result = 0;
  while (!postfix.empty()) {
    if (postfix.front().getType() == gruzdev::ExpressionPartType::OPERAND) {
      calculation.push(postfix.front().getOperand());
    } else {
      long long int right = calculation.top();
      calculation.pop();
      long long int left = calculation.top();
      calculation.pop();
      switch (postfix.front().getOperation()) {
      case '+':
        result = gruzdev::summarize(left, right);
        break;
      case '-':
        result = gruzdev::subtract(left, right);
        break;
      case '*':
        result = gruzdev::multiply(left, right);
        break;
      case '/':
        result = gruzdev::divide(left, right);
        break;
      case '%':
        result = gruzdev::divideWithRemainder(left, right);
        break;
      }
      calculation.push(result);
    }
    postfix.pop();
  }
  return calculation.top();
}
