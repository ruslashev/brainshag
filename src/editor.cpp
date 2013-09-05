#include "editor.hpp"

Editor::Editor(int &newWindowSizeX, int &newWindowSizeY)
{
	WindowSizeX = newWindowSizeX;
	WindowSizeY = newWindowSizeY;
	// a cosmetic window, used for borders around main editor window
	borderWindow = newwin(WindowSizeY-4-4, WindowSizeX, 4, 0);
	box(borderWindow, 0, 0);
	wrefresh(borderWindow);

	window = newwin(WindowSizeY-4-6, WindowSizeX-4, 5, 5);
	char ch;
	std::string buffer;
}

void Editor::Update()
{
	// wrap words at > WindowSizeX - 5
	bufLines = 0;
	for (int i = 0; i < buffer.size(); i++)
		if (buffer[i] == '\n')
			bufLines++;

	for (int i = 0; i < WindowSizeY-4-6; i++)
	{
		wmove(borderWindow, 1+i, 0);
		wattron(borderWindow, A_REVERSE);
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

