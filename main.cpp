#include "sudoku.hpp"

int main() {
  Sudoku s({{5,9,0,4,1,0,0,0,0},
            {4,0,0,0,0,0,0,0,6},
            {0,0,0,0,5,9,0,0,0},
            {0,7,5,9,0,1,0,4,0},
            {8,1,0,0,0,0,0,0,5},
            {9,0,0,0,0,3,8,0,2},
            {0,0,0,0,0,0,1,0,0},
            {0,0,2,0,0,6,0,0,0},
            {0,0,9,0,0,2,7,0,0}});
  Sudoku prev;
  int i;
  for(i=0;s!=prev;i++) {
    prev = s;
    s.recompute_restrictions();
  }
  s.remove_options();
  cout<<s.is_valid();
  return 0;
}
