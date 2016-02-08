#include <iostream>
#include <stdexcept>
#include "array.hpp"
using namespace std;

typedef Array<int, 3, 3> Square;
typedef Array<Square, 3, 3> Table;

class Sudoku {
  Table table;

 public:
  Sudoku():table(Array<int, 3, 3>(0)) {
    table = Table(Square(0));
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
       table.at(i, j) = square(i * 3 + j + 1);
      }
    }
  }


  friend ostream& operator<<(ostream& stream, Sudoku& sudoku) {
    Array<char, 11, 13> buffer(' ');
    for(int i=0;i<3;i++) {
      for(int j=0;j<3;j++) {
        for(int k=0;k<3;k++) {
          for(int l=0;l<3;l++) {
            buffer.at(i*4+k, j*5+l) = sudoku.table.at(i,j).at(k,l)+'0';
          }
        }
      }
    }
    stream << buffer;
    return stream;
  }

 private:
  Square square(int offset = 1) {
    if (offset < 1 or offset > 9) {
      throw logic_error("square assert fail");
    }

    Square ret(0);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        ret.at(i, j) = offset;
        offset = offset % 9 + 1;
      }
    }
    return ret;
  }
};

int main() {
  Sudoku sudoku;
  cout << sudoku;
  return 0;
}
