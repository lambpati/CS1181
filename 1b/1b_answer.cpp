// Name: Patience Lamb
// Date: 2/18/2022
// Brief: Solves problem 1B for Codeforces using regex, file handling, and basic
// C++ concepts.
#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <cmath>
#include <fstream>

// Converts from RC to an Excel structure using the x mod 26 to find the first
// character and then adds it to the string until c <= 1.
std::string convertFromRC(int c, std::string &r, std::string str = ""){
  if(c > 1){
    str += '@' + (c % 26);
    c /= 26;
    return convertFromRC(c, r, str);
  }
  else{
    if(c <= 1) str += 'A';
    reverse(str.begin(), str.end());
    str += r;
    return str;
  }
}

// Uses Radix-26 algorithm to convert from RxxCyy to [A-Z]xx
std::string convertFromExcel(std::string &col, std::string &row){
  int columns = 0;
  int conversion;
  std::string str;
  str += 'R';
  str += row;
  str += 'C';
  if(col == "A"){
    str += std::to_string(1);
    return str;
  }
  reverse(col.begin(), col.end());
  for(int i = 0; i < col.size(); i++){
    if(col.size() >= 2){
      conversion = ((int) col[i] % 65)+1;
      columns += pow(26, i)*conversion;
    }
    else{
      conversion = ((int) col[i] % 65);
      columns += 26+conversion;
    }
  }
  str += std::to_string(columns);
  return str;
}

// General driver to distinguish inputs of strings.
std::string convertString(const std::string &s){
  std::string row;
  std::string col;
  std::string out;
  int c;
  // Check to see if string is in the form RxxCyy
  if(std::regex_match(s, std::regex("R[0-9]+C[0-9]+"))){
    col = std::regex_replace(s, std::regex("R+[0-9]+C"), "$2");
    row = std::regex_replace(s, std::regex("C+[0-9]+"), "$2");
    row.erase(remove(row.begin(), row.end(), 'R'));
    c = std::stoi(col);
    return convertFromRC(c, row);
  }
  // Check to see if string is in the form [A-Z]xx
  else if (std::regex_match(s, std::regex("[A-Z]+[0-9]+"))){
    row = std::regex_replace(s, std::regex("[A-Z]+"), "$2");
    col = std::regex_replace(s, std::regex("[0-9]+"), "$2");
    return convertFromExcel(col, row);
  }
  return "No match";
}
int main(int argc, char const *argv[]) {
  std::string filename;
  std::string str;
  int lineNum = 0;
  std::cout << "Please specify file to convert (including extension & relative path)" << std::endl;
  std::cin >> filename;
  std::ifstream btest;
  btest.exceptions(std::ifstream::badbit); //I dont see why to check for badbits
  try{
    // File read and write
    btest.open(filename);
    if(!btest.is_open()){
      throw std::ifstream::failure("Cannot find file");
    }
    std::getline(btest,str);
    // Assuming first line is always the amount of times to iterate
    lineNum = std::stoi(str);

    for(int i = 0; i < lineNum; i++){
      std::getline(btest, str);
      std::cout << convertString(str) << std::endl;
    }

  }
  catch(const std::ifstream::failure& e){
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
