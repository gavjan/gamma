#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int getch(void) {
	int ch;
	struct termios oldt, newt;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON|ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	return ch;
}
#define UNKNOWN 0
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_RIGHT 3
#define KEY_LEFT 4
#define KEY_SPACE 5
#define KEY_G 6
#define KEY_C 7

int get_key() {
	int c = getch();
	if(c==99 || c==67) return KEY_C;
	if(c==103 || c==71) return KEY_G;
	if(c==32) return KEY_SPACE;
	if(c==27 && getch()==91) {
		c=getch();
		if(c==65) return KEY_UP;
		if(c==66) return KEY_DOWN;
		if(c==67) return KEY_RIGHT;
		if(c==68) return KEY_LEFT;
	}
	return UNKNOWN;
}

int main() {
	while(1) {
		switch(get_key()) {
			case KEY_UP:
				printf("Up\n");
				break;
			case KEY_DOWN:
				printf("Down\n");
				break;
			case KEY_LEFT:
				printf("Left\n");
				break;
			case KEY_RIGHT:
				printf("Right\n");
				break;
			case KEY_SPACE:
				printf("Space\n");
				break;
			case KEY_G:
				printf("G\n");
				break;
			case KEY_C:
				printf("C\n");
				break;
		}

	}

	return 0;
}
