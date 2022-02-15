#include <iostream>
#include <string>
#include <regex>
#include <iterator>

// Converts from RC to an Excel structure using the x mod 26 to find the first
// character and then adds it to the string until c < 26.
std::string convertFromRC(int c, std::string r, std::string str = ""){
  int modulus;
  int n = 0;
  modulus = c % 26;
  str += (char)(modulus+65);
  if(c < 26){
    str += (char)(c+65);
    reverse(str.begin(), str.end());
    str += r;
    std::cout << c << " is now less than 26" << std::endl;
    std::cout << str << std::endl;
    return str;
  }
  else{
    std::cout << c << " is now here" << std::endl;
    while(26*n <= c){
      n++;
    }
    return convertFromRC(n, r, str);
  }
}

// Takes the modulus of the letter (mod 64) to convert to RxxCyy
std::string convertFromExcel(const std::string &col, const std::string &row){
  std::string str;
  int modulus;
  str += 'R';
  str += row;
  str += 'C';
  for(auto &e: col){
    modulus = ((int) e) % 64;
    str += std::to_string(modulus);
  }
  return str;
}


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
    col = std::regex_replace(s, std::regex("[A-Z]+"), "$2");
    row = std::regex_replace(s, std::regex("[0-9]+"), "$2");
    return convertFromExcel(col, row);
  }
  return "No match";
}
int main(int argc, char const *argv[]) {
  std::string str;
  std::cin >> str;
  std::cout << str << std::endl;
  std::cout << convertString(str) << std::endl;
  return 0;
}
