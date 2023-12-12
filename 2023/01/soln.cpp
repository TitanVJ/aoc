#include <iostream>
#include <string>
#include <map>
#include <unordered_map>

const std::multimap<char, std::pair<int, std::string>> NUM_TREE = {
    {'o', {3, "one"}},
    {'t', {3, "two"}},
    {'t', {5, "three"}},
    {'f', {4, "four"}},
    {'f', {4, "five"}},
    {'s', {3, "six"}},
    {'s', {5, "seven"}},
    {'e', {5, "eight"}},
    {'n', {4, "nine"}}
};

const std::unordered_map<std::string, int> NUMS = {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9}
};

void soln(std::istream& input) {
    std::string line = "";
    int total = 0;
    while(input >> line){
        int a = -1;
        int b = -1;
        for(int i = 0; i < line.length(); ++i){
            if( isdigit(line[i]) ){
                if( a < 0 ) a = i;
                b = i;
            }
        }
        total += std::stoi( std::string() + line[a] + line[b] );
    }
    std::cout << total << std::endl;
}

void soln2(std::istream& input){
// check every substring until first num is found in one direction then repeat in the other?
// saves for string? but what if only nums at start either form?

    std::string line = "";
    int total = 0;

    while( input >> line ) {
        int a = -1; int b = -1;
        int len = line.length();
        for(int i = 0; i < len; i++){
            if( isdigit(line[i]) ){
                int n = line[i] - '0';
                if(a < 0) a = n;
                b = n;
            } else if( auto [it, end] = NUM_TREE.equal_range(line[i]); it != end ){
                for( ; it != end; ++it ){
                    std::string s = line.substr(i, std::get<0>(it->second));
                    if(s == std::get<1>(it->second)){
                        int n = NUMS.at(s);
                        if(a < 0) a = n;
                        b = n;
                    }
                }
            }
        }
        total += std::stoi(std::to_string(a) + std::to_string(b));
    }
    std::cout << "Total: " << total << std::endl;
}

int main(){
    soln2(std::cin);
    return 0;
}