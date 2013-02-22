#include "brainshag.hpp"

int choice(vector<string> choices, int moveY)
{
	// > vector
	// I am sorry
	const int nchoices = choices.size();
	ITEM* items[nchoices];
	MENU* menu = NULL;

	for(int i = 0; i < nchoices; i++) {
		items[i] = new_item(const_cast<char*>(choices[i].c_str()), "");
	}
	items[nchoices] = (ITEM*)NULL;

	menu = new_menu((ITEM**)items);
	move(moveY, 0);
	post_menu(menu);
	refresh();

	int ch;
	int selectedItem;
	while(ch = getch()) {
		switch (ch) {
			case KEY_DOWN:
				menu_driver(menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(menu, REQ_UP_ITEM);
				break;
			case 10: // enter
				selectedItem = item_index(current_item(menu))+1;
				goto breakbreak;
		}
	}
	breakbreak:

	unpost_menu(menu);
	free_menu(menu);
	for (int i = 0; i < nchoices; i++)
		free_item(items[i]);

	return selectedItem;
}

int main(int argc, char *argv[])
{
	initscr(); keypad(stdscr, true); cbreak();
	getmaxyx(stdscr, windowSizeY, windowSizeX);
	
	printw("Welcome to Brainshag, a visual brainfuck interpreter!");
	mvprintw(1, 0, "Would you like to:");
	vector<string> t;
	t.push_back("1) Simply execute some brainfuck");
	t.push_back("2) Load an IDE or something that is not even done yet");
	switch (choice(t, 3)) {
		case 1:
			simpleBF();
			break;

		case 2:
			clear();
			mvprintw(0, 0, "Not implemented yet.");
	}

	getch();
	endwin();
	
	return 0;
}

void simpleBF()
{
	clear();
	printw("oh geez!");
	/*char code[1000];
	
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
	}*/
}
