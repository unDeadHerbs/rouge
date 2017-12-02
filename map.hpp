#ifndef __ROUGE_ROUGE_MAP__
#define __ROUGE_ROUGE_MAP__

#include <utility>
#include "udh_frame.hpp"

/**
 */
class RRMap{
private:
  udh_frame map;
  std::pair<uint, uint> spawn= {2, 4};
public:
  RRMap(){
    map.add_row("+-------+ +-------+");
    map.add_row("|       | |       |");
    map.add_row("|       | |       |");
    map.add_row("|       | |       |");
    map.add_row("+--+ +--+ +--+ +--+");
    map.add_row("   | |       | |   ");
    map.add_row("+--+ +-------+ +--+");
    map.add_row("|                 |");
    map.add_row("+-----------------+");
  }
  std::pair<uint,uint> getSpawn()const{return spawn;}
  operator udh_frame&(){
    return map;
  }
  std::string operator[](uint rhs) {
	return map[rhs];
  }
  
  char operator[](std::pair<uint, uint> rhs) {
    return map[rhs];
  }
  udh_frame view_port(std::pair<uint,uint> player, uint r){
    udh_frame vp(2*r+1);
    vp.place(map,std::make_pair(r-player.first,r-player.second));
    vp.place('@',r,r);
    return vp;
  }
};

#endif
