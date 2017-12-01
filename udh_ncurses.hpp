#ifndef __UDH_NCURSES__
#define __UDH_NCURSES__

#include <utility>
#include "udh_frame.hpp"

/**
 * A small wrapper for ncurses.
 *
 * This class defines a singelton object for manageing the ncurses
 * library.
 */
class udh_screen{
private:
  /*
   * This is a pointer to a WINDOW object in ncurses, but the ncurses
   * libaray makes a bunch of globabl variables so i'm encapsulating
   * it in udh_frame.cpp where it won't bother anything else.
   */
  void* win;
  typedef unsigned int uint;
  uint screenRows,screenCols;
  //std::deque<std::deque<char> > next_display; // for if too slow
  udh_frame display;

  /**
   * Anti-Copy Constructor
   *
   * Making a private copy constructor to prevent usage.
   */
  udh_screen(udh_screen const&){}

  /**
   * Anti-Asignment Operator
   *
   * Making a prevent asignment operator to prevent usage.
   */
  udh_screen operator=(udh_screen const&){return *this;}
public:
  std::pair<uint,uint> cursor;
  udh_screen();
  ~udh_screen();

  udh_frame& frame();

  /**
   * Actuly render the chars to the screen.
   */
  void refreshScreen();

  /**
   * re-check the size of the screen.
   */
  void screenResizedTriger(int code);

  /**
   * Read in one char from the user.
   */
  int getKey()const;

  std::pair<uint,uint> size()const;
};

#endif
