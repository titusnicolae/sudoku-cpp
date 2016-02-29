#include "sudoku.hpp"

void solve(Sudoku& s) {
  Sudoku prev; 
  do {
    prev=s;
    s.recompute_restrictions(); 
  }
  while(prev != s);
}

bool solvable(Sudoku s) {
  solve(s);  
  return s.is_valid()==1;
}

int main() {
  Sudoku s,tmp;
  
  s.shuffle(10000);
  bool flag=true;
  for(int i=0;i<56;i++) {
    cout<<i<<endl;
    do {
      tmp = s;
      tmp.remove(1);
    }
    while(not solvable(tmp));
    s= tmp;
  } 
  cout<<s<<endl;
  solve(s); 
  cout<<s<<endl;
  cout<<s.is_valid();
  
  return 0;
}
