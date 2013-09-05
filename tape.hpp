#ifndef TAPE_HPP
#define TAPE_HPP

#include <ncurses.h>
#include <cstdlib>
#include <vector>

class Tape
{
public:
	WINDOW *window;
	int length;
	std::vector<int> data;
	int tapePtr;

	Tape();

	void Update();
};

#endif
