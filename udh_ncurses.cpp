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
	correctDisplaySize();
	refreshScreen();
}

udh_screen::~udh_screen() {
	endwin();
}

void udh_screen::correctDisplaySize() {
	debug(3, "correctDisplaySize");
	debug(4, "setting size to " + std::to_string(screenRows) + ":"
	             + std::to_string(screenCols));
	debugv(4, "size was " + std::to_string(display.size()) + ":"
	              + std::to_string(display.size() ? display[0].size() : 0));
	if (display.size() != screenRows) {
		for (uint i= display.size(); i < screenRows; i++)
			display.push_back("");
		for (uint i= display.size(); i > screenRows; i--)
			display.pop_back();
	}
	if (display.size() && display[0].size() != screenCols) {
		for (uint j= 0; j < display.size(); j++) {
			debugv(5, "row size was "
			              + std::to_string(display[j].size()));
			for (uint i= display[j].size(); i < screenCols; i++)
				display[j].push_back(' ');
			for (uint i= display[j].size(); i > screenCols; i--)
				display[j].pop_back();
			debugv(5, "row size is now "
			              + std::to_string(display[j].size()));
		}
	}
	if (display.size() != 0)
		debugv(4, "size is now " + std::to_string(display.size()) + ":"
		              + std::to_string(display[0].size()));
	else
		debugv(4, "size is now 0:0");
}

void udh_screen::refreshScreen() {
	if (!refreshed) {
		debug(2,"drawToScreen");
		for (uint row= 0; row < display.size(); row++) {
			wmove(win, row, 0);
			waddstr(win, display[row].c_str());
		}
		wrefresh(win); // i'm guessing that this is an expensive call
		refreshed= true;
		wmove(win,cursorRow,cursorCol);
	}
}

void udh_screen::drawToScreen(std::deque<std::string> lines, uint x, uint y) {
	refreshed= false;
	debug(2, "drawToBuffer");
	for (uint r= 0; r + y < display.size() && r < lines.size(); r++) {
		for (uint c= 0;
		     c + x < display[r].size() && c < lines[r].size(); c++) {
			debug(5, "update display location " + std::to_string(r)
			             + "," + std::to_string(c) + " to "
			             + lines[r].c_str()[c]);
			display[r + y][c + x]= lines[r].c_str()[c];
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
