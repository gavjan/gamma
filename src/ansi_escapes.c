/** @file
 * Source file providing functions for interacting with the
 * terminal
 * @author Gevorg Chobanyan
 * @date 11.04.2020
 */
#include "ansi_escapes.h"
#include "ui.h"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
void set_text_color(int code) {
	printf("\x1b[%dm", code);
}
int get_key(game_t* t, int c) {
	if(c == NO_KEY) c = getch(t);
	if(c == CTRL_D) return KEY_CTRL_D;
	if(c == LOWER_C || c == UPPER_C) return KEY_C;
	if(c == LOWER_G || c == UPPER_G) return KEY_G;
	if(c == SPACE) return KEY_SPACE;
	if(c == ESCAPE_CODE) {
		c = getch(t);
		if(c == ESCAPE_BRACKET) {
			c = getch(t);
			if(c == UP_CODE) return KEY_UP;
			if(c == DOWN_CODE) return KEY_DOWN;
			if(c == RIGHT_CODE) return KEY_RIGHT;
			if(c == LEFT_CODE) return KEY_LEFT;
		} else return get_key(t, c);
	}
	return UNKNOWN;
}
int getch(game_t* t) {
	int ch;
	safe_exec(tcgetattr(STDIN_FILENO, &(t->original_terminal)));
	t->new_terminal = t->original_terminal;
	t->new_terminal.c_lflag &= ~(ICANON | ECHO);
	safe_exec(tcsetattr(STDIN_FILENO, TCSANOW, &(t->new_terminal)));
	ch = getchar();
	safe_exec(tcsetattr(STDIN_FILENO, TCSANOW, &(t->original_terminal)));

	return ch;
}
int setup_console(game_t* t) {
	safe_exec(tcgetattr(STDIN_FILENO, &(t->original_terminal)));
	t->new_terminal = t->original_terminal;
	t->new_terminal.c_lflag &= ~(ICANON | ECHO);
	safe_exec(tcsetattr(STDIN_FILENO, TCSANOW, &(t->new_terminal)));
	return SUCCESS;
}
int restore_console(game_t* t) {
	// Reset colors
	printf("\x1b[0m");

	// Reset console mode
	safe_exec(tcsetattr(STDIN_FILENO, TCSANOW, &(t->original_terminal)));
	return SUCCESS;
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
void move_to(int row, int column) {
	printf("\x1b[%d;%df", row, column);
}
