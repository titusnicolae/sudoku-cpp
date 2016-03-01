#include <iostream>
#include <fstream>
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
