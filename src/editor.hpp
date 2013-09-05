#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <string>
#include <ncurses.h>

class Editor
{
	private:
		int WindowSizeX, WindowSizeY;
	public:
		WINDOW *window, *borderWindow;
		std::string buffer;
		int bufLines;

		void Update();

		Editor(int &newWindowSizeX, int &newWindowSizeY);
};

#endif
