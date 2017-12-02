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
  uint view_size;
  std::string status;
  uint status_length;
public:
  bool running=true;
  RRGame(udh_frame* mf):main_frame(mf){
    view_size=7;
    status_length=40;
    player=map.getSpawn();
    main_frame->place(map.view_port(player,view_size));
    main_frame->place("Status: " + status,view_size*2+3);
  }
  void handel_key(char ch){
    switch (ch) {
    case 'w':case 'W':
      if (map[player.first - 1][player.second] == ' '){
	player.first--;
      	status="";
	  }else
	status="That's a wall!";
      break;
    case 'a':case 'A':
      if (map[player.first][player.second - 1] == ' '){
	player.second--;
	status="";
		  }else
	status="That's a wall!";
      break;
    case 's':case 'S':
      if (map[player.first + 1][player.second] == ' '){
	player.first++;
	status="";
      }else
	status="That's a wall!";
      break;
    case 'd':case 'D':
      if (map[player.first][player.second + 1] == ' '){
	player.second++;
      status="";
      }else
	status="That's a wall!";
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
