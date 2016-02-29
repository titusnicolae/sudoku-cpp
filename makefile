all: sudoku.hpp array.hpp
	clang++ -o main main.cpp -std=c++14
	./main

test: test.cpp
	clang++ -o test test.cpp -std=c++14
	./test
 

format:
	clang-format-3.6 -i -style=Google sudoku.hpp array.hpp test.cpp main.cpp
