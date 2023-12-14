#include <iostream>
#include <bits/stdc++.h>

int matches(std::string line) {
    std::unordered_map<int, int> map;
    std::string num;
    std::stringstream s{line};
    s >> num; s >> num;
    while( s >> num ){
        if( !num.compare("|") ) continue;
        map[ std::stoi(num) ]++;
    }
    return  std::accumulate(std::begin(map), std::end(map), 0,
                            [](const auto& lhs, const auto& pair){
                                return lhs + (int)(pair.second == 2);
                            });
}

void soln(std::istream& input){
    std::string line;
    int total = 0;
    while( getline(input, line) ){
        int t = matches(line);
        total += (t)? 1<<(t-1) : 0;
    }
    std::cout << "Total: " << total << std::endl;
}

void soln2(std::istream& input){
    std::string line;
    int total = 0;
    int card = 0;
    std::vector<int> cards = {0};
    while( getline(input, line) ){
        int t = matches(line);
        cards[card]++;
        cards.resize(cards.size() + t);
        int copies = cards[card];
        for(int i = card+1; i <= card+t; ++i){
            cards[ i ] += copies;
        }
        card++;
    }
    int value = std::accumulate(std::begin(cards), std::begin(cards)+card, 0);
    std::cout << "Total: " << value << std::endl;
}

int main() {
    soln2(std::cin);
    return 0;
}