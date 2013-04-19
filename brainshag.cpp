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

	getch();

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
	WINDOW *tape = newwin(3, WindowSizeX, 0, 0);
	box(tape, 0, 0);
	wrefresh(tape);
}

