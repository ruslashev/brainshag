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
	printf("Bye!\n");
	return 0;
}

Tape::Tape()
{
	size = 1;
	dataPointer = 0;
	data = (int*)calloc(size, sizeof(int));
	if (data == NULL) {
		endwin();
		printf("Failed to allocate memory for tape");
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
	mvaddch(3, dataPointer*5+4, '^');
	refresh();

	wrefresh(window);
}
Tape::~Tape()
{
	free(data);
}

Editor::Editor()
{
	// a cosmetic window, used for borders around main editor window
	borderWindow = newwin(WindowSizeY-4-4, WindowSizeX, 4, 0);
	box(borderWindow, 0, 0);
	wrefresh(borderWindow);

	window = newwin(WindowSizeY-4-6, WindowSizeX-4, 5, 5);
	char ch;
	std::string buffer;
}
void Editor::Update()
{
	// wrap words at > WindowSizeX - 5
	bufLines = 0;
	for (int i = 0; i < buffer.size(); i++)
		if (buffer[i] == '\n')
			bufLines++;

	for (int i = 0; i < WindowSizeY-4-6; i++)
	{
		wmove(borderWindow, 1+i, 0);
		wattron(borderWindow, A_REVERSE);
		if (i <= bufLines)
			wprintw(borderWindow, "%3d ", i+1);
		else
			waddstr(borderWindow, "~   ");
		// wattroff(borderWindow, A_REVERSE);
		wrefresh(borderWindow);
	}

	wclear(window);
	for (char c : buffer)
	{
		waddch(window, c);
	}

	wrefresh(window);
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

	Tape tape;
	tape.Update();

	mvaddstr(WindowSizeY-4, 1, "Input: ");
	mvaddstr(WindowSizeY-3, 1, "Output: ");
	refresh();

	Editor editor;
	editor.Update();

	char ch;
	while (true)
	{
		ch = wgetch(editor.window);

		if (ch == 27)
		{

		}

		if (ch == 10 /* \n */ || (ch >= 32 && ch <= 126))
			editor.buffer += ch;

		tape.Update();
		editor.Update();
	}
}

// void simpleInterpreter(std::string code)
// {
// 	char mem[30000] = {0};
// 	int dataPtr = 0;
// 	int openBrackets = 0;
//
// 	for (int i = 0; i < code.size(); i++)
// 	{
// 		char ch = code[i];
//
// 		ptr += ch == '>' ? 1 : ch == '<' ? -1 : 0;
// 		mem[ptr] += ch == '+' ? 1 : ch == '-' ? -1 : 0;
//
// 		if (ch ==  '.')
// 			addch(mem[ptr]);
// 		else if (ch == ',')
// 			mem[ptr] = getch();
// 		else if (ch == '[') {
// 			if (mem[ptr] == 0) {
// 				i++;
// 				while (openBrackets > 0 || code[i] != ']') {
// 					if (code[i] == '[') openBrackets++;
// 					if (code[i] == ']') openBrackets--;
// 					i++;
// 				}
// 			}
// 		} else if (ch == ']') {
// 			i--;
// 			while (openBrackets > 0 || code[i] != '[') {
// 				if (code[i] == ']') openBrackets++;
// 				if (code[i] == '[') openBrackets--;
// 				i--;
// 			}
// 			i--;
// 		}
// 	}
