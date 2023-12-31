#include <iostream>
#include <bits/stdc++.h>

using Row_t = std::vector<char>;
using Grid_t = std::vector<Row_t>;

std::ostream& operator<<(std::ostream& os, const Row_t& row){
    for(auto n : row)
        os << n;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Grid_t& grid){
    os << "Grid(" << grid.size() << "x" << grid[0].size() << "):\n";
    int i = 0;
    for(auto r : grid){
        os << i++ << r << std::endl;
    }
    return os;
}

bool operator==(const Row_t& a, const Row_t& b){
    int size = a.size();
    for( int i = 0; i < size; ++i ){
        if( a[i] != b[i] ) return false;
    }
    return true;
}

int has_reflection(Grid_t& grid){

    std::vector<int> refl(grid.size(), -1);
    for(int i = 0; i < grid.size()-1; ++i ){
        for( int j = i+1; j < grid.size(); ++j ){
            if(grid[i] == grid[j]){
                refl[i] = j; refl[j] = i;
                break;
            }
        }
    }

    // ensure one end is mirrored
    if(refl.front() < 0 && refl.back() < 0) return 0;

    for(int i = 0; i < refl.size(); ++i){
        std::cout << i << "> " << refl[i] << std::endl;
    }

    for( int i = 0; i < refl.size() -1; ++i ){
        if( refl[i] == i+1 ){
            std::cout << "Reflection between " << refl[i] << " & " << refl[i+1] << std::endl;
            return std::max(refl[i], refl[i+1]);
        }
    }
    return 0;
}

bool edge_reflected(Grid_t& grid, int a, int b){
    Row_t edge = grid[0];
    auto find = std::find_if(
        std::begin(grid)+b, std::end(grid),
        [edge](const Row_t& row){ return row == edge; }
    );
    if( find != std::end(grid) ) return true;

    // check for bottom edge
    edge = grid.back();
    find = std::find_if(
        std::begin(grid)+b, std::end(grid),
        [edge](const Row_t& row){ return row == edge; }
    );
    if( find != std::end(grid) ) return true;
    return false;
}

int has_reflection2(Grid_t& grid){
    int a = -1; int b = -1;
    for( int i = 0; i < grid.size()-1; ++i ){
        if(grid[i] == grid[i+1]){
            a = i; b = i+1;
            // NOTE: might be multiple of these occurances
            /*

            */
            break;
        }
    }
    std::cout << "a: " << a << " b: " << b << std::endl;
    if( a < 0 ) return 0;
    // check 0 and size-1 idx for match via distance refl line
    auto it = grid.front();
    std::cout   << "\n"
                << "[" << std::distance(std::begin(grid), std::begin(grid)+b)
                << ", " << std::distance(std::begin(grid), std::end(grid))
                << "]\n"
                << "[" << std::distance(std::begin(grid), std::begin(grid))
                << ", " << std::distance(std::begin(grid), std::begin(grid)+a)
                << "]\n";

    std::cout << "Looking for: " << it << std::endl;

    auto find = std::find_if(
        std::begin(grid)+b, std::end(grid),
        [it](const Row_t& row){ return row == it; }
    );
    if( find == std::end(grid) ){
        it = grid.back();
        std::cout << "Looking for: " << it << std::endl;
        find = std::find_if(
            std::begin(grid), std::begin(grid)+a,
            [it](const Row_t& row){ return row == it; }
        );
    }
    if( find == std::end(grid) ) return 0;
    else { std::cout << std::distance(std::begin(grid), find) << std::endl; }
    return b;
}
void transpose(Grid_t& grid){
    Grid_t copy( grid[0].size(), Row_t(grid.size(), '.'));
    // std::cout << "Copy:\n" << copy;
    int rows = grid.size();
    int cols = grid[0].size();
    for( int i = 0; i < rows; ++i ){
        for( int j = 0; j < cols; j++ ){
            copy[j][i] = grid[i][j];
        }
    }
    grid.clear();
    grid = copy;
}

void soln(std::istream& input){
    std::string line;
    std::vector<Grid_t> patterns;

    Grid_t grid;
    while( getline(input, line) ){
        if( line == "" ){
            patterns.push_back( grid );
            grid.clear();
            continue;
        }

        std::istringstream s{line};
        Row_t row;
        char c;
        while( s >> c ){
            row.push_back(c);
        }
        grid.push_back(row);
    }
    patterns.push_back(grid);

    // for(auto& grid : patterns){
    //     std::cout << "Pattern:\n" << grid << std::endl;
    //     for(int i = 0; i < grid.size()-1; ++i){
    //         Row_t a = grid[i];
    //         Row_t b = grid[i+1];
    //         if(a == b){
    //             std::cout << "Hline between: " << i << ", " << i+1 << std::endl;
    //             // NOTE: horz vs vert via if row/col in pattern is touching an edge
    //             // horz: can check by dist to top and bottom and check if theres a pattern
    //             // if none exist for horz then check for vert( transpose and use horz)

    //             // 0 vs i + (i+1)
    //             // NOTE:
    //             // index array for each row, row position gets -1 if no mathing row
    //             // or the matching rows idx
    //             // if the ends have a non -1 value then have a line in teh current orientation
    //             // the reflection line is between 2 consecutive numbers
    //             // filling the array is n^2 per grid

    //             // edge check version:
    //             // 0
    //             Row_t edge = grid[0];
    //             int distance = i + 1;
    //             Row_t refl = grid[i + distance];
    //             if( edge == refl ){
    //                 // done
    //             } else {
    //                 // check bottom edge
    //                 edge = grid.back();
    //                 distance = grid.size() - 1 - i;

    //             }
    //             /*
    //                 0
    //                 1
    //                  <-------- i - 0 + 1 = 2
    //                 2
    //                 3
    //                 4


    //             */
    //         }
    //     }
    // }
    int rows = 0; int cols = 0;
    for( auto& grid: patterns){
        // int r = has_reflection(grid);
        // std::cout   << grid
        //             << "Refl? " << ((r>0)? "T":"F")
        //             << " Size: " << r
        //             << std::endl;

        // std::cout << grid;
        // transpose(grid);
        std::cout << grid;
        int r = has_reflection2(grid);
        if( r > 0) rows += r;
        else {
            transpose(grid); std::cout << grid;
            cols += has_reflection2(grid);
        }
        std::cout << ((r > 0)? "Horizontal":"Vertical") << std::endl;
    }
    std::cout << "Rows: " << rows << " Cols: " << cols << std::endl;
    std::cout << "Total: " << cols+rows*100 << std::endl;
}

void soln2(std::istream& input){

}

int main() {
    soln(std::cin);
    return 0;
}