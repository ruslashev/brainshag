#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <string>
#include <ncurses.h>

class Editor
{
	private:
		int ScreenSizeX, ScreenSizeY;
		int WindowSizeX, WindowSizeY;
		int borderWinSizeX, borderWinSizeY;
	public:
		WINDOW *window, *borderWindow;
		std::string buffer;
		int bufLines;

		void Update();

		Editor(int &newScreenSizeX, int &newScreenSizeY);
};

#endif
