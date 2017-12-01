#ifndef __UDH_NCURSES__
#define __UDH_NCURSES__

#include <ncurses.h>
#include <deque>
#include <string>
#include <utility>

/**
 * A small wrapper for ncurses.
 *
 * This class defines a singelton object for manageing the ncurses
 * library.
 */
class udh_screen{
private:
  WINDOW* win;
  bool refreshed;
  typedef unsigned int uint;
  uint screenRows,screenCols;
  //std::deque<std::deque<char> > next_display; // for if too slow
  std::deque<std::string> display;

  void correctDisplaySize();

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

  /**
   * Draws a rectangle of chars to the screen at a location.
   *
   * @param lines The rectange of chars to draw.
   *
   * @param x The starting column to print in.
   *
   * @param y The strating row to print in.
   */
  void drawToScreen(std::deque<std::string> lines,uint x=0,uint y=0);

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
