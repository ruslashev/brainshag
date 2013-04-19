all: brainshag.hpp
	g++ brainshag.cpp -std=c++0x -g -o brainshag -lncurses -lmenu
#	mate-terminal -e ./brainshag
