#include <iostream>
#include <bits/stdc++.h>

const std::string Colour[4] = {
        "\033[0;34m",   // Blue
        "\033[0;37m",   // White
        "\033[0m"       // reset
};

struct Cell {
    public:
    char c;
    bool galaxy;

    Cell() = delete;
    Cell(char _c): c{_c}, galaxy{_c == '#'} {}

    friend std::ostream& operator<<(std::ostream& os, const Cell& data){
        os << Colour[data.galaxy] <<  data.c << Colour[2];
        return os;
    }
};
using Cell_t = struct Cell;
using Row_t = std::vector<Cell_t>;
using Coors_t = std::pair<uint64_t, uint64_t>;

struct Grid {
    private:
        std::vector<Row_t> _data;
    public:
        Grid(): _data{} {}

        uint64_t rows() { return _data.size(); }
        uint64_t cols() { return _data[0].size(); }

        void push_back(Row_t& row) {
           _data.push_back(row);
        }

        void empty_rows(std::vector<uint64_t>& rows){
            for(uint64_t i = 0; i < _data.size(); ++i){
                auto it = std::find_if(std::begin(_data[i]), std::end(_data[i]),
                                        [](const Cell_t& c){ return c.c == '#'; });
                if(it == std::end(_data[i]))
                    rows.push_back(i);
            }
        }

        void empty_cols(std::vector<uint64_t>& cols){
            uint64_t row = 0;
            uint64_t size = _data[row].size();
            for( uint64_t col = 0; col < size; ++col ){
                if( _data[row][col].c == '.' ){
                    auto it = std::find_if(std::begin(_data), std::end(_data),
                                        [col](const Row_t& row)-> bool {
                                            return row[col].c == '#'; });

                    if( it == std::end(_data) ){ cols.push_back(col); }
                }
            }
        }

        void find_galaxies(std::vector<Coors_t>& galaxies){
            for(uint64_t i = 0; i < _data.size(); ++i){
                for(uint64_t j = 0; j < _data[i].size(); ++j){
                    if(_data[i][j].galaxy)
                        galaxies.emplace_back(i, j);
                }
            }
        }

        Row_t& operator[](const size_t idx){
            return _data[idx];
        }

        Cell_t& operator[](const Coors_t coor ){
            return _data[coor.first][coor.second];
        }

        friend std::ostream& operator<<(std::ostream& os, const Grid& data){
            auto _grid = data._data;
            os << "Grid(" << _grid.size() << "x" << _grid[0].size() << "):\n";

            os << std::setw(3) << "---";
            for(uint64_t i = 0; i < _grid[0].size(); ++i)
                os << i;
            os << std::endl;

            uint64_t row = 0;
            for( auto& r: _grid) {
                os << std::setw(3) << row++;
                for(auto& cell : r){ os << cell; }
                os << std::endl;
            }
            return os;
        }
};
using Grid_t = struct Grid;

void setup_grid(std::istream& input, Grid_t& grid){
    std::string line;
    uint64_t r = 0;
    while( getline(input, line) ){
        std::istringstream s{line};
        Row_t row; char c; uint64_t col = 0;
        while( s >> c ){
            row.emplace_back(c);
            col++;
        }
        grid.push_back(row);
        r++;
    }
}

uint64_t manhattan_dist(Coors_t a, Coors_t b){
    return abs(a.first - b.first) + abs(a.second - b.second);
}

void galaxy_drift(std::vector<Coors_t>& g,
                  std::vector<uint64_t>& idxes,
                  bool row, uint64_t drift){

    if(drift > 1) drift--;
    for(uint64_t i = 0; i < idxes.size(); ++i){
        std::transform(
            std::begin(g), std::end(g), std::begin(g),
            [i, drift, row, &idxes](Coors_t& g){
                uint64_t idx = (i == 0)? idxes[i] : idxes[i] + i*drift;
                if(row){
                    if( g.first > idx )
                        g.first += drift;
                } else {
                    if( g.second > idx )
                        g.second += drift;
                }
                return g;
            }
        );
    }
}


void solve(std::istream& input, uint64_t DRIFT){
    Grid_t grid;
    std::vector<Coors_t> galaxies;

    setup_grid(input, grid);
    grid.find_galaxies(galaxies);
    std::cout << grid;

    std::vector<uint64_t> rows, cols;
    grid.empty_rows(rows);
    grid.empty_cols(cols);

    galaxy_drift(galaxies, rows, true, DRIFT);
    galaxy_drift(galaxies, cols, false, DRIFT);

    uint64_t total = 0;
    uint64_t size = galaxies.size();
    std::cout << "Num Galaxies: " << size << std::endl;
    for(uint64_t i = 0; i < size; ++i){
        for(uint64_t j = i+1; j < size; ++j){
            uint64_t d = manhattan_dist( galaxies[i], galaxies[j] );
            total += d;
        }
    }
    std::cout << "Total: " << total << std::endl;
}

void soln(std::istream& input){
    solve(input, 1);
}

void soln2(std::istream& input){
    solve(input, 1000000);
}

int main() {
    soln2(std::cin);
    return 0;
}