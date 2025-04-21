#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdexcept>
#include <string>

namespace gruzdev {

  enum class ExpressionPartType {
    OPERAND,
    OPERATION,
    BRACKET
  };

  class ExpressionPart {
    public:
      ExpressionPart() = delete;
      explicit ExpressionPart(long long int operand);
      explicit ExpressionPart(char symbol);

      long long int getOperand() const;
      char getOperation() const;
      char getBracket() const;
      int getPriority() const;
      ExpressionPartType getType() const;

      bool operator==(const ExpressionPart& rhs) const;
      bool operator!=(const ExpressionPart& rhs) const;

    private:
      union {
        long long int operand_;
        char symbol_;
      };
      ExpressionPartType type_;
  };
}

#endif
