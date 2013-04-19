#include <fstream>
#include <ncurses.h>

// Bracketless Hello world: 	++++++++++>+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.
// Hello world: 				++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.

using namespace std;

void loadInterpreter();

/*
void simpleBF()
{
	clear();
	char code[1000];
	
	clear();
	printw("Enter your code:\n");
	getstr(code);
	
	clear();
	attron(A_REVERSE);
	printw("Program output: ");
	attroff(A_REVERSE);
	chgat(-1, A_REVERSE, 0, NULL);
	move(1, 0);

	char mem[30000] = {0};
	int ptr = 0;
	int openBrackets = 0;

	for (int i = 0; i < strlen(code); i++) {
		char ch = code[i];
		
		ptr += ch == '>' ? 1 : ch == '<' ? -1 : 0;
		mem[ptr] += ch == '+' ? 1 : ch == '-' ? -1 : 0;

		if (ch ==  '.')
			addch(mem[ptr]);
		else if (ch == ',')
			mem[ptr] = getch();
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
