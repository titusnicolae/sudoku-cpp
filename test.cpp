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
  for (int line = 0; line < 9; line++) {
    for (int col = 0; col < 9; col++) {
      if (line < 3 and col < 3) continue;
      s.at(line / 3, col / 3).at(line % 3, col % 3).clear();
    }
  }
}

TEST_CASE("get line", "[region]") {
  Sudoku s1;
  clear_except_first_square(s1);
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
  // todo
}

TEST_CASE("shuffle", "[shuffle]") {
  Sudoku s;
  REQUIRE(s.is_valid() == 1);
  for (int i = 0; i < 100; i++) {
    s.shuffle(1);
    REQUIRE(s.is_valid() == 1);
  }
}

TEST_CASE() {
  Array<int, 10, 10> a(1), b(1), c(2);
  REQUIRE(a == b);
  REQUIRE(a != c);
}

TEST_CASE("equality inequality operators") {
  Sudoku s1, s2;
  REQUIRE(s1 == s2);
  REQUIRE(not(s1 != s2));
  REQUIRE(s1.at(0, 0) == s2.at(0, 0));
  REQUIRE(not(s1.at(0, 0) != s2.at(0, 0)));
}

TEST_CASE("solve newspaper sudoku", "[solve]") {
  /*
  Sudoku s({{0, 0, 9, 4, 2, 1, 0, 0, 3},
            {1, 0, 3, 7, 5, 0, 2, 0, 0},
            {0, 0, 0, 0, 3, 8, 0, 0, 0},
            {5, 0, 0, 0, 0, 7, 0, 0, 9},
            {0, 0, 0, 0, 6, 0, 0, 0, 0},
            {4, 0, 0, 1, 0, 0, 0, 0, 2},
            {0, 0, 0, 3, 4, 0, 0, 0, 0},
            {0, 0, 7, 0, 1, 6, 8, 0, 4},
            {9, 0, 0, 0, 0, 5, 6, 0, 0}});*/
  Sudoku s({
    {5,2,0,7,0,9,0,0,1},
    {8,0,0,0,0,0,0,0,0},
    {0,1,7,0,0,0,9,0,0},
    {0,8,0,9,0,1,6,0,5},
    {4,0,0,6,0,2,0,0,9},
    {1,0,6,3,0,8,0,2,0},
    {9,0,3,0,0,0,4,1,0},
    {0,0,0,0,0,0,0,0,6},
    {6,0,0,5,0,0,0,9,0}});
  s.solve();
  s.first_pass_restrictions();

  REQUIRE(s.is_valid() == 1);
}

TEST_CASE("check filter") {
  vector<int> v = {1,2,1,4,3,2};
  REQUIRE(filter(v,1)==vector<int>({2,4,3,2}));
  REQUIRE(filter(v,2)==vector<int>({1,1,4,3}));
  REQUIRE(filter(v,4)==vector<int>({1,2,1,3,2}));
  REQUIRE(filter(v,3)==vector<int>({1,2,1,4,2}));
}
