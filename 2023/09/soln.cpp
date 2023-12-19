#include <iostream>
#include <bits/stdc++.h>

using row_t = std::vector<int>;
using table_t = std::vector<row_t>;

bool allZero(row_t& row){
    for(auto& r : row)
        if( r != 0) return false;
    return true;
}

void diff_pyr(std::vector<int>& row, table_t& table) {
    table.push_back(row);
    int idx = 0;
    bool Z = false;
    do{
        row_t& cur_row = table[idx];
        row_t diff;
        int size = cur_row.size();

        for( int i = 1; i < size; ++i ){
            diff.push_back( cur_row[i] - cur_row[i-1] );
        }
        table.push_back( diff );
        idx++;
        Z = allZero(diff);
    } while( !Z );
}

int predict(table_t& mat, int idx){
    row_t top = mat[idx];
    if(allZero(top)) return 0;

    return top.back() + predict(mat, ++idx);
}

int predict_r(table_t& mat, int idx){
    row_t top = mat[idx];
    if( allZero(top) ) return 0;

    return top.front() - predict_r(mat, ++idx);
}

void solve(std::istream& input, auto& pred_fun){
    table_t in_table;
    std::string line;
    while( getline(input, line) ){
        std::istringstream s{line};
        std::vector<int> row;
        int value;
        while( s >> value ) row.push_back(value);
        in_table.push_back(row);
    }

    int total = 0;
    for(auto& table: in_table ){
        table_t pyr;
        diff_pyr(table, pyr);
        total += pred_fun(pyr, 0);
    }
    std::cout << "Total: " << total << std::endl;
}

void soln(std::istream& input) { solve(input, predict); }

void soln2(std::istream& input){ solve(input, predict_r); }

int main() {
    soln2(std::cin);
    return 0;
}