#pragma once
#include <string>

namespace Calculator {
    
    //takes 2 numbers and uses the operator to get the result
    extern double useOperator(int& anchor, int& operand, char& op);
    
    //calculates the user equation
    extern double calculate(std::string& equation);
}