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

const std::string Colour[4] = {
        "\033[0;44m",   // Blue bg
        "\033[0;47m",   // While bg
        "\033[0;41m",   // Red bg
        "\033[0m"       // reset
};

struct Tile {
    public:
        const char pipe;
        bool visited;
        int colour = 0;
        Tile() = delete;
        Tile( char _pipe ): pipe{_pipe}, visited{false} {}

        friend std::ostream& operator<<(std::ostream& os, const Tile& tile){
            // TODO: add colours https://stackoverflow.com/a/2616912
            // os << tile.pipe;
            os  << Colour[ tile.colour ] << tile.pipe << Colour[3];
            return os;
        }
};
using tile_t = struct Tile;
using Row_t = std::vector<tile_t>;
using Grid_t = std::vector<Row_t>;
using coors_t = std::pair<int, int>;
constexpr coors_t offsets[4] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

void print_g(Grid_t& grid){
    std::cout << "Grid(" << grid.size() << "x" << grid[0].size() << "):\n";
    int rows = grid.size();
    int cols = grid[0].size();
    int i = 0;
    for( auto& r: grid) {
        // std::cout << i++;
        for(auto& cell : r){ std::cout << cell; }
        std::cout << std::endl;
    }
}

bool compat(Dir src, tile_t dst){
    std::vector<char> supp = dir_pipe_map[ src ];
    return std::find_if(supp.begin(), supp.end(),
                        [dst](const auto& d){ return d == dst.pipe; }) != supp.end();
}

void setup_grid(std::istream& input, Grid_t& grid, coors_t& start){
    std::string line;
    int i = 0;
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

void walk_path(Grid_t& grid, std::vector<int>& dists,
               std::vector<coors_t>* path, coors_t start){
    int r = start.first;
    int c = start.second;
    int walk = 0;
    while( !grid[r][c].visited ) {
        // std::cout << "Visiting: " << r << ", " << c << std::endl;
        tile_t& curr = grid[r][c];
        curr.visited = true;
        curr.colour = 1;
        dists.push_back( ++walk );
        if( path != nullptr ) path->emplace_back(r, c);

        std::pair<Dir, Dir> outs;
        if( curr.pipe == 'S' ){
            curr.colour = 2;
            std::vector<Dir> dir_list = {UP, RIGHT, DOWN, LEFT};
            if( r == 0) dir_list.erase(dir_list.begin());
            if( c == grid[0].size() - 1) {
                dir_list.erase( std::find(dir_list.begin(), dir_list.end(), RIGHT) );
            }
            if( r == grid.size() - 1 ) {
                dir_list.erase( std::find(dir_list.begin(), dir_list.end(), DOWN) );
            }
            if( c == 0) {
                dir_list.erase( std::find(dir_list.begin(), dir_list.end(), LEFT) );
            }
            auto n_it = std::find_if(
                std::begin(dir_list), std::end(dir_list),
                [&grid, r, c] (const Dir& data) -> bool {
                    coors_t off = offsets[data];
                    // TODO: check edge conditions
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

int get_area(std::vector<coors_t>& path){
    // shoelace formula
    path.emplace_back(path.front().first, path.front().second);
    int size = path.size() - 1;
    int sum = 0;
    for( int i = 0; i < size; ++i ){
        int delta_x = path[i].first - path[i+1].first;
        int delta_y = path[i].second + path[i+1].second;
        sum += delta_x * delta_y;
    }
    return abs(sum) * 0.5 ;
}

void soln(std::istream& input){
    Grid_t grid;
    coors_t start;
    std::vector<int> dists;

    setup_grid(input, grid, start);
    walk_path(grid, dists, nullptr, start);

    int max = 0;
    auto fr = dists.begin();
    auto bk = dists.rbegin();
    while( fr != dists.end() && bk != dists.rend() ){
        max = std::max( max, std::min( *fr, *bk ));
        ++fr; ++bk;
    }
    std::cout << "Max: " << max << std::endl;
    print_g(grid);
}

void soln2(std::istream& input){
    Grid_t grid;
    coors_t start;
    std::vector<int> dists;
    std::vector<coors_t> path;

    setup_grid(input, grid, start);
    walk_path(grid, dists, &path, start);
    print_g(grid);
    int area = get_area(path);

    // Picks formula: A = i + b/2 - 1; i: interior pts b: perimeter
    int inside = area - (path.size()-1)/2 + 1;
    std::cout << "Inside: " << inside << std::endl;
}

int main() {
    soln2(std::cin);
    return 0;
}