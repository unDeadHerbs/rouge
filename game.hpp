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
  RRGame(udh_frame* mf);
  void handel_key(char ch);
};

#endif
