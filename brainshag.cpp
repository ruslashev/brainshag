#include <iostream>

// Bracketless Hello world: 	++++++++++>+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.
// Hello world: 				++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.

int main(int argc, char *argv[])
{
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

	return 0;
}