#include <string>
using std::string;
#include <deque>
using std::deque;

#include "debug.hpp"
#include "udh_ncurses.hpp"

int main() {
	debug("starting");

	udh_screen Screen;
	usleep(1 * 1000 * 1000);

	deque<string> new_rows;
	new_rows.push_back("row one");
	new_rows.push_back("row two");
	Screen.drawToScreen(new_rows);
	usleep(1 * 1000 * 1000);
	Screen.refreshScreen();
	usleep(1 * 1000 * 1000);

	deque<string> test2;
	test2.push_back("this is");
	test2.push_back("some text");
	test2.push_back("row three");
	Screen.drawToScreen(test2, 20, 20);
	usleep(1 * 1000 * 1000);
	Screen.refreshScreen();
	usleep(1 * 1000 * 1000);

	deque<string> prompt;
	prompt.push_back("type here:");
	Screen.drawToScreen(prompt, 20,0);
	Screen.cursor= std::make_pair(20,prompt[0].size());
	Screen.refreshScreen();
	usleep(3 * 1000 * 1000);
	return 0;
}
