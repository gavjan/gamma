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
#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_RIGHT 67
#define KEY_LEFT 68


int detect_key(int* buff, int ptr) {
	ptr=(ptr+1)%3;
	if(buff[(ptr+1)%3]==27 && buff[(ptr+2)%3]==91) {
		if(buff[(ptr+3)%3]==65) return KEY_UP;
		if(buff[(ptr+3)%3]==66) return KEY_DOWN;
		if(buff[(ptr+3)%3]==67) return KEY_RIGHT;
		if(buff[(ptr+3)%3]==68) return KEY_LEFT;
	}
	return UNKNOWN;
}
int get_key() {
	int c = getch();
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
	int c = 0;
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
		}

	}

	return 0;
}
