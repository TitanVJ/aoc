#include <iostream>
#include <bits/stdc++.h>

std::unordered_map<char, size_t> m_card = {{'A', 14}, {'K', 13}, {'Q', 12},
                                        {'J', 11}, {'T', 10} };

std::array<std::string, 7> Type_names = {"HIGH_CARD", "ONE_P", "TWO_P",
                                         "THREE_K", "FULL_HS", "FOUR_K", "FIVE_K"};

std::array<char, 13> Face_val = {'2', '3', '4', '5', '6', '7', '8', '9',
                                 'T', 'J', 'Q', 'K', 'A'};
std::array<char, 13> Face_val2 = {'J', '2', '3', '4', '5', '6', '7', '8', '9',
                                 'T', 'Q', 'K', 'A'};

struct Hand {
    private:
        std::string label;
        size_t type;

    void set_type() {
        std::unordered_map<char, size_t> count;
        for( char c : label ){ count[c]++; }

        // adjust based on J
        if( count.find('J') != std::end(count) && count['J'] < 5 ){
            size_t add = count['J']; count.erase('J');
            auto max = std::max_element(
                std::begin(count),
                std::end(count),
                [](const auto& a, const auto& b){
                    return a.second < b.second;
                });
                count[max->first] += add;
        }
        size_t size = count.size();
        size_t max = std::max_element(  count.begin(), count.end(),
                                        [](const auto& a, const auto& b){
                                            return a.second < b.second;})->second;
        if( size == 5 ){ // max 1
            type = 0;
        } else if( size == 4 ){ // max 2
            type = 1;
        } else if( size == 3 ){
            type = max;
        } else if( size == 2 ){
            type = (max==3)? 4:5;
        } else{
            type = 6;
        }
    }

    public:
        size_t bid;
        Hand() = delete;
        Hand(std::string _label, size_t _bid) :label{_label}, bid{_bid} { set_type(); }

        friend bool operator<(const Hand& a, const Hand& b) {
            if( a.type != b.type ){ return a.type < b.type; }

            // compare chars of labels
            for( int i = 0; i < 5; ++i ){
                if( a.label[i] == b.label[i] ) continue;

                int aval = std::distance(std::begin(Face_val2),
                                         std::find(std::begin(Face_val2),
                                                   std::end(Face_val2), a.label[i]));
                int bval = std::distance(std::begin(Face_val2),
                                         std::find(std::begin(Face_val2),
                                                   std::end(Face_val2), b.label[i] ));
                return aval < bval;
            }
            return true;
        }

        friend std::ostream& operator<<(std::ostream& os, const Hand& data) {
            os << std::setw(5) << data.label << " " << Type_names[data.type];
            os << " [" << data.type << "] ";
            return os;
        }
};
using Hand_t = struct Hand;

void soln(std::istream& input){
    std::string label;
    size_t bid;
    std::vector<Hand_t> hands;
    while( input >> label >> bid ){
        hands.emplace_back(label, bid);
    }
    std::sort(std::begin(hands), std::end(hands));
    // int i = 1;
    // for(auto h: hands) std::cout << i++ << " " << h << std::endl;

    size_t total = 0;
    for( int i = 0; i < hands.size(); ++i ) {
        total += hands[i].bid * (i+1);
    }
    std::cout << "Total: " << total << std::endl;
}

void soln2(std::istream& input){
    // adjusted hand_t to fit part 2 and ran part 1 soln
}

int main() {
    soln(std::cin);
    return 0;
}