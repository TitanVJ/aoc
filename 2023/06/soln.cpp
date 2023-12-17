#include <iostream>
#include <bits/stdc++.h>

void factorize(std::vector<size_t>& factors, size_t N){
    factors.push_back(N);
    factors.push_back(1);
    int i = 2;
    while( i < N ){

        int fac = N / i;
        if( fac * i == N ){
            factors.push_back(i);
            if(i != fac) factors.push_back(fac);
            N = fac;
        }
        i++;
    }
    std::sort(std::begin(factors), std::end(factors));
}

void soln(std::istream& input){
    std::string times;
    std::string dists;
    getline(input, times);
    getline(input, dists);

    std::istringstream ts{times};
    std::istringstream ds{dists};
    std::string buff;

    ts >> buff; ds >> buff;
    size_t t, d;
    std::vector<std::pair<size_t, size_t>> races;
    while( ts >> t && ds >> d ){ races.emplace_back(t, d); }

    size_t total = 1;
    for( auto& race: races ){
        size_t time = race.first;
        size_t dist = race.second;
        std::vector<std::pair<size_t, size_t>> parts;
        for( size_t i = 0 , j = time; i <= j; ++i, --j ){
            parts.emplace_back(i, j);
        }

        size_t c = std::count_if(  std::begin(parts), std::end(parts),
                                [dist](const auto& a){ return a.first*a.second > dist; });
        size_t cc = 2*c - ((time%2==0)? 1 : 0);
        total *= cc;
    }
    std::cout << "Total: " << total << std::endl;
}

void soln2(std::istream& input){
    //NOTE: brute force for the winning. math == headache
    std::string times;
    std::string dists;
    getline(input, times);
    getline(input, dists);

    std::istringstream ts{times};
    std::istringstream ds{dists};
    std::string buff;

    ts >> buff; ds >> buff;
    std::string t, d, t_str = "", d_str = "";
    while( ts >> t && ds >> d ){ t_str += t; d_str += d; }

    size_t time = std::stoull(t_str);
    size_t dist = std::stoull(d_str);

    size_t total = 1;
    std::vector<std::pair<size_t, size_t>> parts;
    for( size_t i = 0 , j = time; i <= j; ++i, --j ){
        parts.emplace_back(i, j);
    }

    size_t c = std::count_if(  std::begin(parts), std::end(parts),
                            [dist](const auto& a){ return a.first*a.second > dist; });
    size_t cc = 2*c - ((time%2==0)? 1 : 0);
    total *= cc;
    std::cout << "Total: " << total << std::endl;
}

int main() {
    soln2(std::cin);
    return 0;
}