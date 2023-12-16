#include <iostream>
#include <bits/stdc++.h>

std::string nice(size_t n){
    std::string result_str = std::to_string(n);
	if (result_str.length() > 3)
	{
		for (int i = result_str.length() - 3; i > 0; i -= 3)
		{
        	result_str.insert(i, ",");
		}
	}
	return result_str;
}

struct Range {
    public:
        size_t start;
        size_t end;
        size_t length;

        Range(): start{0}, end{0}, length{0} {}
        Range(size_t _start, size_t _length) :start{_start},
                                              end{_start + _length - 1},
                                              length{_length} {}

        friend bool operator<(const Range& a, const Range& b) {
            return a.start < b.start;
        }

        friend std::ostream& operator<<(std::ostream& os, const Range& data) {
            size_t w = (data.length < 10000)? 4 : 13;
            os  << "Range: [" << std::setw(w) << nice(data.start)
                << " - " << std::setw(w) <<  nice(data.end)
                << "] (" << std::setw(w-1) << nice(data.length) << ")";
            return os;
        }
};
using Range_t = struct Range;

struct Map_entry {
    private:
        Range_t src;
        Range_t dst;
    public:
        Map_entry(size_t _src, size_t _dst, size_t _range) :src{_src, _range},
                                                            dst{_dst, _range} {}

       Range_t get(std::vector<Range_t>& values, Range_t key) {
           if( src.start > key.start && src.start > key.end){ // key above range
                values.emplace_back( dst.start, key.length ); // full coverage in a way
                return Range_t{};
            } else if( src.end < key.start ){// key below range
                return key;
            }

           // full coverage
            if( key.start >= src.start && key.end <= src.end ){
                values.emplace_back( dst.start + abs(key.start - src.start), key.length );
                return Range_t{};
            }

            // partial coverage
            size_t start = std::max( key.start, src.start );
            size_t end = std::min( key.end, src.end );
            size_t length = end - start + 1;
            values.emplace_back( dst.start + abs(start - src.start) , length );

            if( start > key.start ){ // 2 mappings
                values.emplace_back( key.start, abs(key.start - start));
                return Range_t{};
            } else { // 1 mapping
                if(key.length - length <= 0 ) std::cout << "\a FUCKED HERE\n";
                return Range_t{end+1, key.length - length};
            }
        }

        size_t get(size_t key) {
            if( key >= src.start && key <= src.end )
                return dst.start + abs(src.start - key);
            return key;
        }

        friend bool operator<(const Map_entry& a, const Map_entry& b){
            return a.src < b.src;
        }

        friend std::ostream& operator<<(std::ostream& os, const Map_entry& data) {
            os  << data.src
                << " -> "
                << data.dst;
            return os;
        }
};
using Entry_t = struct Map_entry;

struct Map {
    private:
        std::vector<Entry_t> entries;
    public:
        Map(): entries{} {}

        void add(size_t s, size_t d, size_t r) {
            entries.emplace_back(s, d, r);
            std::sort(  std::begin(entries), std::end(entries) );
        }

        void get(std::vector<Range_t>& values, Range_t key){
            int i = 0;
            for( auto& entry: entries ) {
                key = entry.get(values, key);
                if( !key.length ) break;
            }

            if( key.length != 0 ) {
                values.push_back(key);
            }
            sort(std::begin(values), std::end(values)); // might be redundant
        }

        size_t operator[](const size_t key){
            auto it = std::begin(entries);
            size_t ret = key;
            do {
                ret = it++->get(key);
            } while( it != std::end(entries) && ret == key);
            return ret;
        }

        friend std::ostream& operator<<(std::ostream& os, const Map& data) {
            for(auto& e : data.entries )
                os << e << std::endl;
            return os;
        }
};
using Map_t = struct Map;

struct Seed {
    private:
       Range_t _seed;
    public:
        Seed() = delete;
        Seed(size_t _start, size_t _length) : _seed{_start, _length} {}

        void get(std::vector<Map_t>& maps, std::vector<Range_t>& locs) {
            std::vector<Range_t> keys;
            std::vector<Range_t> values;

            keys.push_back(_seed);
            int i = 0;
            for( auto& map : maps ){
                for( auto& key : keys ){
                    map.get(values, key);
                }
                keys.clear();
                keys.insert(std::end(keys), std::begin(values), std::end(values));
                values.clear();
            }
            locs.insert(std::end(locs), std::begin(keys), std::end(keys));
        }

        void get(std::vector<Map_t>& maps, std::vector<size_t>& locs) {
            for( size_t key = _seed.start; key <= _seed.end; ++key ){
                size_t loc = key;
                for( auto& map : maps ){
                    loc = map[loc];
                }
                locs.push_back(loc);
            }
            return;
        }

        friend std::ostream& operator<<(std::ostream& os, const Seed& data) {
            os  << "Seed: " << data._seed;
            return os;
        }
};
using Seed_t = struct Seed;

void setup_maps(std::vector<Map_t>& maps, std::istream& input) {
    std::string line;
    size_t map_idx = -1;
    while( getline(input, line) ){
        if(line.empty()) continue;

        if( !isdigit(line[0]) ) {
            ++map_idx;
            continue;
        }

        std::stringstream s{line};
        size_t dst, src, range;
        s >> dst >> src >> range;
        maps[map_idx].add(src, dst, range);
    }
}

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
    setup_maps(maps, input);

    // need location per seed
    std::vector<size_t> locs;
    for( auto seed : seeds ) {
        size_t key = seed;
        for( auto& map : maps ){
            key = map[key];
        }
        locs.push_back(key);
    }
    size_t min = *std::min_element(std::begin(locs), std::end(locs));
    std::cout << "Min Location: " << min << std::endl;
}

void soln2(std::istream& input){
    std::string line;
    std::vector<Seed_t> seeds;

    getline(input, line);
    std::stringstream sds{line};

    sds >> line;
    size_t seed_s = 0; size_t seed_r = 0;
    while( sds >> seed_s >> seed_r ){ seeds.emplace_back(seed_s, seed_r); }

    std::vector<Map_t> maps(7);
    setup_maps(maps, input);

    std::vector<Range_t> locs;
    for( auto seed : seeds ) {
        seed.get(maps, locs);
    }

    size_t min = std::min_element(std::begin(locs), std::end(locs),
                [](const auto& a, const auto& b){ return a.start < b.start; })->start;
    std::cout << "\nMin Location: " << min << std::endl;
}

int main() {
    soln2(std::cin);
    return 0;
}