all: sudoku.cpp array.hpp
	clang++ sudoku.cpp array.hpp -std=c++14

format:
	clang-format-3.6 -i -style=Google sudoku.cpp array.hpp
