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
  uint size()const;
  void drop_row();
};

#endif
