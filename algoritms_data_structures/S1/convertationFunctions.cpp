#include "convertationFunctions.h"

namespace {
  bazhenov::ExpressionPart separationForUnion(const std::string& token)
  {
    if (token.length() == 1 && !std::isdigit(token.at(0))) {
      bazhenov::ExpressionPart part(token.at(0));
      return part;
    } else {
      bazhenov::ExpressionPart part(std::stoll(token));
      return part;
    }
  }
}

bazhenov::Queue< bazhenov::ExpressionPart > bazhenov::convertStringToInfix(std::string str)
{
  bazhenov::Queue< bazhenov::ExpressionPart > infix;
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

bazhenov::Queue< bazhenov::ExpressionPart > bazhenov::convertInfixToPostfix(Queue< bazhenov::ExpressionPart >& infix)
{
  bazhenov::Stack< bazhenov::ExpressionPart > conversion;
  bazhenov::Queue< bazhenov::ExpressionPart > postfix;
  while (!infix.empty()) {
    if (infix.front().getType() == bazhenov::ExpressionPartType::OPERAND) {
      postfix.push(infix.front());
    } else {
      if (infix.front() == bazhenov::ExpressionPart('(')) {
        conversion.push(infix.front());
      } else if (infix.front() == bazhenov::ExpressionPart(')')) {
        while (conversion.top() != bazhenov::ExpressionPart('(') && !conversion.empty()) {
          postfix.push(conversion.top());
          conversion.pop();
        }
        if (conversion.empty()) {
          throw std::logic_error("Incorrect arithmetic expression!");
        }
        conversion.pop();
      } else {
        if (conversion.empty() || conversion.top() == bazhenov::ExpressionPart('(')) {
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

long long bazhenov::convertPostfixToResult(Queue< bazhenov::ExpressionPart >& postfix)
{
  bazhenov::Stack< long long int > calculation;
  long long int result = 0;
  while (!postfix.empty()) {
    if (postfix.front().getType() == bazhenov::ExpressionPartType::OPERAND) {
      calculation.push(postfix.front().getOperand());
    } else {
      long long int right = calculation.top();
      calculation.pop();
      long long int left = calculation.top();
      calculation.pop();
      switch (postfix.front().getOperation()) {
      case '+':
        result = bazhenov::summarize(left, right);
        break;
      case '-':
        result = bazhenov::subtract(left, right);
        break;
      case '*':
        result = bazhenov::multiply(left, right);
        break;
      case '/':
        result = bazhenov::divide(left, right);
        break;
      case '%':
        result = bazhenov::divideWithRemainder(left, right);
        break;
      }
      calculation.push(result);
    }
    postfix.pop();
  }
  return calculation.top();
}
