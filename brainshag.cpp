#include "brainshag.hpp"

static int WindowSizeX, WindowSizeY;

int main(int argc, char *argv[])
{
	initscr();
	keypad(stdscr, true);
	cbreak();
	noecho();
	getmaxyx(stdscr, WindowSizeY, WindowSizeX);
	
	// printw("Welcome to Brainshag, a visual brainfuck interpreter!");
	loadInterpreter();

	endwin();
	printf("Bye!");
	return 0;
}

Tape::Tape(int newSize)
{
	size = newSize;
	dataPointerPos = 0;
	data = (int*)calloc(size, sizeof(int));
	if (data == NULL) {
		// well shit
		// TODO handle this
		endwin();
		exit(1);
	}

	window = newwin(3, size*5+1, 0, 1);
	// wborder(tapeWin, '|', '|', '-', '-', '+', '+', '+', '+');
	box(window, 0, 0);
}
void Tape::Update()
{
	wmove(window, 1, 1);
	for (int i = 0; i < size; i++)
		wprintw(window, "%4d|", data[i]);

	mvchgat(3, 0, -1, A_INVIS, 0, NULL); // clear the line
	mvaddch(3, dataPointerPos*5+4, '^');
	refresh();

	wrefresh(window);
}
Tape::~Tape()
{
	free(data);
}

void loadInterpreter()
{
	/* +--------------------+
	 * |10|5 |6 |1 |  |  |  |
	 * +--------------------+
	 *        ^
	 * +--------------------+
	 * | ++++ > <--[++<-]   | <
	 * | <-->+++++          |
	 * | etc                |
	 * |                    |
	 * |                    |
	 * |                    |
	 * |                    |
	 * +--------------------+
	 * Out:
	 * Hello, W
	 */

	Tape tape(11);

	mvaddstr(WindowSizeY-4, 1, "Input: ");
	mvaddstr(WindowSizeY-3, 1, "Output: ");
	refresh();

	// basically editorWinBorder is a useless window made just so input box
	// can have borders without overwriting them
	WINDOW *editorWinBorder = newwin(WindowSizeY-4-4, WindowSizeX-2, 4, 1);
	box(editorWinBorder, 0, 0);
	wrefresh(editorWinBorder);

	WINDOW *editorWin = newwin(WindowSizeY-4-6, WindowSizeX-4, 5, 2);
	string code;
	scrollok(editorWin, true);
	while (1) // TODO that's terrible to call update that often
	{
		tape.Update();

		code = wgetch(editorWin);
		waddstr(editorWin, code.c_str());
		wrefresh(editorWin);
	}
}

