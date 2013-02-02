#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Bracketless Hello world: 	++++++++++>+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->+++++++>++++++++++>+++>+<<<<->++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.
// Hello world: 				++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.

int main(int argc, char *argv[])
{
	char mem[30000] = {0};
	char code[1000];
	fgets(code, 1000, stdin);
	int ptr = 0;
	int openBrackets = 0;

	for (int i = 0; i < strlen(code); i++)
	{
		char ch = code[i];
		
		ptr += ch == '>' ? 1 : ch == '<' ? -1 : 0;
		mem[ptr] += ch == '+' ? 1 : ch == '-' ? -1 : 0;

		if (ch ==  '.')
			putchar(mem[ptr]);
		else if (ch == ',')
			mem[ptr] = getchar();
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