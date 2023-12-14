#include <iostream>
#include <bits/stdc++.h>

void soln(std::istream& input){
    std::string line;
    int total = 0;
    while( getline(input, line) ){
        std::stringstream s{line};
        std::string num;
        std::unordered_map<int, int> counts;
        s >> num; s >> num;
        while( s >> num ){
            if( !num.compare("|") ) continue;
            counts[ std::stoi(num) ]++;
        }

        int t = std::accumulate(std::begin(counts), std::end(counts), 0,
                                [](const auto& lhs, const auto& pair){
                                    return lhs + (int)(pair.second == 2);
                                });
        total += (t)? 1<<(t-1) : 0;
    }
    std::cout << "Total: " << total << std::endl;
}

void soln2(std::istream& input){

}

int main() {
    soln(std::cin);
    return 0;
}