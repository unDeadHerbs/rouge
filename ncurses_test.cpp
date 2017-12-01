#include "debug.hpp"
#include "udh_frame.hpp"
#include "udh_ncurses.hpp"

int main() {
	debug("starting");

	udh_screen Screen;
	usleep(1 * 1000 * 1000);
	auto &main_frame= Screen.frame();

	udh_frame new_rows;
	new_rows.add_row("row one");
	new_rows.add_row("row two");
	main_frame.place_frame(new_rows);
	usleep(1 * 1000 * 1000);
	Screen.refreshScreen();
	usleep(1 * 1000 * 1000);

	udh_frame test2;
	test2.add_row("this is");
	test2.add_row("some text");
	test2.add_row("row three");
	main_frame.place_frame(test2, 20, 20);
	usleep(1 * 1000 * 1000);
	Screen.refreshScreen();
	usleep(1 * 1000 * 1000);

	udh_frame prompt;
	prompt.add_row("type here:");
	main_frame.place_frame(prompt, 20, 0);
	Screen.cursor= std::make_pair(20, prompt[0].size());
	Screen.refreshScreen();
	usleep(3 * 1000 * 1000);
	return 0;
}
