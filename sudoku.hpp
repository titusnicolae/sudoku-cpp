#include <iostream>
#include <vector>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <set>
#include <map>
#include "array.hpp"
#include <cassert>
using namespace std;

typedef Array<vector<int>, 3, 3> Square;
typedef Array<Square, 3, 3> Table;

//std::random_device rd;
std::mt19937 gen(0);//rd());
set<int> one_to_nine({1,2,3,4,5,6,7,8,9});

set<int> operator-=(set<int>& first, set<int> second){
  for(auto& e: second) {
    first.erase(e);
  }
  return first;
}

void print(set<int> s) {
  for(auto& e: s) {
    cout<<e<<" ";
  }
  cout<<endl;
}

class Sudoku {
  Table table;

 public:
  Sudoku(vector<vector<int>> v) {
    assert(v.size()==9); 
    for(auto& e: v) assert(e.size()==9);
    for(int l=0;l<9;l++) {
      for(int c=0;c<9;c++) {
        if(v[l][c]!=0) {
          table.at(l/3,c/3).at(l%3,c%3)={v[l][c]};
        }
      }
    }
  }

  Sudoku() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        table.at(i, j) = square(j * 3 + i + 1);
      }
    }
  }
  Square& at(int i, int j) { return table.at(i, j); }
  friend ostream& operator<<(ostream& stream, Sudoku& sudoku) {
    const int N = 35;
    Array<char, N, N> buffer(' ');
    for (int i: {0,1,2}) {
      for (int j: {0,1,2}) {
        for (int k: {0,1,2}) {
          for (int l: {0,1,2}) {
            for (int m = 0; m < sudoku.table.at(i, j).at(k, l).size(); m++) {
              buffer.at((i * 3 + k) * 4 + m / 3, (j * 3 + l) * 4 + m % 3) =
                  sudoku.table.at(i, j).at(k, l)[m] + '0';
            }
          }
        }
      }
    }

    for (int i = 0; i < 8; i++) {
      for (int k = 0; k < N; k++) {
        buffer.at(k, i * 4 + 3) = '|';
        buffer.at(i * 4 + 3, k) = '-';
      }
    }

    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        buffer.at(i * 4 + 3, j * 4 + 3) = '+';
      }
    }

    stream << buffer;
    return stream;
  }
  static void assert_different(int x, int y) {
    if (x == y) throw logic_error("equal");
  }

  void swap_block_line(int l1, int l2) {
    assert_different(l1, l2);
    for (auto& i : {0, 1, 2}) {
      swap(table.at(l1, i), table.at(l2, i));
    }
  }

  void swap_block_column(int c1, int c2) {
    assert_different(c1, c2);
    for (auto& i : {0, 1, 2}) {
      swap(table.at(i, c1), table.at(i, c2));
    }
  }

  void swap_line(int l1, int l2) {
    assert_different(l1, l2);
    for (int col = 0; col < 9; col++) {
      swap(table.at(l1 / 3, col / 3).at(l1 % 3, col % 3),
           table.at(l2 / 3, col / 3).at(l2 % 3, col % 3));
    }
  }

  void swap_column(int c1, int c2) {
    assert_different(c1, c2);
    for (int line = 0; line < 9; line++) {
      swap(table.at(line / 3, c1 / 3).at(line % 3, c1 % 3),
           table.at(line / 3, c2 / 3).at(line % 3, c2 % 3));
    }
  }
  static pair<int,int> random_pair(int start, int end) {
    int first, second;
    std::uniform_int_distribution<> random_op(start, end);
    first = random_op(gen);
    while((second=random_op(gen))==first);
    return make_pair(first, second);
  }

  void shuffle(int steps) {
    std::uniform_int_distribution<> random_op(0, 3);
    pair<int,int> temp;
    for(int i=0;i<steps;i++) {
      switch(random_op(gen)) {
        case 0: 
          temp=Sudoku::random_pair(0,2);
          swap_block_line(temp.first, temp.second);
        break;

        case 1: 
          temp=random_pair(0,2);
          swap_block_column(temp.first, temp.second);
        break;

        case 2: 
          temp=random_pair(0,8);
          swap_line(temp.first, temp.second);
        break;

        case 3: 
          temp=random_pair(0,8);
          swap_column(temp.first, temp.second);
        break;
      }
    }
  }
  void remove(int steps) {
    std::uniform_int_distribution<> r3(0, 2);
    for(int i=0;i<steps;i++) {
      for(int j=0;j<=100000;j++) {
        if(j==100000) throw logic_error("random");
        auto&v = table.at(r3(gen), r3(gen)).at(r3(gen), r3(gen));
        if(v.size()>0) {
          v.clear();
          break;
        }
      }
    } 
  }
  void remove_options() {
    for(int lb: {0,1,2})
      for(int cb: {0,1,2})
        for(int l: {0,1,2})
          for(int c: {0,1,2}) {
            auto& e = table.at(lb,cb).at(l,c);
            if(e.size()>1)
              e.clear();
          }
  }
  set<int> get_line(int l) {
    set<int> ret;
    for(int c=0;c<9;c++) {
      auto e = table.at(l/3,c/3).at(l%3,c%3); 
      if(e.size()==1) {
        ret.insert(e[0]); 
      }
    }
    return ret;
  }
  set<int> get_col(int c) {
    set<int> ret;
    for(int l=0;l<9;l++) {
      auto e = table.at(l/3,c/3).at(l%3,c%3); 
      if(e.size()==1) {
        ret.insert(e[0]); 
      }
    }
    return ret;
  }
  set<int> get_square(int line, int col) {
    set<int> ret;
    for(int i=0;i<9;i++) {
      auto e = table.at(line,col).at(i/3, i%3);
      if(e.size()==1) {
        ret.insert(e[0]);
      }
    }
    return ret;
  }
  void first_pass_restrictions() {
    for(int line = 0; line<9; line++) {
      for(int col = 0; col<9; col++) {
        auto& e = table.at(line/3, col/3).at(line%3, col%3);
        if(e.size()!=1) {
          set<int> s= one_to_nine;
          s-=get_line(line);
          s-=get_col(col);
          s-=get_square(line/3, col/3);
          std::copy(s.begin(), s.end(), std::back_inserter(e));
        }  
      }
    }
  }
  void unique_in_square() {
    for(int lb: {0,1,2}) {
      for(int cb: {0,1,2}) {
        map<int, vector<pair<int,int>>> m;  
        for(int l: {0,1,2}) {
          for(int c: {0,1,2}) {
            for(int e: table.at(lb,cb).at(l,c)) {
              m[e].push_back(make_pair(l, c));
            } 
          }
        }
        for(auto& e: m) {
          if(e.second.size()==1) {
            table.at(lb,cb).at(e.second[0].first, e.second[0].second) = vector<int> {e.first};
          }
        }
      } 
    } 
  }
  void recompute_restrictions() {
    remove_options();   
    first_pass_restrictions();
    unique_in_square();
  }
  bool operator!=(Sudoku& s) {
    return not (*this==s);
  }
  bool operator==(Sudoku& s) {
    for(int l = 0;l<9;l++) {
      for(int c = 0;c<9;c++) {
        if(table.at(l/3,c/3).at(l%3,c%3) != s.at(l/3,c/3).at(l%3,c%3)) {
          return false; 
        }  
      }
    }
    return true;
  }
  bool is_valid() {
    for(int lb: {0,1,2})for(int cb: {0,1,2})for(int l: {0,1,2})for(int c: {0,1,2}){
      auto& e= table.at(lb, cb).at(l, c);
      if(e.size()!=1) {
        return false;
      }
    } 
    for(int i=0;i<9;i++) {
      if(get_line(i)!=one_to_nine){
        return false;
      }
      if(get_col(i)!=one_to_nine){
        return false;
      }
    }
    for(int l: {0,1,2}) {
      for(int c: {0,1,2}) {
        if(get_square(l,c)!=one_to_nine){
          return false;
        }
      }
    }
    return true;
  }
   
private:
  Square square(int offset = 1) {
    if (offset < 1 or offset > 9) {
      throw logic_error("square assert fail");
    }

    Square ret;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        ret.at(i, j).push_back((offset - 1) % 9 + 1);
        offset = offset % 9 + 1;
      }
    }
    return ret;
  }
};
