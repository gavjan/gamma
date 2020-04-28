#include "ansi_escapes.h"
#include "ui.h"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>


int get_key(game_t* t) {
	int c = getch(t);
	if(c == 99 || c == 67) return KEY_C;
	if(c == 103 || c == 71) return KEY_G;
	if(c == 32) return KEY_SPACE;
	if(c == 27 && getch(t) == 91) {
		c = getch(t);
		if(c == 65) return KEY_UP;
		if(c == 66) return KEY_DOWN;
		if(c == 67) return KEY_RIGHT;
		if(c == 68) return KEY_LEFT;
	}
	return UNKNOWN;
}
int getch(game_t* t) {
	int ch;
	tcgetattr(STDIN_FILENO, &(t->original_terminal));
	t->new_terminal = t->original_terminal;
	t->new_terminal.c_lflag &= ~(ICANON|ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &(t->new_terminal));
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &(t->original_terminal));

	return ch;
}
void setup_console(game_t* t) {
	tcgetattr(STDIN_FILENO, &(t->original_terminal));
	t->new_terminal = t->original_terminal;
	t->new_terminal.c_lflag &= ~(ICANON|ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &(t->new_terminal));
}

void restore_console(game_t* t) {
	// Reset colors
	printf("\x1b[0m");

	// Reset console mode
	tcsetattr(STDIN_FILENO, TCSANOW, &(t->original_terminal));
}
void clear_screen() {
	printf("\x1b[%dJ", CLEAR_ALL);
}

void clear_line() {
	printf("\x1b[%dK", CLEAR_ALL);
}

void cursor_up() {
	printf("\x1b[%dA", MOVE_BY_ONE);
}

void cursor_down() {
	printf("\x1b[%dB", MOVE_BY_ONE);
}

void cursor_right() {
	printf("\x1b[%dC", MOVE_BY_ONE);
}

void cursor_left() {
	printf("\x1b[%dD", MOVE_BY_ONE);
}
void move_to(int row, int col) {
	printf("\x1b[%d;%df", row, col);
}
