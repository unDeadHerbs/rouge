#include "game.hpp"
#include "debug.hpp"

using namespace std::string_literals;

RRGame::RRGame(udh_frame *mf) : main_frame(mf) {
	view_size= 7;
	status.resize(1, 40);
	player= map.getSpawn();
	main_frame->place(map.view_port(player, view_size));
	main_frame->place("Status: "s, view_size * 2 + 3);
	main_frame->place(status, view_size * 2 + 3, "Status: "s.size());
}
void RRGame::handel_key(char ch) {
	switch (ch) {
	case 'w':
	case 'W':
		if (map[player.first - 1][player.second] == ' ')
			player.first--;
		else
			status.place("That's a wall!"s);
		break;
	case 'a':
	case 'A':
		if (map[player.first][player.second - 1] == ' ')
			player.second--;
		else
			status.place("That's a wall!"s);
		break;
	case 's':
	case 'S':
		if (map[player.first + 1][player.second] == ' ')
			player.first++;
		else
			status.place("That's a wall!"s);
		break;
	case 'd':
	case 'D':
		if (map[player.first][player.second + 1] == ' ')
			player.second++;
		else
			status.place("That's a wall!"s);
		break;
	case 'q':
	case 'Q':
		running= false;
		debugv("quiting");
		break;
	default:
		break;
	}
	main_frame->place(map.view_port(player, view_size));
	main_frame->place("Status: "s, view_size * 2 + 3);
	main_frame->place(status, view_size * 2 + 3, "Status: "s.size());
	status.clear();
}
