#include "editor.hpp"

Editor::Editor(int &newScreenSizeX, int &newScreenSizeY)
{
	ScreenSizeX = newScreenSizeX;
	ScreenSizeY = newScreenSizeY;

	borderWinSizeX = ScreenSizeX;
	borderWinSizeY = ScreenSizeY-4-5;
	// a cosmetic window, used for lines (see below) and line numbers
	borderWindow = newwin(borderWinSizeY, borderWinSizeX, 4, 0);
	for (int x = 0; x < WindowSizeX; x++) {
		wmove(borderWindow, 0, x);
		waddch(borderWindow, ACS_HLINE);
		wmove(borderWindow, borderWinSizeY-1, x);
		waddch(borderWindow, ACS_HLINE);
	}

	WindowSizeX = ScreenSizeX-4;
	WindowSizeY = ScreenSizeY-4-7;
	window = newwin(WindowSizeY, WindowSizeX, 5, 4);
}

void Editor::Update()
{
	// wrap words at > WindowSizeX - 5
	bufLines = 0;
	for (int i = 0; i < buffer.size(); i++)
		if (buffer[i] == '\n')
			bufLines++;

	for (int i = 0; i < borderWinSizeY-2; i++)
	{
		wmove(borderWindow, i+1, 0);
		// wattron(borderWindow, A_REVERSE);
		if (i <= bufLines)
			wprintw(borderWindow, "%3d ", i+1);
		else
			waddstr(borderWindow, "~   ");
		// wattroff(borderWindow, A_REVERSE);
		wrefresh(borderWindow);
	}

	wclear(window);
	for (char c : buffer)
		waddch(window, c);

	wrefresh(window);
}

