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

/* TODO: needs ywing
TEST_CASE("solve newspaper from halfway", "[solve]") {
  Sudoku s({
    {{5},{2},{4},{7},{3},{9},{8},{6},{1}},
    {{8},{6},{9},{1,2,4,5},{1,2},{4, 5},{3,5},{4,5,7},{3,7}},
    {{3},{1},{7},{4,5,8},{6,8},{4,5,6},{9},{4,5},{2}},
    {{7},{8},{2},{9},{4},{1},{6},{3},{5}},
    {{4},{3},{5},{6},{7},{2},{1},{8},{9}},
    {{1},{9},{6},{3},{5},{8},{7},{2},{4}},
    {{9},{5},{3},{2,8},{2,6,8},{6,7},{4},{1},{7,8}},
    {{2},{4,7},{1,8},{1,4,5,8},{9},{3,4,5,7},{3,5},{5,7},{6}},
    {{6},{4,7},{1,8},{4,5},{1,8},{3,4,5,7},{2},{9},{3,7}},
  });
  s.solve();
  cout<<s;
  REQUIRE(s.is_valid() == 1);
} */
 /* 
TEST_CASE("solve newspaper sudoku", "[solve]") {
  Sudoku s({
    {5,2,4,7,0,9,0,6,1},
    {8,6,9,0,0,0,0,0,0},
    {3,1,7,0,0,0,9,0,2},
    {7,8,2,9,4,1,6,3,5},
    {4,3,5,6,7,2,1,8,9},
    {1,9,6,3,5,8,7,2,0},
    {9,5,3,0,0,0,4,1,0},
    {2,0,0,0,9,0,0,0,6},
    {6,0,0,5,0,0,0,9,0}});
  s.solve();
  cout<<s<<endl;
  REQUIRE(s.is_valid() == 1);
}
TEST_CASE("solve newspaper sudoku 21", "[solve]") {
  Sudoku s({
    {0,0,0,3,0,0,0,2,0},
    {7,0,0,0,0,0,6,0,0},
    {0,6,5,9,8,0,0,0,0},
    {9,5,0,0,0,0,2,3,0},
    {8,1,0,5,0,6,0,9,4},
    {0,7,2,0,0,0,0,8,5},
    {0,0,0,0,7,9,4,5,0},
    {0,0,7,0,0,0,0,0,2},
    {0,9,0,0,0,1,0,0,0}});
  s.solve();
  cout<<s;
  REQUIRE(s.is_valid() == 1);
}

TEST_CASE("asd") {
  Sudoku s({
    {0, 5, 3, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 4},
    {7, 8, 6, 4, 5, 3, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 4, 2, 9, 1, 0, 0, 0, 6},
    {0, 7, 0, 3, 4, 2, 0, 8, 0},
    {0, 0, 7, 0, 0, 0, 0, 1, 2},
    {0, 0, 0, 0, 3, 0, 0, 0, 0},
    {2, 0, 1, 0, 9, 0, 6, 0, 0}});
  s.solve();
  cout<<s;
  REQUIRE(s.is_valid()==1);
}
*/

TEST_CASE("XY set") {
  set<XY> xy;
  for(int x=0;x<1000;x++) {
    for(int y=0;y<1000;y++) {
      xy.insert(XY(x,y)); 
    }
  }
  REQUIRE(xy.size()==1000*1000);
}

TEST_CASE("moderate", "[solve]") {
  //todo pointing pairs
  Sudoku s({
    {4, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 3, 0, 9, 0, 4, 0},
    {0, 7, 0, 0, 0, 5, 0, 0, 9},
    {0, 0, 0, 0, 6, 0, 0, 2, 1},
    {0, 0, 4, 0, 7, 0, 6, 0, 0},
    {1, 9, 0, 0, 5, 0, 0, 0, 0},
    {9, 0, 0, 4, 0, 0, 0, 7, 0},
    {0, 3, 0, 6, 0, 8, 0, 0, 0},
    {0, 0, 0, 0, 3, 0, 0, 0, 6}});
  s.solve();
  cout<<s;
  REQUIRE(s.is_valid()==1);
}


TEST_CASE("set of XY", "datastructure") {
  set<XY> xy;
  for(int i=0;i<1000;i++) {
    xy.insert(XY(i,i));
  }
  REQUIRE(xy.size()==1000);   
}
TEST_CASE("set intersection") {
  set<int> a({1,2,3});
  set<int> b({1,2,3,4});
  REQUIRE(intersect(a,b)==a);
}

TEST_CASE("check filter") {
  vector<int> v = {1,2,1,4,3,2};
  REQUIRE(filter(v,1)==vector<int>({2,4,3,2}));
  REQUIRE(filter(v,2)==vector<int>({1,1,4,3}));
  REQUIRE(filter(v,4)==vector<int>({1,2,1,3,2}));
  REQUIRE(filter(v,3)==vector<int>({1,2,1,4,2}));
}
TEST_CASE("max min set") {
  REQUIRE(max(set<int>({3,4,5}))==5);
  REQUIRE(min(set<int>({3,4,5}))==3);
}

TEST_CASE("check set subtraction") {
  set<int> a({1,2,3,4});
  set<int> b({1,2,3});
  REQUIRE(a-b==set<int>({4}));
}
TEST_CASE("filter out") {
  REQUIRE(filter_out(vector<int>({1,2,3,4}), set<int>({1,4})) == vector<int>({2,3}));
}

