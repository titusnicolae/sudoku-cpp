#include <iostream>
#include <vector>
#include <stdexcept>
#include <iterator>
#include "array.hpp"
using namespace std;

typedef Array<vector<int>, 3, 3> Square;
typedef Array<Square, 3, 3> Table;

class Sudoku {
  Table table;

 public:
  Sudoku() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        table.at(i, j) = square(j * 3 + i + 1);
      }
    }
  }

  friend ostream& operator<<(ostream& stream, Sudoku& sudoku) {
    const int N = 35;
    Array<char, N, N> buffer(' ');
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
          for (int l = 0; l < 3; l++) {
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
  
  vector<int> filter(int x, int y) {
    int squarex = x/3, squarey=y/3;
    int posx = x%3, posy = y%3;
    vector<int> ret(table.at(squarex, squarey).at(posx, posy));

    copy(ret.begin(), ret.end(), ostream_iterator<int>(cout, " "));
    return ret;
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

int main() {
  Sudoku sudoku;
  cout << sudoku;
  sudoku.filter(5, 5);
  return 0;
}
