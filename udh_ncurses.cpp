#include "udh_ncurses.hpp"
#include "debug.hpp"
#include <ncurses.h>

udh_screen::udh_screen() {
	static bool first= true;
	assert(first);
	first= false;

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	getmaxyx(stdscr, screenRows, screenCols);
	debug(2, "screen size set to " + std::to_string(screenRows) + ":"
	             + std::to_string(screenCols));
	win= newwin(screenRows, screenCols, 0, 0);
	display.resize(screenRows, screenCols);
	cursor= std::make_pair(screenRows - 1, screenCols - 1);
	refreshScreen();
}

udh_screen::~udh_screen() {
	endwin();
}

udh_frame &udh_screen::frame() {
	return display;
}

void udh_screen::refreshScreen() {
	debug(2, "drawToScreen");
	for (uint row= 0; row < display.size().first; row++) {
		wmove((WINDOW *)win, row, 0);
		waddstr((WINDOW *)win, display[row].c_str());
	}
	wmove((WINDOW *)win, cursor.first, cursor.second);
	wrefresh((WINDOW *)win);
}

void udh_screen::screenResizedTriger(int code) {
	debug(1, "screenResizedTriger: " + std::to_string(code));
	getmaxyx((WINDOW *)win, screenRows, screenCols);
	refreshScreen();
}

int udh_screen::getKey() const {
	return getch();
}

std::pair<uint, uint> udh_screen::size() const {
	return std::make_pair(screenRows, screenCols);
}
