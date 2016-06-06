#include "editor.hh"

Editor::Editor(int newScreenSizeX, int newScreenSizeY)
{
	ScreenSizeX = newScreenSizeX;
	ScreenSizeY = newScreenSizeY;

	WindowSizeX = ScreenSizeX;
	WindowSizeY = ScreenSizeY-4-5;
	window = newwin(WindowSizeY, WindowSizeX, 4, 0);

	curs.x = curs.y = 0;
	lines.push_back("");

	mode = NORMAL;

	commandBuf = "";
}

void Editor::Update(int ch)
{
	switch (mode) {
		case NORMAL:
			switch (ch) {
				case 'i':
					mode = INSERT;
					break;
				case 'x':
					if (curs.x < lines[curs.y].size())
						lines[curs.y].replace(curs.x, lines[curs.y].size()-curs.x,
								lines[curs.y], curs.x+1, lines[curs.y].size()-curs.x-1);
					break;
				case 'X':
					if (curs.x < lines[curs.y].size() && curs.x != 0) {
						lines[curs.y].replace(curs.x-1, lines[curs.y].size()-curs.x,
								lines[curs.y], curs.x, lines[curs.y].size()-curs.x-1);
						curs.x--;
					} else if (curs.x == lines[curs.y].size() && curs.x != 0) {
						lines[curs.y].pop_back();
						curs.x--;
					}
					break;
				case 'o':
					lines.emplace(lines.begin()+curs.y+1, "");
					curs.y++;
					curs.x = 0;
					break;
				case 'O':
					lines.emplace(lines.begin()+curs.y, "");
					curs.y--;
					curs.x = 0;
					break;
				case 'h':
					if (curs.x > 0)
						curs.x--;
					break;
				case 'l':
					if (curs.x < lines[curs.y].size())
						curs.x++;
					break;
				case 'k':
					if (curs.y > 0)
						curs.y--;
					break;
				case 'j':
					if (curs.y < lines.size()-1)
						curs.y++;
					break;
				case ':':
					mode = COMMAND;
				default:
					break;
			}
			break;
		case INSERT:
			switch (ch) {
				case 10: // \n
				{
					std::string head = "", tail = "";
					int i = 0;
					for (; i < curs.x; i++)
						head += lines[curs.y][i];
					for (; i < lines[curs.y].size(); i++)
						tail += lines[curs.y][i];
					lines[curs.y] = head;
					lines.emplace(lines.begin()+curs.y+1, tail);
					curs.y++;
					curs.x = 0;
					break;
				}
				case 9: // \t
					mode = NORMAL;
					break;
				default:
					if (ch >= 32 && ch <= 126) { // printable
						lines[curs.y].insert(curs.x, 1, (char)ch);
						curs.x++;
					}
			}
			break;
		case COMMAND:
			char buf[80];
			echo();
			mvwaddch(window, WindowSizeY-2, 1, ch);
			wgetnstr(window, buf, 80);
			noecho();
			commandBuf = ch;
			commandBuf += buf;
			if (commandBuf == "quit" || commandBuf == "q") {
				endwin();
				exit(0);
			} else if (commandBuf == "compile" || commandBuf == "co") {

			}
			mode = NORMAL;
			break;
	}
}

void Editor::Redraw()
{
	// Note from past self: wrap words at > WindowSizeX - 5

	wclear(window);

	for (int x = 0; x < WindowSizeX; x++) {
		mvwaddch(window, 0, x, ACS_HLINE);
		mvwaddch(window, WindowSizeY-1, x, ACS_HLINE);
	}
	mvwaddstr(window, 0, 1, mode == NORMAL ? " NORMAL " : " INSERT ");

	int i = 0;
	for (; i < lines.size(); i++)
		mvwprintw(window, i+1, 0, "%3d %s", i+1, lines[i].c_str());
	for (; i < WindowSizeY-3; i++)
		mvwaddstr(window, i+1, 0, "~");

	if (mode == COMMAND) {
		mvwaddch(window, WindowSizeY-2, 0, ':');
		waddstr(window, commandBuf.c_str());
	} else
		wmove(window, curs.y+1, curs.x+4);

	wrefresh(window);
}

