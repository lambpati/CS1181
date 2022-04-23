
// Name: Patience Lamb
// Date: 3/22/2022
// Brief: Solves problem C Shockers for Codeforces using
// C++ concepts.
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <fstream>

int sum = 26;
int count = 0;

std::vector<bool> findPath(std::string &word){
    std::vector<bool> locations(26, 0);
    for(int pos = 0; pos < word.size(); pos++){
        locations[word[pos]-'a'] = 1;
    }
    return locations;
}
std::vector<bool> noShock(std::vector<bool> &location, std::vector<bool> &valid){
    for(int letter = 0; letter < 26; letter++){
        if(valid[letter] && location[letter]){
            valid[letter] = 0;
            sum--;
        }
    }
    return valid;
}

std::vector<bool> shock(std::vector<bool> &location, std::vector<bool> &valid){
    for(int letter = 0; letter < 26; letter++){
        if(valid[letter] && !location[letter]){
            valid[letter] = 0;
            sum--;
        }
    }
    return valid;
}

std::vector<bool> guess(std::string &word, std::vector<bool> &valid){
    int letter = word.at(0) - 'a';
    if(valid[letter]){
        sum--;
    }
    valid[letter] = 0;
    return valid;
}

int determineAction(std::string &str){
    std::string word;
    std::vector<bool> valid(26,1);
    word = std::regex_replace(str, std::regex("[!.? ]"), "$2");
    std::vector<bool> loc = findPath(word);
    if(str.find('!') != std::string::npos){
        std::cout << "! activated" << std::endl; 
        shock(loc, valid);
    }
    else if(str.find('.') != std::string::npos){
        std::cout << ". activated" << std::endl;
        noShock(loc, valid);
        count += (sum == 1);
    }
    else if(str.find('?') != std::string::npos){
        std::cout << "? activated" << std::endl;
        guess(word, valid);
    }
    return count;
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
            std::cout << determineAction(str) << std::endl;
        }

    }
    catch(const std::ifstream::failure& e){
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
