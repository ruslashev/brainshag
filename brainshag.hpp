#include <fstream>
#include <string>
#include <ncurses.h>

// Bracketless Hello world: 	++++++++++>+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.
// Hello world: 				++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.

void loadInterpreter();

class Tape
{
public:
	WINDOW *window;
	int size;
	int *data;
	int dataPointer;

	void Update();

	Tape();
	~Tape();
};

class Editor
{
public:
	WINDOW *window, *borderWindow;
	std::string buffer;
	int bufLines;

	void Update();

	Editor();
};

