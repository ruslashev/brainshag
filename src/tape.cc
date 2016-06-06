#include "tape.hh"

Tape::Tape()
{
	length = 1;
	tapePtr = 0;
	data.reserve(100);

	window = newwin(3, length*4+1, 0, 1);
	// wborder(tapeWin, '|', '|', '-', '-', '+', '+', '+', '+');
	box(window, 0, 0);
}

void Tape::Update()
{
	wmove(window, 1, 1);
	for (int i = 0; i < length; i++) {
		wprintw(window, "%03d", data[i]);
		waddch(window, ACS_VLINE);
	}

	mvchgat(3, 0, -1, A_INVIS, 0, NULL); // clear the line
	mvaddch(3, tapePtr*4+3, '^');
	refresh();

	wrefresh(window);
}

