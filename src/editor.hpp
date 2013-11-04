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
	enum { NORMAL, INSERT, COMMAND } mode;
	std::string commandBuf;

	Editor(int newScreenSizeX, int newScreenSizeY);

	void Update(int ch);
	void Redraw();
};

#endif
