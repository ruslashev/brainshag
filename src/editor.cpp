#include "editor.hpp"

Editor::Editor(int newScreenSizeX, int newScreenSizeY)
{
	ScreenSizeX = newScreenSizeX;
	ScreenSizeY = newScreenSizeY;

	WindowSizeX = ScreenSizeX;
	WindowSizeY = ScreenSizeY-4-5;
	window = newwin(WindowSizeY, WindowSizeX, 4, 0);

	curs.x = curs.y = 0;
	lines.push_back("\n");
}

void Editor::Update()
{
	// Note from past self: wrap words at > WindowSizeX - 5

	wclear(window);

	for (int x = 0; x < WindowSizeX; x++) {
		mvwaddch(window, 0, x, ACS_HLINE);
		mvwaddch(window, WindowSizeY-1, x, ACS_HLINE);
	}

	int i = 0;
	for (; i < lines.size(); i++)
		mvwprintw(window, i+1, 0, "%3d %s", i+1, lines[i].c_str());
	for (; i < WindowSizeY; i++)
		mvwaddstr(window, i+1, 0, "~");

	wmove(window, curs.y+1, curs.x+4);

	wrefresh(window);
}

