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

void loadInterpreter()
{
	/* +--------------------+
	 * |10|5 |6 |1 |  |  |  |
	 * +--+--+--+--+--+--+--+
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

	refresh();

	int *tape, tapeSize;
	tapeSize = 11;
	tape = (int*)calloc(tapeSize, sizeof(int));
	if (tape == NULL)
	{
		// well shit
		// TODO handle this
		endwin();
		exit(1);
	}

	WINDOW *tapeWin = newwin(3, tapeSize*4+1, 0, 1);
	wborder(tapeWin, '|', '|', '-', '-', '+', '+', '+', '+');
	wmove(tapeWin, 1, 1);
	for (int i = 0; i < tapeSize; i++)
	{
		// TODO make a pretty separator
		// i.e.: +
		//       |
		//       +
		wprintw(tapeWin, " %d |", tape[i]);
	}
	wrefresh(tapeWin);

	mvaddstr(WindowSizeY-4, 1, "Input: ");
	mvaddstr(WindowSizeY-3, 1, "Output: ");

	// basically editorWinBorder is a useless window made just so input box
	// can have borders without overwriting them
	WINDOW *editorWinBorder = newwin(WindowSizeY-4-4, WindowSizeX-2, 4, 1);
	box(editorWinBorder, 0, 0);
	wrefresh(editorWinBorder);

	WINDOW *editorWin = newwin(WindowSizeY-4-6, WindowSizeX-4, 5, 2);
	string code;
	while (true) // TODO that's terrible to call update that often
	{
		code = wgetch(editorWin);
		waddstr(editorWin, code.c_str());
		wrefresh(editorWin);
	}
	scrollok(editorWin, false);

	free(tape);
}

