all: brainshag.hpp
	g++ brainshag.cpp -std=c++0x -g -o brainshag -lncurses
#	mate-terminal -e ./brainshag
