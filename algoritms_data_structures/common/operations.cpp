#include "operations.h"

#include <limits>
#include <stdexcept>

namespace {
  const long long int max_long_int = std::numeric_limits< long long int >::max();
  const long long int min_long_int = std::numeric_limits< long long int >::min();

  int sign(long long int val)
  {
    return (val > 0) ? 1 : ((val < 0) ? -1 : 0);
  }

  bool sameSign(long long int a, long long int b)
  {
    return sign(a) * sign(b) >= 0;
  }

}

long long int bazhenov::summarize(long long int left, long long int right)
{
  if (!sameSign(left,right)) {
    return left + right;
  } else {
    if (left > 0) {
      if (right <= max_long_int - left) {
        return left + right;
      }
    } else {
      if (right >= min_long_int - left) {
        return left + right;
      }
    }
  }
  throw std::logic_error("Overflow!+");
}

long long int bazhenov::subtract(long long int left, long long int right)
{
  if (sameSign(left,right)) {
    return left - right;
  } else {
    if (left > 0) {
      if (left <= max_long_int + right) {
        return left - right;
      }
    } else {
      if (left >= min_long_int + right) {
        return left - right;
      }
    }
  }
  throw std::logic_error("Overflow!-");
}

long long int bazhenov::divide(long long int left, long long int right)
{
  if (right == 0) {
    throw std::logic_error("Division by zero is impossible!");
  }
  return left / right;
}

long long int bazhenov::multiply(long long int left, long long int right)
{
  if (left == 0 || right == 0) {
    return 0;
  }
  if (sameSign(left,right)) {
    if (left <= max_long_int / right) {
      return left * right;
    }
  } else {
    if (left >= min_long_int / right) {
      return left * right;
    }
  }
  throw std::logic_error("Overflow!*");
}

long long int bazhenov::divideWithRemainder(long long left, long long right)
{
  if (right == 0) {
    throw std::logic_error("Division with remainder is impossible!");
  }
  if (sameSign(left, right)) {
    return left % right;
  }
  return (right + (left % right)) % right;
}
