#include "editor.hpp"

Editor::Editor(int newScreenSizeX, int newScreenSizeY)
{
	ScreenSizeX = newScreenSizeX;
	ScreenSizeY = newScreenSizeY;

	borderWinSizeX = ScreenSizeX;
	borderWinSizeY = ScreenSizeY-4-5;
	borderWin = newwin(borderWinSizeY, borderWinSizeX, 4, 0);
	// a cosmetic window, used for lines (see below) and line numbers
	for (int x = 0; x < borderWinSizeX; x++) {
		mvwaddch(borderWin, 0, x, ACS_HLINE);
		mvwaddch(borderWin, borderWinSizeY-1, x, ACS_HLINE);
	}

	WindowSizeX = ScreenSizeX-4;
	WindowSizeY = ScreenSizeY-4-7;
	window = newwin(WindowSizeY, WindowSizeX, 5, 4);

	curs.x = curs.y = 0;
	lines.push_back("\n");
}

void Editor::Update()
{
	// Note from past self: wrap words at > WindowSizeX - 5

	int i = 0;
	for (; i < lines.size(); i++)
		mvwprintw(borderWin, i+1, 0, "%3d %s", i+1, lines[i].c_str());
	for (; i < WindowSizeY; i++)
		mvwaddstr(borderWin, i+1, 0, "~");

	wmove(window, curs.y, curs.x);

	wrefresh(borderWin);
	wrefresh(window);
}

