#include "sudoku.hpp"

bool solvable(Sudoku s) {
  s.solve();
  return s.is_valid() == 1;
}

int main() {
  Sudoku s, tmp;
  for(int j = 0; j<2;j++) {
    cout<<j<<endl;
    s.shuffle(10000);
    bool flag = true;
    for (int i = 0; i < 54; i++) {
      do {
        tmp = s;
        tmp.remove(1);
      } while (not solvable(tmp));
      s = tmp;
    }
    ofstream puzzle("output/out"+to_string(j)+".puzzle");
    puzzle<<s.to_string();
    puzzle.close();

    s.solve();

    ofstream solution("output/out"+to_string(j)+".solution");
    solution<<s.to_string();
    solution.close();
    cout<<"------------"<<endl;
  }
  return 0;
}
