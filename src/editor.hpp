#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <string>
#include <vector>
#include <ncurses.h>

class Editor
{
	int ScreenSizeX, ScreenSizeY;
	int WindowSizeX, WindowSizeY;
public:
	WINDOW *window;
	std::vector<std::string> lines;
	struct { unsigned int x, y; } curs;

	Editor(int newScreenSizeX, int newScreenSizeY);

	void Update();
};

#endif
