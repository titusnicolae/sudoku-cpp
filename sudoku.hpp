#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <functional>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <set>
#include <map>
#include "array.hpp"
#include <cassert>
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#define DEBUG 0
#define AA 0
using namespace std;

typedef Array<vector<int>, 3, 3> Square;
typedef Array<Square, 3, 3> Table;

struct XY{
  int x,y;
  XY(int x, int y) : x(x),y(y){}
};

bool operator==(const XY& s1, const XY& s2) {
  return s1.x==s2.x and s1.y==s2.y;
}

bool operator<(const XY& s1, const XY& s2) {
  if (s1.x<s2.x) return true;
  else if(s1.x>s2.x) return false;
  if (s1.y<s2.y) return true;
  return false;
}

std::random_device rd;
std::mt19937 gen(rd());
set<int> one_to_nine({1, 2, 3, 4, 5, 6, 7, 8, 9});

int max(set<int> s) {
  int ret = *s.begin();
  for(auto& e: s) {
    ret = max(e,ret);
  }
  return ret;
}

int min(set<int> s) {
  int ret = *s.begin();
  for(auto& e: s) {
    ret = min(e,ret);
  }
  return ret;
}

set<int> operator-=(set<int>& first, set<int> second) {
  for (auto& e : second) {
    first.erase(e);
  }
  return first;
}
set<int> operator-(set<int>& first, set<int> second) {
  set<int> ret;
  for (auto& e : first) {
    if(second.find(e) == second.end()){
      ret.insert(e);
    }
  }
  return ret;
}

set<int> intersect(set<int>& a, set<int>& b) {
  set<int> ret;
  for(int x: a) {
    if(b.find(x)!=b.end()) {
      ret.insert(x);
    }
  }
  return ret;
}

vector<int> filter(const vector<int>& v, int n) {
  vector<int> res;
  for(int x: v)
    if(x!=n) res.push_back(x);
  return res;
}
vector<int> filter_out(const vector<int>& v, const set<int>& s) {
  vector<int> res;
  for(int x: v) {
    if(s.find(x)==s.end()) {
      res.push_back(x);
    }
  } 
  return res;
}

void print(set<int> s) {
  for (auto& e : s) {
    cout << e << " ";
  }
  cout << endl;
}

class Sudoku {
 public:
  Table table;
  Sudoku(vector<vector<int>> v) {
    assert(v.size() == 9);
    for (auto& e : v) assert(e.size() == 9);
    for (int l = 0; l < 9; l++) {
      for (int c = 0; c < 9; c++) {
        if (v[l][c] != 0) {
          table.at(l / 3, c / 3).at(l % 3, c % 3) = {v[l][c]};
        }
      }
    }
  }
  Sudoku(vector<vector<vector<int>>> v) {
    assert(v.size() == 9);
    for (auto& e : v) assert(e.size() == 9);
    for (int l = 0; l < 9; l++) {
      for (int c = 0; c < 9; c++) {
        table.at(l / 3, c / 3).at(l % 3, c % 3) = v[l][c];
      }
    }
  }

