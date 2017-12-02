#ifndef __ROUGE_ROUGE_GAME__
#define __ROUGE_ROUGE_GAME__

#include "udh_frame.hpp"
#include "map.hpp"

/**
 */
class RRGame{
private:
  std::pair<uint, uint> player;
  udh_frame* main_frame;
  RRMap map;
public:
  bool running=true;
  RRGame(udh_frame* mf):main_frame(mf){
    main_frame->place(map);
    player=map.getSpawn();
  }
  void handel_key(char ch){
    switch (ch) {
    case 'w':case 'W':
      if (map[player.first - 1][player.second] == ' ')
	player.first--;
      break;
    case 'a':case 'A':
      if (map[player.first][player.second - 1] == ' ')
	player.second--;
      break;
    case 's':case 'S':
      if (map[player.first + 1][player.second] == ' ')
	player.first++;
      break;
    case 'd':case 'D':
      if (map[player.first][player.second + 1] == ' ')
	player.second++;
      break;
    case 'q':case 'Q':
      running=false;
      debugv("quiting");
      break;
    default:
      break;
    }
    main_frame->place(map);
    main_frame->place('@',player);
  }
};

#endif
