#include <iostream>
#include <fstream>

#include "convertationFunctions.h"

int main(int argv, char** argc)
{
  std::ifstream file;
  if (argv == 2) {
    file.open(argc[1]);
    if (!file.is_open()) {
      std::cerr << "Error in opening file!";
      return 1;
    }
  }

  std::istream& in = file.is_open() ? file : std::cin;
  gruzdev::Stack< long long int > answers;
  std::string token = "";

  try {
    while (std::getline(in,token)) {
      if (!token.empty()) {
        gruzdev::Queue< gruzdev::ExpressionPart > infix = gruzdev::convertStringToInfix(token);
        gruzdev::Queue< gruzdev::ExpressionPart > postfix = gruzdev::convertInfixToPostfix(infix);
        answers.push(gruzdev::convertPostfixToResult(postfix));
      }
    }
  } catch (const std::exception& ex) {
      std::cerr << ex.what() << "\n";
      return 1;
  }

  if (answers.empty()) {
    std::cout << "\n";
  }

  while (!answers.empty()) {
    std::cout << answers.top();
    answers.pop();
    answers.empty() ? std::cout << "\n" : std::cout << " ";
  }
}
