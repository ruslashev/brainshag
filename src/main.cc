#include "editor.hh"
#include "tape.hh"

int ScreenSizeX, ScreenSizeY;
void loadInterpreter();

int main(int argc, char *argv[])
{
	initscr();
	raw(); // cbreak();
	keypad(stdscr, true);
	noecho();
	getmaxyx(stdscr, ScreenSizeY, ScreenSizeX);

	loadInterpreter();

	endwin();
	printf("Bye!\n");
	return 0;
}

void loadInterpreter()
{
	Tape tape;
	Editor editor(ScreenSizeX, ScreenSizeY);

	mvaddstr(ScreenSizeY-5, 1, "Input: ");
	mvaddstr(ScreenSizeY-4, 1, "Output: ");
	refresh();

	int ch;
	while (1) {
		tape.Update();
		editor.Redraw();

		ch = wgetch(editor.window);

		if (ch == 27) // Escape
			break;

		editor.Update(ch);
	}
}

