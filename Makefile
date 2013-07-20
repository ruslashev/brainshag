all: brainshag.hpp
	clang++ brainshag.cpp -g -o brainshag -std=c++0x -lncurses
	./brainshag
