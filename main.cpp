#include "sudoku.hpp"

bool solvable(Sudoku s) {
  s.solve();
  return s.is_valid() == 1;
}

int main() {
  Sudoku s, tmp;

  s.shuffle(10000);
  bool flag = true;
  for (int i = 0; i < 54; i++) {
    do {
      tmp = s;
      tmp.remove(1);
    } while (not solvable(tmp));
    s = tmp;
  }
  s.solve();

  return 0;
}
