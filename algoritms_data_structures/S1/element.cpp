#include "element.h"

gruzdev::ExpressionPart::ExpressionPart(long long operand):
  operand_(operand),
  type_(ExpressionPartType::OPERAND)
{}

gruzdev::ExpressionPart::ExpressionPart(char symbol)
{
  const std::string str = "()+-*/%";
  size_t index = str.find(symbol);
  if (index == std::string::npos) {
    throw std::logic_error("Incorrect value for ExpressionPart");
  } else {
    type_ = (index < 2) ? ExpressionPartType::BRACKET : ExpressionPartType::OPERATION;
    symbol_ = symbol;
  }
}

char gruzdev::ExpressionPart::getBracket() const
{
  if (type_ == ExpressionPartType::BRACKET) {
    return symbol_;
  }
  throw std::logic_error("It is not a bracket!");
}

char gruzdev::ExpressionPart::getOperation() const {
  if (type_ == ExpressionPartType::OPERATION) {
    return symbol_;
  }
  throw std::logic_error("It is not an operation!");
}

long long int gruzdev::ExpressionPart::getOperand() const
{
  if (type_ == ExpressionPartType::OPERAND) {
    return operand_;
  }
  throw std::logic_error("It is not an operand");
}

gruzdev::ExpressionPartType gruzdev::ExpressionPart::getType() const
{
  return type_;
}

int gruzdev::ExpressionPart::getPriority() const {
  if (type_ == ExpressionPartType::OPERAND) {
    throw std::logic_error("Lack of priority execution for the operand!");
  } else if (type_ == ExpressionPartType::BRACKET) {
    return 0;
  } else {
    if (symbol_ == '+' || symbol_ == '-') {
      return 1;
    } else {
      return 2;
    }
  }
}

bool gruzdev::ExpressionPart::operator==(const ExpressionPart& rhs) const
{
  return type_ == rhs.type_ && (type_ == ExpressionPartType::OPERAND ? operand_ == rhs.operand_ : symbol_ == rhs.symbol_);
}

bool gruzdev::ExpressionPart::operator!=(const ExpressionPart& rhs) const
{
  return !(*this == rhs);
}
