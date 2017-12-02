#include "debug.hpp"

#include "game.hpp"
#include "udh_ncurses.hpp"

int main() {
	udh_screen Screen;

	RRGame game(&Screen.frame());
	while (game.running) {
		Screen.refreshScreen();
		game.handel_key(Screen.getKey());
	}
	return 0;
}
