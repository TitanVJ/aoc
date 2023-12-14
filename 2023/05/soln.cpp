#include <iostream>
#include <bits/stdc++.h>

struct Map_entry { //NOTE: re-enable this => map -> map entry and have a map consist of these?
             //      move the strings to the parent element instead for the map values?
    private:
        int src;
        int dst;
        int range;
        // std::unordered_map<int, std::pair<int, int>> map;
        // std::string source;
        // std::string destination;
    public:
        // Map(std::string _s, std::string _d): source{_s}, destination{_d};
        Map_entry(int _src, int _dst, int _range) :src{_src}, dst{_dst}, range{_range} {}
        // int operator[](const int idx){
        //     if( idx >= src && idx <= src+range ){
        //        return dst + (src + range - idx);
        //     }
        //     return idx;
        // }
        friend std::ostream& operator<<(std::ostream&, const Map_entry&);
};
using Entry_t = struct Map_entry;

std::ostream& operator<<(std::ostream& os, const Entry_t& data) {
    os  << std::setw(5) << data.src
        << " -> "
        << std::setw(5) << data.dst
        << std::setw(5) << "(" << data.range << ")";
    return os;
}
struct Map {
    private:
        std::vector<Entry_t> entries;
    public:
        Map(): entries{} {}
        void add(int s, int d, int r) { entries.emplace_back(s, d, r); }
        int operator[](const int key){
            // TODO: all entries for possible mapping
            return 0;
        }
        friend std::ostream& operator<<(std::ostream&, const Map&);
};
// using Map_t = std::vector<Entry_t>;
using Map_t = struct Map;
std::ostream& operator<<(std::ostream& os, const Map& data) {
    for(auto& e : data.entries )
        os << e << std::endl;
    return os;
}

void soln(std::istream& input){
    std::string line;
    std::vector<int> seeds;

    getline(input, line);
    std::stringstream sds{line};
    std::string seed;
    sds >> seed;
    while( sds >> seed )
        seeds.push_back( std::stoi(seed) );

    std::vector<Map_t> maps(7);
    int map_idx = -1;
    while( getline(input, line) ){
        if(line.empty()) continue;

        //NOTE: use to fill next map
        if( !isdigit(line[0]) ) {
            // std::cout << std::endl;
            ++map_idx;
            continue;
        }
        // std::cout << "[" << line << "]" << std::endl;

        std::stringstream s{line};
        int dst, src, range;
        s >> dst >> src >> range;
        maps[map_idx].add(src, dst, range);
    }

    int i = 0;
    for(auto& map : maps ){
        std::cout << "map: " << i++ << std::endl;
        // for(auto& entry: map ){
        //     std::cout << entry << std::endl;
        // }
        std::cout << map;
    }
}

void soln2(std::istream& input){

}

int main() {
    soln(std::cin);
    return 0;
}