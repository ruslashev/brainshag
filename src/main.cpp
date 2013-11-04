#include "main.hpp"
#include "editor.hpp"
#include "tape.hpp"

int ScreenSizeX, ScreenSizeY;

int main(int argc, char *argv[])
{
	initscr();
	keypad(stdscr, true);
	raw(); // cbreak();
	keypad(stdscr, TRUE);
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
	tape.Update();

	mvaddstr(ScreenSizeY-5, 1, "Input: ");
	mvaddstr(ScreenSizeY-4, 1, "Output: ");
	refresh();

	Editor editor(ScreenSizeX, ScreenSizeY);
	editor.Update();

	int ch;
	while (true)
	{
		ch = wgetch(editor.window);

		// if (ch == KEY_BACKSPACE)
		// 	editor.buffer.pop_back();

		if (ch == 27 /* Escape */) {
			break;
		}

		if ((ch >= 32 && ch <= 126)) { // printable chars
			editor.lines[editor.curs.y].data.insert(editor.curs.x, 1, (char)ch);
			editor.curs.x++;
		} else if (ch == 10) { // \n
			std::string deleted = editor.lines[editor.curs.y].data.erase(\
					editor.curs.x, std::string::npos);
			editor.lines.emplace(\
					editor.lines.begin()+editor.curs.y+1, \
					line_t(""));
			editor.bufLines++;
			editor.curs.y++;
			editor.curs.x = 0;
		} else if (ch == KEY_LEFT) {
			editor.curs.x--;
		} else if (ch == KEY_RIGHT) {
			editor.curs.x++;
		} else if (ch == KEY_UP) {
			editor.curs.y--;
		} else if (ch == KEY_DOWN) {
			editor.curs.y++;
		}

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
