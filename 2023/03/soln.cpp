#include <iostream>
#include <bits/stdc++.h>

struct Cell {
    private:
        int num;
    public:
        const bool Symbol;
        Cell(int n): num{n}, Symbol{false} {}
        Cell(bool symbol): num{0}, Symbol{symbol} {}
        int value() { int r = num; num = 0; return r; }
};
using Cell_t    = struct Cell;
using Row_t     = std::vector<std::shared_ptr<Cell_t>>;
using Grid_t    = std::vector<Row_t>;
using Coors_t   = std::array<std::pair<int, int>, 8>;

Coors_t eight(int r, int c){
    int up = r-1; int down = r+1;
    int left = c-1; int right = c+1;
    return { std::make_pair(up, left), std::make_pair(up, c), std::make_pair(up, right),
             std::make_pair(r, left), std::make_pair(r, right),
             std::make_pair(down, left), std::make_pair(down, c), std::make_pair(down, right)
            };
}

int window_sum(Grid_t& grid, int r, int c) {
    Coors_t coors = eight(r, c);
    return std::accumulate(std::begin(coors), std::end(coors), 0,
                            [grid](const auto& lhs, const auto& rhs) {
                                return lhs + grid[rhs.first][rhs.second]->value();
                            });
}

int gear_ratio(Grid_t& grid, int r, int c){
    Coors_t coors = eight(r, c);

    // {num count, product of nums}
    std::pair<int, int> ret = std::accumulate( std::begin(coors), std::end(coors), std::make_pair(0, 1),
                                 [grid](const std::pair<int, int>& lhs, const auto& rhs){
                                     int value = grid[rhs.first][rhs.second]->value();
                                    return (value > 0)? std::make_pair(lhs.first +1, lhs.second * value) : lhs;
                                 });

    return (ret.first == 2)? ret.second : 0;
}


// NOTE: separate pass 1 to create grid fix the colour
void set_grid(Grid_t& grid, std::istream& input, std::function<bool(const char)> pred) {
    std::string line;
    while( input >> line ){
        size_t nCols = line.length();
        Row_t row; row.reserve( nCols + 2 );
        for( size_t i = 0; i < nCols; ++i ){
            if( isdigit(line[i]) ){
                // want to absorb the remaining digits to create one
                auto it = std::begin(line) + i;
                auto end_it = std::find_if( it,
                                            std::end(line),
                                            [](const auto& v){ return !isdigit(v); });

                int length = std::distance(it, end_it);
                int num = std::stoi(line.substr(i, length));
                std::fill_n( std::back_inserter(row), length, std::make_shared<Cell_t>(num) );

                // Update i past num, -1 => loop inc
                i += length - 1;

            } else {
                row.push_back( std::make_shared<Cell_t>( pred(line[i]) ) );
            }
        }
        // 0 padding
        row.insert(std::begin(row), std::make_shared<Cell_t>(0) );
        row.push_back( std::make_shared<Cell_t>(0) );
        grid.push_back( row );
    }
    // 0 padding
    std::vector<std::shared_ptr<Cell_t>> vec(grid[0].size(), std::make_shared<Cell_t>(false));
    grid.insert(std::begin(grid), vec);
    grid.push_back(vec);
}

void soln_prime(std::istream& input,
                std::function<bool(const char)> pred,
                std::function<int(Grid_t&, int, int)> calc){
     Grid_t grid;
    set_grid(grid, input, pred);

    int total = 0;
    for( int r = 1; r < grid.size() - 1; ++r ){
        for( int c = 1; c < grid[0].size()-1; ++c ){
            if(grid[r][c]->Symbol)
                // total += window_sum(grid, r, c);
                total += calc(grid, r, c);
        }
    }
    std::cout << "Total: " << total << std::endl;

}
void soln(std::istream& input){
    soln_prime(input, [](const char c){ return c != '.'; }, window_sum);
}

void soln2(std::istream& input){
    soln_prime(input, [](const char c){ return c == '*'; }, gear_ratio);
}

int main() {
    soln2(std::cin);
    return 0;
}