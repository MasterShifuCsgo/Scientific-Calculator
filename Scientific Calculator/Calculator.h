#pragma once
#include <string>
#include <string_view>
#include <unordered_set>
#include <map>
#include <vector>

namespace Calculator {
    
  //available operators are defined in order least to most valuable.
  extern const std::string_view operator_order;
  extern std::unordered_set<char> operator_lookup;
  extern std::map<char, std::vector<int>> operator_positions;
  /*
  *
  * creating positions for all of them is not a great idea, because when one sub-equation gets solved, then it should switch out the sub-equation with
  * its result.
  * 1. you cannot create a new equation because then looking for the positions would be redundant computation
  *
  * FIX:
  * drop finding the positions of all the valuable equations.
  * instead, you look for the most valuable equation every time. that would be O(n^2).
  * you could result the right most valuable equations first, going from right to left, then move to the next most valuable equation, not look for one each time.
  * this would not change the found positions of the left side valuable equations.
  * thats fast enough for me.
  */

  

    //takes 2 numbers and uses the operator to get the result
    extern double useOperator(int& anchor, int& operand, char op);
    
    //calculates the user equation
    extern double calculate(std::string equation);
}