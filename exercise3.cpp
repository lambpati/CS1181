//Name: Patience Lamb
//Semester: Spring 2022
//Date: January 24, 2021
//Email:lambpati@isu.edu
//Brief: Returns the roman numeral equivalent to user's arabic numeral input.
#include <iostream>
#include <algorithm>
#include <map>
#include <stdexcept>

// Throws an out of range error when the user inputs a value below 1 or above 3999
void rangeCheck(int number){
  if(number > 3999 || number < 1){
    throw std::range_error("Number must be between 1-3999. Please rerun the program and try again.");
  }
}

// Maps intNum to the string equivalent in roman numerals through two separate
// arrays where one subtracts the arabic value from intNum and the other adds
// the roman numeral equivalent to the answer.
std::string romanNum(int intNum){
  std::string answer;
  std::string roman[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
  int numbers[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
  for(int i = 0; i < 13; i++){
    while(intNum - numbers[i] >= 0){
      answer += roman[i];
      intNum -= numbers[i];
    }
  }
  return answer;

}
int main(int argc, char const *argv[]) {
try{
  int number;
  std::cout << "Please enter a number to convert to Roman Numerals: " ;
  std::cin >> number;

  rangeCheck(number);
  std::cout << number << " in Roman Numerals is " << romanNum(number) << std::endl;
}
catch(const std::range_error& e){
  std::cerr << e.what() << std::endl;
  return -1;
}
  return 0;
}
