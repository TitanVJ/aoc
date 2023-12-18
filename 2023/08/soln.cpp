#include <iostream>
#include <bits/stdc++.h>

using Node_t = std::pair<std::string, std::string>;
using Lookup_t = std::unordered_map<std::string, Node_t>;

// size_t cycle_len(Lookup_t& table, std::string start, std::string end){
//     int i = 0;
//     while( true ){
//         key =  (steps[ i % step_size ] == 'L')? table[key].first : table[key].second;
//         ++i;
//         if( key == "ZZZ") break;
//     }

// }


void soln(std::istream& input){

    std::string steps, line;
    getline(input, steps);
    getline(input, line);
    size_t step_size = steps.length();

    Lookup_t table;
    auto notAlpha = [](const char c) -> bool { return !isalpha(c); };
    while( getline(input, line) ){
        if( line == "" ) continue;

        std::istringstream s{line};
        std::string key, t, a, b;
        s >> key >> t >> a >> b;
        a.erase( std::remove_if( std::begin(a), std::end(a), notAlpha), std::end(a) );
        b.erase( std::remove_if( std::begin(b), std::end(b), notAlpha), std::end(b) );

        table[key] = std::make_pair(a, b);
    }
    int i = 0; std::string key = "AAA";
    while( true ){
        key =  (steps[ i % step_size ] == 'L')? table[key].first : table[key].second;
        ++i;
        if( key == "ZZZ") break;
    }
    std::cout << "Steps: " << i << std::endl;
}

void soln2(std::istream& input){
    std::string steps, line;
    getline(input, steps);
    getline(input, line);
    size_t step_size = steps.length();

    std::vector<std::string> Z;
    Lookup_t table;
    auto notAlpha = [](const char c) -> bool { return !isalnum(c); };
    while( getline(input, line) ){
        if( line == "" ) continue;

        std::istringstream s{line};
        std::string key, t, a, b;
        s >> key >> t >> a >> b;
        a.erase( std::remove_if( std::begin(a), std::end(a), notAlpha), std::end(a) );
        b.erase( std::remove_if( std::begin(b), std::end(b), notAlpha), std::end(b) );

        table[key] = std::make_pair(a, b);
        if( key.back() == 'A' ) { Z.push_back(key); }
    }

    std::vector<size_t> lens;
    for(auto z: Z){
        std::string key = z;
        size_t i = 0;
        while( true ){
            key =  (steps[ i % step_size ] == 'L')? table[key].first : table[key].second;
            ++i;
            if( key.back() == 'Z' ) break;
        }
        lens.push_back(i);
    }
    size_t total = 1;
    for(int i = 0; i < lens.size(); ++i){
        total = std::lcm(total, lens[i]);
    }
    std::cout << "Steps: " << total << std::endl;
}

int main() {
    soln2(std::cin);
    return 0;
}