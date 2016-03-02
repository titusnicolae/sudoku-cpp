#include <iostream>
#include <fstream>

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

using namespace std;

ostream& operator<<(ostream& stream, vector<int>& v) {
  for (int e : v) {
    stream << e << " ";
  }
  return stream;
}
template <typename T, int lines, int columns>
class Array {
 public:
  T array[lines][columns];
  Array() {}
  Array(T value) {
    for (int i = 0; i < lines; i++) {
      for (int j = 0; j < columns; j++) {
        array[i][j] = value;
      }
    }
  }

  friend ostream& operator<<(ostream& stream, Array<T, lines, columns>& array) {
    for (int i = 0; i < lines; i++) {
      for (int j = 0; j < columns; j++) {
        switch (array.at(i,j)) {
          default: stream<<WHITE;break;
          case '1': stream<<GREEN;break;
          case '2': stream<<MAGENTA;break;
          case '3': stream<<CYAN;break;
          case '4': stream<<YELLOW;break;
          case '5': stream<<BLUE;break;
          case '8': stream<<RED;break;
        }
        stream << array.at(i, j);
      }
      stream << endl;
    }
    return stream;
  }

  T& at(int line, int column) { return array[line][column]; }

  template <int lines2, int columns2>
  void copy(Array<T, lines2, columns2> array, int start_lines,
            int start_columns) {
    for (int i = 0; i < lines2; i++) {
      for (int j = 0; j < columns2; j++) {
        this->array[i + start_lines][j + start_columns] = array.at(i, j);
      }
    }
  }
  bool operator==(Array<T, lines, columns>& other) {
    for (int i = 0; i < lines; i++) {
      for (int j = 0; j < columns; j++) {
        if (other.at(i, j) != array[i][j]) {
          return false;
        }
      }
    }
    return true;
  }
  bool operator!=(Array<T, lines, columns>& other) {
    return not((*this) == other);
  }
};
