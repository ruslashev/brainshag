#include "main.hpp"
#include "editor.hpp"
#include "tape.hpp"

int ScreenSizeX, ScreenSizeY;

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
		editor.Update();

		ch = wgetch(editor.window);

		if (ch == 'h') {
			editor.curs.x--;
		} else if (ch == 'l') {
			editor.curs.x++;
		} else if (ch == 'k') {
			editor.curs.y--;
		} else if (ch == 'j') {
			editor.curs.y++;
		} else if (ch >= 32 && ch <= 126) { // printable
			editor.lines[editor.curs.y].insert(editor.curs.x, 1, (char)ch);
			editor.curs.x++;
		} else if (ch == 10) { // \n
			std::string head = "", tail = "";
			int i = 0;
			for (; i < editor.curs.x; i++)
				head += editor.lines[editor.curs.y][i];
			for (; i < editor.lines[editor.curs.y].size(); i++)
				tail += editor.lines[editor.curs.y][i];
			editor.lines[editor.curs.y] = head;
			editor.lines.emplace(editor.lines.begin()+editor.curs.y+1, tail);
			editor.curs.y++;
			editor.curs.x = 0;
			editor.Update();
		} else if (ch == 27) // Escape
			break;
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
