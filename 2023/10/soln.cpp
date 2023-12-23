#include <iostream>
#include <bits/stdc++.h>


// NOTE: Only move in 4 dirctions
enum Dir { UP=0, RIGHT, DOWN, LEFT };

std::unordered_map<char, std::pair<Dir, Dir>> pipe_map {
    {'|', { UP, DOWN }},
    {'-', { RIGHT, LEFT }},
    {'L', { UP, RIGHT }},
    {'J', { UP, LEFT }},
    {'7', { DOWN, LEFT }},
    {'F', { RIGHT, DOWN }}
};

std::unordered_map<Dir, std::vector<char>> dir_pipe_map {
    { UP, {'|', '7', 'F'}},
    { RIGHT, {'-', 'J', '7'}},
    { DOWN, {'|', 'L', 'J'}},
    { LEFT, {'-', 'L', 'F'}}
};

struct Tile {
    public:
        const char pipe;
        bool visited;
        int colour = -1;
        Tile() = delete;
        Tile( char _pipe ): pipe{_pipe}, visited{false} {}

        friend std::ostream& operator<<(std::ostream& os, const Tile& tile){
            os << tile.pipe;
            return os;
        }
};
using tile_t = struct Tile;
using Row_t = std::vector<tile_t>;
using Grid_t = std::vector<Row_t>;
using coors_t = std::pair<size_t, size_t>;
constexpr coors_t offsets[4] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

void print_g(Grid_t& grid){
    std::cout << "Grid(" << grid.size() << "x" << grid[0].size() << "):\n";
    size_t rows = grid.size();
    size_t cols = grid[0].size();
    int i = 0;
    for( auto& r: grid) {
        std::cout << i++;
        for(auto& cell : r){ std::cout << cell; }
        std::cout << std::endl;
    }
}

bool compat(Dir src, tile_t dst){
    std::vector<char> supp = dir_pipe_map[ src ];
    return std::find_if(supp.begin(), supp.end(),
                        [dst](const auto& d){ return d == dst.pipe; }) != supp.end();
}

void setup_grid(std::istream& input, Grid_t& grid, std::pair<size_t, size_t>& start){
    std::string line;
    size_t i = 0;
    while( getline(input, line) ){
        Row_t row; i++;
        int j = 0;
        for( char c : line ){
            j++;
            if(c == 'S'){ start = { i-1, j-1 }; }
            row.emplace_back(c);
        }
        grid.push_back( row );
    }
}

void walk_path(Grid_t& grid, std::vector<size_t>& dists, std::pair<size_t, size_t> start){
    size_t r = start.first;
    size_t c = start.second;
    size_t walk = 0;
    while( !grid[r][c].visited ) {
        // std::cout << "Visiting: " << r << ", " << c << std::endl;
        tile_t& curr = grid[r][c];
        curr.visited = true;
        curr.colour = 1;
        dists.push_back( ++walk );

        std::pair<Dir, Dir> outs;
        if( curr.pipe == 'S' ){
            std::vector<Dir> dir_list = {UP, RIGHT, DOWN, LEFT};
            auto n_it = std::find_if(
                std::begin(dir_list), std::end(dir_list),
                [&grid, r, c] (const Dir& data) -> bool {
                    coors_t off = offsets[data];
                    return compat(data, grid[r+off.first][c+off.second]);
                    });
            outs = std::make_pair(*n_it, *n_it);
        } else {
            outs = pipe_map[ curr.pipe ];
        }

        coors_t offset = offsets[ outs.first ];
        if( grid[ r + offset.first ][ c + offset.second ].visited ){
            // visit second
            offset = offsets[ outs.second ];
        }

        // update curr coors
        r += offset.first;
        c += offset.second;
    }
}

void flood_fill(Grid_t& grid, std::pair<size_t, size_t> start) {

     // how to know
     return;
}

void soln(std::istream& input){
    Grid_t grid;
    std::pair<size_t, size_t> start;
    std::vector<size_t> dists;

    setup_grid(input, grid, start);
    walk_path(grid, dists, start);

    size_t max = 0;
    auto fr = dists.begin();
    auto bk = dists.rbegin();
    while( fr != dists.end() && bk != dists.rend() ){
        max = std::max( max, std::min( *fr, *bk ));
        ++fr; ++bk;
    }
    std::cout << "Max: " << max << std::endl;
    std::cout << "\033[1;31mbold red text\033[0m\n";
}

void soln2(std::istream& input){
    Grid_t grid;
    std::pair<size_t, size_t> start;
    std::vector<size_t> dists;

    setup_grid(input, grid, start);
    walk_path(grid, dists, start);

    // flood fill

}

int main() {
    soln(std::cin);
    return 0;
}