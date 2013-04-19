#include "brainshag.hpp"

static int WindowSizeX, WindowSizeY;

int main(int argc, char *argv[])
{
	initscr();
	keypad(stdscr, true);
	cbreak();
	noecho();
	getmaxyx(stdscr, WindowSizeY, WindowSizeX);
	
	printw("Welcome to Brainshag, a visual brainfuck interpreter!");
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

	WINDOW *tape = newwin(4, WindowSizeX-4, 1, 1);
	box(tape, 0, 0);
	wborder(tape, '#', '#', '#', '#', '#', '#', '#', '#');
	wrefresh(tape);
	refresh();
}

