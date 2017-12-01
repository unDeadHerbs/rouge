#ifndef __UDH_FRAME__
#define __UDH_FRAME__

#include <deque>
#include <string>

/**
 * A small wrapper for ncurses.
 *
 * This class defines a singelton object for manageing the ncurses
 * library.
 */
class udh_frame{
private:
  std::deque<std::string> frame;
public:
  std::string& operator[](int rhs);
  void add_row(std::string row);
  std::pair<uint,uint> size()const;
  void resize(uint rows,uint cols);
  void drop_row();
  void place_frame(udh_frame sub_frame,int row=0,int col=0);
  udh_frame clip(uint from_row,uint from_col,uint rows,uint cols);
};

#endif