  Sudoku(Table a) { table = a; }
  Sudoku() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        table.at(i, j) = square(j * 3 + i + 1);
      }
    }
  }
  Square& at(int i, int j) { return table.at(i, j); }

  friend ostream& operator<<(ostream& stream, Sudoku& sudoku) {
    stream<<sudoku.table;
    return stream;
  }

  string to_string() {
    stringstream ss;
    ss<<"[";
    for(int i=0;i<9;i++) {
      ss<<"[";
      for(int j=0;j<9;j++) {
        auto& list = table.at(i/3,j/3).at(i%3,j%3);
        if(list.size()==1) 
          ss<<list[0];
        else
          ss<<0; 
        if(j!=8)
          ss<<", ";
        else {
          if(i!=8) 
            ss<<"],"<<endl;
          else
            ss<<"]";
        } 
      }
      if(i==8)
        ss<<"]"<<endl;
    } 
    return ss.str();
  }

  friend ostream& operator<<(ostream& stream, Table& table) {
    const int N = 35;
    Array<char, N, N> buffer(' ');
    for (int i : {0, 1, 2}) {
      for (int j : {0, 1, 2}) {
        for (int k : {0, 1, 2}) {
          for (int l : {0, 1, 2}) {
            vector<bool> v(10);
            for (auto e : table.at(i, j).at(k, l)) {
              v[e] = true;
            }
            for (int m = 0; m < 9; m++) {
              if (v[m + 1]) {
                buffer.at((i * 3 + k) * 4 + m / 3, (j * 3 + l) * 4 + m % 3) =
                    m + 1 + '0';
              }
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

    for (int i = 0; i < 2; i++) {
      for (int k = 0; k < N; k++) {
        buffer.at(k, i * 12 + 11) = 'x';
        buffer.at(i * 12 + 11, k) = 'x';
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
  static pair<int, int> random_pair(int start, int end) {
    int first, second;
    std::uniform_int_distribution<> random_op(start, end);
    first = random_op(gen);
    while ((second = random_op(gen)) == first)
      ;
    return make_pair(first, second);
  }
  static int random(int start, int end) {
    std::uniform_int_distribution<> random_op(start, end);  // cache
    return random_op(gen);
  }

  void shuffle(int steps) {
    std::uniform_int_distribution<> random_op(0, 3);
    pair<int, int> temp;
    int l;
    for (int i = 0; i < steps; i++) {
      switch (random_op(gen)) {
        case 0:
          temp = Sudoku::random_pair(0, 2);
          swap_block_line(temp.first, temp.second);
          break;

        case 1:
          temp = random_pair(0, 2);
          swap_block_column(temp.first, temp.second);
          break;

        case 2:
          temp = random_pair(0, 2);
          l = random(0, 2) * 3;
          swap_line(l + temp.first, l + temp.second);
          break;

        case 3:
          temp = random_pair(0, 2);
          l = random(0, 2) * 3;
          swap_column(l + temp.first, l + temp.second);
          break;
      }
    }
  }
  void remove(int steps) {
    std::uniform_int_distribution<> r3(0, 2);
    for (int i = 0; i < steps; i++) {
      for (int j = 0; j <= 100000; j++) {
        if (j == 100000) throw logic_error("random");
        auto& v = table.at(r3(gen), r3(gen)).at(r3(gen), r3(gen));
        if (v.size() > 0) {
          v.clear();
          break;
        }
      }
    }
  }
  set<int> get_line(int l) {
    set<int> ret;
    for (int c = 0; c < 9; c++) {
      auto e = table.at(l / 3, c / 3).at(l % 3, c % 3);
      if (e.size() == 1) {
        ret.insert(e[0]);
      }
    }
    return ret;
  }
  set<int> get_col(int c) {
    set<int> ret;
    for (int l = 0; l < 9; l++) {
      auto e = table.at(l / 3, c / 3).at(l % 3, c % 3);
      if (e.size() == 1) {
        ret.insert(e[0]);
      }
    }
    return ret;
  }
  set<int> get_square(int line, int col) {
    set<int> ret;
    for (int i = 0; i < 9; i++) {
      auto e = table.at(line, col).at(i / 3, i % 3);
      if (e.size() == 1) {
        ret.insert(e[0]);
      }
    }
    return ret;
  }
  void remove_options() {
    for (int lb : {0, 1, 2})
      for (int cb : {0, 1, 2})
        for (int l : {0, 1, 2})
          for (int c : {0, 1, 2}) {
            auto& e = table.at(lb, cb).at(l, c);
            if (e.size() > 1) e.clear();
          }
  }

  void first_pass_restrictions() {
    if(AA) cout<<"first_pass_restrictions"<<endl;
    for (int line = 0; line < 9; line++) {
      for (int col = 0; col < 9; col++) {
        auto& e = table.at(line / 3, col / 3).at(line % 3, col % 3);
        if (e.size() != 1) {
          set<int> s;
          if(e.size()==0)
            s = one_to_nine;
          else
            s = set<int>(e.begin(), e.end());
          s -= get_line(line);
          s -= get_col(col);
          s -= get_square(line / 3, col / 3);
          e = vector<int>(s.begin(), s.end());
        }
      }
    }
  }

  void unique_in_square() {
    if(AA) cout<<"unique_in_square"<<endl;
    for (int lb : {0, 1, 2}) {
      for (int cb : {0, 1, 2}) {
        map<int, vector<XY>> m;
        for (int l : {0, 1, 2}) {
          for (int c : {0, 1, 2}) {
            for (int e : table.at(lb, cb).at(l, c)) {
              m[e].push_back(XY(l, c));
            }
          }
        }
        for (auto& e : m) {
          if (e.second.size() == 1) {
            table.at(lb, cb).at(e.second[0].x, e.second[0].y) =
                vector<int>{e.first};
          }
        }
      }
    }
  }
  void unique_in_line() {
    if(AA) cout<<"unique_in_line"<<endl;
    for(int l=0;l<9;l++) {
      map<int, set<int>> m;
      for(int c=0;c<9;c++) {
        for(int e: table.at(l/3,c/3).at(l%3,c%3)) {
          m[e].insert(c);
        }
      }
      for(auto& e: m) {
        if (e.second.size()==1) {
          int col = *(e.second.begin());
          table.at(l/3, col/3).at(l%3, col%3) = {e.first};
        }
      }
    }
  }

  void unique_in_column() {
    if(AA) cout<<"unique_in_column"<<endl;
    for(int c=0;c<9;c++) {
      map<int, set<int>> m;
      for(int l=0;l<9;l++) {
        for(int e: table.at(l/3,c/3).at(l%3,c%3)) {
          m[e].insert(l);
        }
      }
      for(auto& e: m) {
        if(DEBUG) {
          cout<<"unique_in_column c: "<<c<<" e: "<<e.first<<": ";
        }

        if (e.second.size()==1) {
          int line = *(e.second.begin());
          //cout<<"unique_in_column l: "<<line<<" c: "<<c<<" "<<e.first<<endl;
          table.at(line/3, c/3).at(line%3, c%3) = vector<int>({e.first});
        }
      }
    }
  }

  void same_line_column() {
    if(AA) cout<<"same_line_column"<<endl;
    for(int lb: {0,1,2}) {
      for(int cb: {0,1,2}) {
        map<int, vector<int>> line;    
        map<int, vector<int>> column;    
        for(int l: {0,1,2}) {
          for(int c: {0,1,2}) {
            auto& possibilities=table.at(lb, cb).at(l, c);
            for(int e: possibilities) {
              line[e].push_back(3*lb+l);
              column[e].push_back(3*cb+c);
            }
          }
        }
        for(auto& e: line) {
          if(e.second.size()>1 and set<int>(e.second.begin(), e.second.end()).size()==1) {
            for(int i=0;i<9;i++)  {
              if (i/3==cb) continue;
              auto& possibilities = table.at(e.second[0]/3, i/3).at(e.second[0]%3, i%3);
              possibilities = filter(possibilities, e.first);
            } 
          } 
        }
        for(auto& e: column) {
          if(e.second.size()>1 and set<int>(e.second.begin(), e.second.end()).size()==1) {
            for(int i=0;i<9;i++) {
              if (i/3==lb) continue;
              auto& possibilities = table.at(i/3, e.second[0]/3).at(i%3, e.second[0]%3);
              possibilities = filter(possibilities, e.first);
            }
          } 
        }
      }
    }
  }
  void naked_pair_line2() { //exactly two of each in te same place
    if(AA) cout<<"naked_pair_line2"<<endl;
    for(int l=0;l<9;l++) {
      map<int, set<int>> line;
      for(int c=0;c<9;c++) {
        for(auto& e: table.at(l/3, c/3).at(l%3, c%3)){
          line[c].insert(e);
        }
      }
      for(auto a=line.begin();a!=line.end(); a++) {
        for(auto b=next(a); b!=line.end(); b++) {
          if(a->second == b->second and a->second.size()==2) {
            for(int c2=0; c2<9;c2++) {
              if(!(c2==a->first or c2==b->first)){
                table.at(l/3,c2/3).at(l%3, c2%3) = filter_out(table.at(l/3,c2/3).at(l%3,c2%3), a->second);
              }
            }
          }
        }
      }
    }
  }

  void box_line_column() {
    for(int c = 0;c<9;c++) {
      map<int, set<int>> pos;  
      for(int l = 0;l<9;l++) {
        for(auto& e: table.at(l/3, c/3).at(l%3, c%3)){
          pos[e].insert(l);
        }
      }
      for(auto& e: pos) {
        for(int lb=0;lb<3;lb++) {
          if(lb*3<=min(e.second) and max(e.second)<=lb*3+2) {
            for(int l=0;l<=2;l++) {
              for(int cb=0;cb<=2;cb++) {
                if(c%3!=cb) {
                  table.at(lb,c/3).at(l,cb) = filter_out(table.at(lb,c/3).at(l,cb), set<int>({e.first}));
                }
              }
            }
          }
        }
      }
    } 
  } 

  void naked_pair_column() {
    if(AA) cout<<"naked_pair_column"<<endl;
    for(int c=0;c<9;c++) {
      map<int, set<int>> rows;  
      for(int l=0;l<9;l++) {
        for(auto& e: table.at(l/3,c/3).at(l%3, c%3)) {
          rows[e].insert(l); 
        } 
      }
      for(auto a = rows.begin(); a!=rows.end(); a++) {
        for(auto b = next(a); b!=rows.end(); b++) {
          if(a->second == b->second and a->second.size()==2) {
            for(int row=0;row<9;row++) {
              auto& possibilities = table.at(row/3,c/3).at(row%3,c%3);
              if(DEBUG) {cout<<"naked_col l: "<<row<<"c: "<<c<<" ["<<a->first<<" "<<b->first<<"]\n";}
              if(a->second.find(row)!=a->second.end()) {
                possibilities = vector<int>({a->first, b->first}); 
              }
              else {
                possibilities = filter_out(possibilities, set<int>({a->first, b->first}));
              }
            }
          }
        }
      }
    }
  }
  void hidden_pair_square() {
    for(int lb: {0,1,2}) {
      for(int cb: {0,1,2}) {
        map<int, set<XY>> pos; 
        for(int l: {0,1,2}) {
          for(int c: {0,1,2}) {
            for(int e: table.at(lb,cb).at(l,c)) {
              pos[e].insert(XY(l,c));
            }
          }
        }
      
        for(auto a=pos.begin();a!=pos.end(); a++) {
          for(auto b = next(a); b!=pos.end(); b++) {
            if(a->second == b->second and a->second.size()==2) {
              for(auto& e: a->second) {
                table.at(lb,cb).at(e.x, e.y) = vector<int>{a->first, b->first}; 
              }
            }
          }
        }
      }
    }
  }

  void naked_pair_square() {
    if(AA) cout<<"naked_pair_square"<<endl;
    for(int lb: {0,1,2}) {
      for(int cb: {0,1,2}) {
        map<XY, set<int>> pos; 
        for(int l: {0,1,2}) {
          for(int c: {0,1,2}) {
            for(int e: table.at(lb,cb).at(l,c)) {
              pos[XY(l,c)].insert(e);
            }
          }
        }

        for(auto a=pos.begin();a!=pos.end(); a++) {
          for(auto b = next(a); b!=pos.end(); b++) {
            if(a->second == b->second and a->second.size()==b->second.size() and a->second.size()==2) {
              for(int l: {0,1,2}) {
                for(int c: {0,1,2}) {
                  if(!((a->first.x==l and a->first.y==c) or (b->first.x==l and b->first.y==c))){
                    filter_out(table.at(lb,cb).at(l,c), a->second);
                  }
                }
              }  
            }
          }
        }
      }
    }
    /*
    for(int l=0;l<9;l++) {
      map<int, set<int>> cols;  
      for(int c=0;c<9;c++) {
        for(auto& e: table.at(l/3,c/3).at(l%3, c%3)) {
          cols[e].insert(c); 
        } 
      }
      for(auto a = cols.begin(); a!=cols.end(); a++) {
        for(auto b = next(a); b!=cols.end(); b++) {
          if(a->second == b->second and a->second.size()==2) {
            for(int col: a->second) {
              auto& possibilities = table.at(l/3,col/3).at(l%3,col%3) = vector<int>({a->first, b->first});

            }
          }
        }
      }
    }*/
  }



  void recompute_restrictions() {
    vector<function<void(void)>> solvers = {
      bind(&Sudoku::first_pass_restrictions, this),
      bind(&Sudoku::same_line_column, this),
      bind(&Sudoku::unique_in_column, this),
      bind(&Sudoku::unique_in_square, this),
      bind(&Sudoku::unique_in_line, this),
      bind(&Sudoku::naked_pair_line2, this),
      bind(&Sudoku::naked_pair_column, this),
      bind(&Sudoku::naked_pair_square, this),
      bind(&Sudoku::hidden_pair_square, this),
      bind(&Sudoku::box_line_column, this),
    };
    for(auto& e: solvers) {
      Sudoku prev = *this;
      e();
      if(*this!=prev) {
        //cout<<*this<<endl;
      }
    }
  }

  bool operator!=(Sudoku& s) { return not(*this == s); }
  bool operator==(Sudoku& s) {
    for (int l = 0; l < 9; l++) {
      for (int c = 0; c < 9; c++) {
        if (table.at(l / 3, c / 3).at(l % 3, c % 3) !=
            s.at(l / 3, c / 3).at(l % 3, c % 3)) {
          return false;
        }
      }
    }
    return true;
  }
  int is_valid() {
    for (int lb : {0, 1, 2})
      for (int cb : {0, 1, 2})
        for (int l : {0, 1, 2})
          for (int c : {0, 1, 2}) {
            auto& e = table.at(lb, cb).at(l, c);
            if (e.size() != 1) {
              return -1;
            }
          }
    for (int i = 0; i < 9; i++) {
      if (get_line(i) != one_to_nine) {
        return -2;
      }
      if (get_col(i) != one_to_nine) {
        return -3;
      }
    }
    for (int l : {0, 1, 2}) {
      for (int c : {0, 1, 2}) {
        if (get_square(l, c) != one_to_nine) {
          return -4;
        }
      }
    }
    return 1;
  }
  void solve() {
    Table prev;
    do {
      prev = table;
      if(DEBUG) {cout<<"prev"<<endl<<prev<<endl;}
      recompute_restrictions();
      if(DEBUG) {cout<<"table"<<endl<<table<<endl;}
      for(int rr = 0;rr<9;rr++) {
        if(DEBUG) {cout<<rr<<": ";}
        for(auto& e: table.at(rr/3,2).at(rr%3,2)) {
          if(DEBUG) {cout<<e<<" ";}
        }
        if(DEBUG) {cout<<endl;}
      }
    } while (prev != table);
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
