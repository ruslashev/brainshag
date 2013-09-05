#include "main.hpp"
#include "editor.hpp"
#include "tape.hpp"

int WindowSizeX, WindowSizeY;

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

void loadInterpreter()
{
	Tape tape;
	tape.Update();

	mvaddstr(WindowSizeY-4, 1, "Input: ");
	mvaddstr(WindowSizeY-3, 1, "Output: ");
	refresh();

	Editor editor(WindowSizeX, WindowSizeY);
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
