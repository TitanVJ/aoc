#include <iostream>
#include <bits/stdc++.h>

// constexpr int max_r = 12;
// constexpr int max_g = 13;
// constexpr int max_b = 14;

std::unordered_map<std::string, int> MAX_CUBES = {
    {"red", 12},
    {"green", 13},
    {"blue", 14}
};

void soln(std::istream& input){

    std::string line{};
    int game = 0;
    int total = 0;
    while( getline(input, line) ) {
        game++;
        size_t pos = line.find(':');
        std::stringstream s{ line.substr(pos + 2, line.length() - pos + 1) };
        int value; std::string colour;
        bool add = true;
        while( s >> value && s >> colour ){
            char last = colour[colour.length() -1];
            if( last == ';' || last == ',' ) colour = colour.substr(0, colour.length() - 1);
            if( value > MAX_CUBES.at(colour) ){ add = false; break; }
        }
        if(add) {
            total += game;
            std::cout << " TRUE" << std::endl;
        } else { std::cout << " FALSE" << std::endl; }
    }
    std::cout << "Total: " << total << std::endl;

}


void soln2(std::istream& input){

    std::string line{};
    // int game = 0;
    int total = 0;

    while( getline(input, line) ) {
        // game++;
        size_t pos = line.find(':');
        std::stringstream s{ line.substr(pos + 2, line.length() - pos + 1) };
        int value; std::string colour;
        // bool add = true;
        std::unordered_map<std::string, int> GAME_MAX = {
            {"red", 0},
            {"green", 0},
            {"blue", 0}
        };
        // std::istringstream s{ line };
        // std::cout << "start -----------" << std::endl;
        // std::cout << value << colour << std::endl;
        // s >> value; s >> colour;
        while( s >> value && s >> colour ){
            char last = colour[colour.length() -1];
            if( last == ';' || last == ',' ) colour = colour.substr(0, colour.length() - 1);
            // if( value > MAX_CUBES.at(colour) ){ add = false; break; }
            // std::cout << colour << ": " << value  << "-- " << GAME_MAX[colour] << std::endl;

            GAME_MAX[colour] = std::max( GAME_MAX[colour], value );
        }
        // std::cout << std::reduce(GAME_MAX.begin(), GAME_MAX.end()) << std::endl;
        // total += std::accumulate(GAME_MAX.begin(), GAME_MAX.end(), 1,
        //                 [](const int prev, const std::pair<const std::string, int>& value){
        //                     std::cout << prev << " " << value.second << std::endl;
        //                     return prev+value.second;
        //                 });
        // std::cout << "==============================" << std::endl;
        // for(auto& [key, pair]: GAME_MAX){
            // std::cout << key << " " << pair << std::endl;
        // }
        total += std::accumulate(std::begin(GAME_MAX), std::end(GAME_MAX), 1,
        [](const auto& prev, const auto& value){
            // std::cout << prev << " " << value.second;
            return prev*value.second;
            });
    }
    std::cout << "Total: " << total << std::endl;

}

int main() {
    soln2(std::cin);
    return 0;
}