#include "editor.hpp"

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
}

void Editor::Update(int ch)
{
	// TODO: switch switches
	switch (mode) {
		case NORMAL:
			switch (ch) {
				case 'i':
					mode = INSERT;
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
					curs.x--;
					break;
				case 'l':
					curs.x++;
					break;
				case 'k':
					curs.y--;
					break;
				case 'j':
					curs.y++;
					break;
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
	for (; i < WindowSizeY-2; i++)
		mvwaddstr(window, i+1, 0, "~");

	wmove(window, curs.y+1, curs.x+4);

	wrefresh(window);
}

