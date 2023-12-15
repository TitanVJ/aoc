#include <iostream>
#include <bits/stdc++.h>

struct Map_entry { //NOTE: re-enable this => map -> map entry and have a map consist of these?
             //      move the strings to the parent element instead for the map values?
    private:
        size_t src;
        size_t dst;
        size_t range;
    public:
        Map_entry(size_t _src, size_t _dst, size_t _range) :src{_src}, dst{_dst}, range{_range} {}
        size_t get(size_t key) {
            if( key >= src && key <= src+range) return dst + abs(src - key);
            return key;
        }
        friend std::ostream& operator<<(std::ostream&, const Map_entry&);
};
using Entry_t = struct Map_entry;

std::ostream& operator<<(std::ostream& os, const Entry_t& data) {
    os  << std::setw(10) << data.src
        << " -> "
        << std::setw(10) << data.dst
        << std::setw(12) << "(" << data.range << ")";
    return os;
}

struct Map {
    private:
        std::vector<Entry_t> entries;
    public:
        Map(): entries{} {}
        void add(size_t s, size_t d, size_t r) { entries.emplace_back(s, d, r); }
        size_t operator[](const size_t key){
            // TODO: all entries for possible mapping
            auto it = std::begin(entries);
            size_t ret = key;
            do {
                ret = it++->get(key);
            } while( it != std::end(entries) && ret == key);
            return ret;
        }
        friend std::ostream& operator<<(std::ostream&, const Map&);
};
using Map_t = struct Map;
std::ostream& operator<<(std::ostream& os, const Map& data) {
    for(auto& e : data.entries )
        os << e << std::endl;
    return os;
}

// NOTE: for part 2 need a ranged seed type like above.
//       only matters for seed -> soil, after that its normal?

void soln(std::istream& input){
    std::string line;
    std::vector<size_t> seeds;

    getline(input, line);
    std::stringstream sds{line};
    std::string seed;
    sds >> seed;
    while( sds >> seed )
        seeds.push_back( std::stoll(seed) );

    std::vector<Map_t> maps(7);
    size_t map_idx = -1;
    while( getline(input, line) ){
        if(line.empty()) continue;

        //NOTE: use to fill next map
        if( !isdigit(line[0]) ) {
            // std::cout << std::endl;
            ++map_idx;
            continue;
        }

        std::stringstream s{line};
        size_t dst, src, range;
        s >> dst >> src >> range;
        maps[map_idx].add(src, dst, range);
    }

    // size_t i = 0;
    // for(auto& map : maps ){
    //     std::cout << "Map: " << i++ << std::endl;
    //     std::cout << map << std::endl;
    // }

    // need location per seed
    std::vector<size_t> locs;
    for( auto seed : seeds ) {
        // std::cout << "Seed: " << seed << " ";
        size_t key = seed;
        for( auto& map : maps ){
            key = map[key];
        }
        // std::cout << "Loc: " << key << std::endl;
        locs.push_back(key);
    }
    size_t min = *std::min_element(std::begin(locs), std::end(locs));
    std::cout << "Min Location: " << min << std::endl;

}

void soln2(std::istream& input){

}

int main() {
    soln(std::cin);
    return 0;
}