all: brainshag.hpp
	clang++ brainshag.cpp tape.cpp -g -o brainshag -std=c++0x -lncurses
	./brainshag
