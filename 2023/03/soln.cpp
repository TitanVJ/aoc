#include <iostream>
#include <bits/stdc++.h>

enum Content { NUMBER, SYMBOL, DOT };
using content_t = enum Content;

// struct Cell {
//     private:
//         int num;
//         bool _visited;
//         content_t _content;
//     public:
//         Cell(content_t c): num{-1}, _visited{false}, _content{c} {}
//         Cell(content_t c, int n): num{n}, _visited{false}, _content{c} {}

//         content_t content() { return _content; }
//         int value() {
//             if( _visited ){
//                 _visited = true;
//                 return num;
//             }
//             return 0;
//         }
// };
struct Cell {
    private:
        int num;
    public:
        const bool Symbol;
        Cell(int n): num{n}, Symbol{false} {}
        Cell(bool symbol): num{0}, Symbol{symbol} {}
        int value() { int r = num; num = 0; return r; }
};
using Cell_t = struct Cell;
using Row_t = std::vector<std::shared_ptr<Cell_t>>;
using Grid_t = std::vector<Row_t>;

// int window_sum(std::vector<std::shared_ptr<Cell_t>>& A, int R, int C, int idx) {}
// int window_sum(Grid_t& grid, int r, int c) { }

// NOTE: separate pass 1 to create grid fix the colour
// void gen_grid(Grid_t& grid, std::istream& input){}

void soln(std::istream& input){

    std::string line;
    Grid_t grid;

    while( input >> line ){
        size_t nCols = line.length();
        Row_t row; row.reserve( nCols + 2 );

        // row.push_back( std::make_shared<Cell_t>(0) );

        std::cout << line << " [";
        for( size_t i = 0; i < nCols; ++i ){
            if( isdigit(line[i]) ){
                // want to absorb the remaining digits to create one
                auto it = std::begin(line) + i;
                auto end_it = std::find_if( it,
                                            std::end(line),
                                            [](const auto& v){ return !isdigit(v); });

                int length = std::distance(it, end_it);
                int num = std::stoi(line.substr(i, length));
                std::cout << num << ", ";
                // std::cout   << line << "\nC: " << line[i] << ": len=" << length << " num=" << num
                //             << " i=" << i << " ++i=" << i+length << std::endl;
                // TODO: 2d -> 1d coordinates
                // row = floor( x / rows )
                // col = x % cols -1
                // auto ptr = std::make_shared<Cell_t>(num);
                // for( auto i = 0; i < length; ++i)
                //     row.push_back(ptr);
                std::fill_n( std::back_inserter(row), length, std::make_shared<Cell_t>(num) );

                // Update i past num, -1 => loop inc
                i += length - 1;

            } else {
                row.push_back( std::make_shared<Cell_t>(line[i] != '.') );
            }
        }
        row.insert(std::begin(row), std::make_shared<Cell_t>(0) );
        row.push_back( std::make_shared<Cell_t>(0) );

        std::cout << "]" << std::endl << row.size() << std::endl;
        for( auto& cell : row ){
            std::cout << cell->value() << " ";
            // std::cout << "Symbol? " << ( (cell->Symbol)? "T" : "F" ) << " Num: " << cell->value() << std::endl;
        }
        std::cout << std::endl << "---------------------\n";
        grid.push_back( row );
    }
    std::vector<std::shared_ptr<Cell_t>> vec(grid[0].size(), std::make_shared<Cell_t>(false));
    grid.insert(std::begin(grid), vec);
    grid.push_back(vec);

    // print the 2d array
    // grid.push_back( &std::vector<Cell_t>(grid[0].size(), std::make_shared<Cell_t>(false)) );
}

void soln2(std::istream& input){

}

int main() {
    soln(std::cin);
    return 0;
}