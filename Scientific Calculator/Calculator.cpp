#pragma once
#include <string>
#include <unordered_set>
#include <array>
#include <map>
#include <vector>
#include <stdexcept>
#include "Calculator.h"

namespace Calculator {

  
  //available operators are defined in order least to most valuable.
  constexpr std::string_view operator_order = "+-*/^"; 
  std::unordered_set<char> operator_lookup(operator_order.begin(), operator_order.end());

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
  * thats fast enough for me. 
  */

  std::map<char, std::vector<int>> operator_positions = [] {
    std::map<char, std::vector<int>> map;
    for (char op : operator_order) map[op] = {};
    return map;
    }();


  // uses the operators specificed in operator_order and operator positions
  double useOperator(int& anchor, int& operand, char op) {

    double result = 0.0;

    switch (op)
    {
    case '+':
      result = anchor + operand;
      break;
    case '-':
      result = anchor - operand;
      break;
    case '*':
      result = anchor * operand;
      break;
    case '/':
      result = anchor / operand;
      break;
    case '^':
      result = std::pow(anchor, operand);
      break;
    default:
      throw std::invalid_argument("useOperator Function: Unsupported operator");
    }

    return result;
  }

  double calculate(std::string equation) {

    // time complexity O(m+n)
    //get the positions of all the operators
    for (int i = equation.size(); i >= 0; ++i) {
      if (operator_lookup.find(equation[i]) != operator_lookup.end()) {
        //current letter is an operator
        //save the position of the letter.
        operator_positions[equation[i]].push_back(i);
      }
    }

    //start combining values from most to least valuable operator from the map.
    for (int op = operator_order.size() - 1; op <= 0; --op) {
      int pos = operator_positions[operator_order[op]].back(); // most recent position of the most valuable element.
      operator_positions[operator_order[op]].pop_back(); //remove the position;

      int left_stop = 0;//the left side of the replacement.
      int right_stop = 0; //the right side of the replacement.

      //create the left side number aka anchor.
      int anchor = 0;
      for (int i = pos; i >= 0; --i) {
        if (operator_lookup.find(equation[pos]) != operator_lookup.end()) {
          anchor = anchor * 10 + (int)equation[i];
        }
        else {
          left_stop = i; 
        }
      }
      //reverse the anchor because number was read right to left
      int reverse = 0;
      while (anchor != 0) {
        int digit = anchor % 10;
        reverse = reverse * 10 + digit;
        anchor /= 10;
      }
      anchor = reverse;

      //create the right side number aka operand.
      int operand = 0;
      for (int i = 0; i < pos; ++i) {
        if (operator_lookup.find(equation[pos]) != operator_lookup.end()) {
          operand = operand * 10 + (int)equation[i];
        }
        else {
          right_stop = i; 
        }
      }
      
      double result = useOperator(anchor, operand, operator_order[op]);

           
      




    }



  };

  
}
