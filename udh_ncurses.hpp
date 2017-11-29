#include <ncurses.h>
#include <deque>
#include <string>

class udh_screen{
private:
  WINDOW* win;
  bool refreshed;
  typedef unsigned int uint;
  uint cursorRow, cursorCol,screenRows,screenCols;
  std::deque<std::deque<char> > diffabledisplay;

  void correctDiffabledisplaySize();
public:
  udh_screen();
  ~udh_screen();
  void drawToScreen(std::deque<std::string> lines);
  void refreshScreen();
  void screenResizedTriger(int code);
  int getKey();
};
