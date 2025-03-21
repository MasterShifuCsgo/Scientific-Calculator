#include <iostream>
#include <numeric>
#include <string>
#include "Calculator.h"

template<typename T>
void getUserInput(T& variable) {
  while (true) {
    std::cin >> variable;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Please enter a real number";
      continue;
    }
    else {
      break;
    }
  }
}



int main()
{

  

  std::cout << "\n\n\nWelcome to calculator!\n\n\n";  

  std::string userInput;
  getUserInput(userInput);

  double result = Calculator::calculate(userInput);

  std::cout << "result: " << result;

}

