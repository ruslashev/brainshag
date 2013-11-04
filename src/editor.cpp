#include "editor.hpp"

Editor::Editor(int newScreenSizeX, int newScreenSizeY)
{
	ScreenSizeX = newScreenSizeX;
	ScreenSizeY = newScreenSizeY;

	borderWinSizeX = ScreenSizeX;
	borderWinSizeY = ScreenSizeY-4-5;
	borderWindow = newwin(borderWinSizeY, borderWinSizeX, 4, 0);
	// a cosmetic window, used for lines (see below) and line numbers
	for (int x = 0; x < WindowSizeX; x++) {
		wmove(borderWindow, 0, x);
		waddch(borderWindow, ACS_HLINE);
		wmove(borderWindow, borderWinSizeY-1, x);
		waddch(borderWindow, ACS_HLINE);
	}

	WindowSizeX = ScreenSizeX-4;
	WindowSizeY = ScreenSizeY-4-7;
	window = newwin(WindowSizeY, WindowSizeX, 5, 4);

	curs.x = curs.y = 0;
	bufLines = 1;
	lines.push_back(line_t());
}

void Editor::Update()
{
	// Note from past self: wrap words at > WindowSizeX - 5

	for (int i = 0; i < borderWinSizeY-2; i++)
	{
		wmove(borderWindow, i+1, 0);
		// Not enabling reverse mode gives an overall "viey" feel
		if (i < bufLines)
			wprintw(borderWindow, "%3d ", i+1);
		else
			waddstr(borderWindow, "~");
		wrefresh(borderWindow);
	}
	wmove(borderWindow, 0, 0);
	waddstr(borderWindow, "----");
	wrefresh(borderWindow);

	// wclear(window);
	wmove(window, 0, 0);
	int lineY = 0;
	for (auto &x : lines)
	{
		// TODO clear line in term
		if (x.dirty)
			waddstr(window, x.data.c_str());
		wmove(window, ++lineY, 0);
	}
	wmove(window, curs.y, curs.x);

	wrefresh(window);
}

