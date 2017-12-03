#ifndef __ROUGE_ROUGE_GAME__
#define __ROUGE_ROUGE_GAME__

#include "udh_frame.hpp"
#include "map.hpp"

using namespace std::string_literals;

/**
 */
class RRGame{
private:
  std::pair<uint, uint> player;
  udh_frame* main_frame;
  RRMap map;
  uint view_size;
  udh_frame status;
public:
  bool running=true;
  RRGame(udh_frame* mf):main_frame(mf){
    view_size=7;
    status.resize(1,40);
    player=map.getSpawn();
    main_frame->place(map.view_port(player,view_size));
    main_frame->place("Status: "s,view_size*2+3);
    main_frame->place(status,view_size*2+3,"Status: "s.size());
  }
  void handel_key(char ch){
    switch (ch) {
    case 'w':case 'W':
      if (map[player.first - 1][player.second] == ' ')
	player.first--;
      else
	status.place("That's a wall!"s);
      break;
    case 'a':case 'A':
      if (map[player.first][player.second - 1] == ' ')
	player.second--;
      else
	status.place("That's a wall!"s);
      break;
    case 's':case 'S':
      if (map[player.first + 1][player.second] == ' ')
	player.first++;
      else
	status.place("That's a wall!"s);
      break;
    case 'd':case 'D':
      if (map[player.first][player.second + 1] == ' ')
	player.second++;
      else
	status.place("That's a wall!"s);
      break;
    case 'q':case 'Q':
      running=false;
      debugv("quiting");
      break;
    default:
      break;
    }
    main_frame->place(map.view_port(player,view_size));
    main_frame->place("Status:" + std::string(status_length,' '),view_size*2+3);
    main_frame->place("Status:" + status,view_size*2+3);
  }
};

#endif
