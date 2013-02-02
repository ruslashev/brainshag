#include <iostream>
#include <ncurses.h>

// Bracketless Hello world: 	++++++++++>+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.
// Hello world: 				++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.

int windowSizeX, windowSizeY;
int choice(std::string info, int numOfChoices, int moveY)
{
	int ch;
	mvprintw(moveY, 0, info.c_str());
	mvprintw(moveY+numOfChoices+1, 0, "$ ");
	// menus are for sissies
	while ((ch = getch()-48) < 1 || ch > numOfChoices) {
		mvprintw(moveY+numOfChoices+1, 0, "I thought I can trust you dude\n");
		mvprintw(moveY+numOfChoices+2, 0, "$ ");
	}

	return ch;
}

int main(int argc, char *argv[])
{
	initscr(); raw(); keypad(stdscr, true); noecho(); cbreak();
	getmaxyx(stdscr, windowSizeY, windowSizeX);
	
	int ch;
	printw("Welcome to Brainshag, a visual brainfuck interpreter!");
	ch = choice("Would you like to:"														"\n"
				"1) Simply execute some brainfuck"											"\n"
				"2) Load a super-amazing visual IDE or something that is not even done yet"	"\n", 2, 2);

	getch();
	endwin();

	/*
	char mem[30000] = {0};
	std::string code;
	std::cin >> code;
	int ptr = 0;
	int openBrackets = 0;

	for (int i = 0; i < code.length(); i++)
	{
		char ch = code[i];
		
		ptr += ch == '>' ? 1 : ch == '<' ? -1 : 0;
		mem[ptr] += ch == '+' ? 1 : ch == '-' ? -1 : 0;

		if (ch ==  '.')
			std::cout << mem[ptr];
		else if (ch == ',')
			std::cin >> mem[ptr];
		else if (ch == '[') {
			if (mem[ptr] == 0) {
				i++;
				while (openBrackets > 0 || code[i] != ']') {
					if (code[i] == '[') openBrackets++;
					if (code[i] == ']') openBrackets--;
					i++;
				}
			}
		} else if (ch == ']') {
			i--;
			while (openBrackets > 0 || code[i] != '[') {
				if (code[i] == ']') openBrackets++;
				if (code[i] == '[') openBrackets--;
				i--;
			}
			i--;
		}
	}
	*/

	return 0;
}