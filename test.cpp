#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "sudoku.hpp"
#include <iostream>
using namespace std;

TEST_CASE("swap block line", "[swap]") {
  Sudoku s1, s2;
  s1.swap_block_line(0, 1);
  for (int cb : {0, 1, 2}) {
    for (int l : {0, 1, 2}) {
      for (int c : {0, 1, 2}) {
        REQUIRE(s1.at(0, cb).at(l, c) == s2.at(1, cb).at(l, c));
        REQUIRE(s1.at(2, cb).at(l, c) == s2.at(2, cb).at(l, c));
      }
    }
  }
}

TEST_CASE("swap block column", "[swap]") {
  Sudoku s1, s2;
  s1.swap_block_column(0, 1);
  for (int lb : {0, 1, 2}) {
    for (int l : {0, 1, 2}) {
      for (int c : {0, 1, 2}) {
        REQUIRE(s1.at(lb, 0).at(l, c) == s2.at(lb, 1).at(l, c));
        REQUIRE(s1.at(lb, 2).at(l, c) == s2.at(lb, 2).at(l, c));
      }
    }
  }
}

TEST_CASE("swap column", "[swap]") {
  Sudoku s1, s2;
  s1.swap_column(0, 1);
  for (int line = 0; line < 9; line++) {
    REQUIRE(s1.at(line / 3, 0).at(line % 3, 0) ==
            s2.at(line / 3, 0).at(line % 3, 1));
  }
}

void clear_except_first_square(Sudoku& s) {
  for(int line=0;line<9;line++) {
    for(int col=0;col<9;col++) {
      if(line<3 and col<3) continue;
      s.at(line/3, col/3).at(line%3, col%3).clear();
    }
  } 
}

TEST_CASE("get line", "[region]") {
  Sudoku s1;
  clear_except_first_square(s1);
  for(int x: s1.get_line(0)) cout<<x<<" ";
  REQUIRE(s1.get_line(0) == set<int>({1, 2, 3}));
  REQUIRE(s1.get_line(1) == set<int>({4, 5, 6}));
  REQUIRE(s1.get_line(2) == set<int>({7, 8, 9}));
}

TEST_CASE("get column", "[region]") {
  Sudoku s1;
  clear_except_first_square(s1);
  REQUIRE(s1.get_col(0) == set<int>({1, 4, 7}));
  REQUIRE(s1.get_col(1) == set<int>({2, 5, 8}));
  REQUIRE(s1.get_col(2) == set<int>({3, 6, 9}));
}

TEST_CASE("get square", "[region]") {
  //todo
}

TEST_CASE("shuffle", "[shuffle]") {
  Sudoku s;
  REQUIRE(s.is_valid()==1);
  for(int i=0;i<100;i++) {
    s.shuffle(1);
    REQUIRE(s.is_valid()==1);
  }
}
