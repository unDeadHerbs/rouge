#include "debug.hpp"
#include "udh_frame.hpp"
#include "udh_ncurses.hpp"

int main() {
	udh_screen Screen;
	auto &main_frame= Screen.frame();

	udh_frame map; // make a constructor for this
	map.add_row("+-------+ +-------+");
	map.add_row("|       | |       |");
	map.add_row("|       | |       |");
	map.add_row("|       | |       |");
	map.add_row("+--+ +--+ +--+ +--+");
	map.add_row("   | |       | |   ");
	map.add_row("+--+ +-------+ +--+");
	map.add_row("|                 |");
	map.add_row("+-----------------+");

	main_frame.place(map);

	std::pair<uint, uint> me= {2, 4};

	char ch;
	do {
		main_frame.place(map);
		main_frame.place('@', me);

		Screen.refreshScreen();
		ch= Screen.getKey();
		debugv(2, "got key " + std::to_string(ch));
		switch (ch) {
		case 'w':
			if (map[me.first - 1][me.second] == ' ') me.first--;
			break;
		case 'a':
			if (map[me.first][me.second - 1] == ' ') me.second--;
			break;
		case 's':
			if (map[me.first + 1][me.second] == ' ') me.first++;
			break;
		case 'd':
			if (map[me.first][me.second + 1] == ' ') me.second++;
			break;
		case 'q':
			break;
			debugv("quiting");
			break;
		default:
			break;
		}
	} while (ch != 'q');

	return 0;
}
