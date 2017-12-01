#include "udh_ncurses.hpp"
#include "debug.hpp"

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

void udh_screen::refreshScreen() {
	if (!refreshed) {
		debug(2, "drawToScreen");
		for (uint row= 0; row < display.size().first; row++) {
			wmove(win, row, 0);
			waddstr(win, display[row].c_str());
		}
		wmove(win, cursor.first, cursor.second);
		wrefresh(win); // i'm think that this is an expensive call
		refreshed= true;
	}
}

void udh_screen::drawToScreen(udh_frame lines, uint row, uint col) {
	refreshed= false;
	debug(2, "drawToBuffer");
	for (uint r= 0;
	     r + row < display.size().first && r < lines.size().first; r++) {
		for (uint c= 0;
		     c + col < display[r].size() && c < lines[r].size(); c++) {
			debug(5, "update display location " + std::to_string(r)
			             + "," + std::to_string(c) + " to "
			             + lines[r].c_str()[c]);
			display[r + row][c + col]= lines[r].c_str()[c];
		}
	}
}

void udh_screen::screenResizedTriger(int code) {
	debug(1, "screenResizedTriger: " + std::to_string(code));
	getmaxyx(win, screenRows, screenCols);
	refreshed= false;
	refreshScreen();
}

int udh_screen::getKey() const {
	return getch();
}

std::pair<uint, uint> udh_screen::size() const {
	return std::make_pair(screenRows, screenCols);
}
