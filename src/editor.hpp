#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <string>
#include <vector>
#include <ncurses.h>

struct line_t
{
	std::string data;
	bool dirty;

	line_t(std::string newData = "") { data = newData; dirty = true; };
};

class Editor
{
	private:
		int ScreenSizeX, ScreenSizeY;
		int WindowSizeX, WindowSizeY;
		int borderWinSizeX, borderWinSizeY;
	public:
		WINDOW *window, *borderWindow;
		std::vector<line_t> lines; // TODO try other containers
		int bufLines;
		struct { unsigned int x, y; } curs;

		void Update();

		Editor(int newScreenSizeX, int newScreenSizeY);
};

#endif
