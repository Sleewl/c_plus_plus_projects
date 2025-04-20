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
  bazhenov::Stack< long long int > answers;
  std::string token = "";

  try {
    while (std::getline(in,token)) {
      if (!token.empty()) {
        bazhenov::Queue< bazhenov::ExpressionPart > infix = bazhenov::convertStringToInfix(token);
        bazhenov::Queue< bazhenov::ExpressionPart > postfix = bazhenov::convertInfixToPostfix(infix);
        answers.push(bazhenov::convertPostfixToResult(postfix));
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
