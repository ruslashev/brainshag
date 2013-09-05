#include "tape.hpp"

Tape::Tape()
{
	length = 1;
	tapePtr = 0;
	data.reserve(100);

	window = newwin(3, length*5+1, 0, 1);
	// wborder(tapeWin, '|', '|', '-', '-', '+', '+', '+', '+');
	box(window, 0, 0);
}

void Tape::Update()
{
	wmove(window, 1, 1);
	for (int i = 0; i < length; i++)
		wprintw(window, "%04d|", data[i]);

	mvchgat(3, 0, -1, A_INVIS, 0, NULL); // clear the line
	mvaddch(3, tapePtr*5+4, '^');
	refresh();

	wrefresh(window);
}

