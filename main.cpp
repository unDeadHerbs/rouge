#include <string>
using std::string;
#include <deque>
using std::deque;

#include "udh_ncurses.hpp"
#include "debug.hpp"

int main(){
  debug("starting");
  udh_screen Screen;
  usleep(1*1000*1000);
  deque<string> new_rows;
  new_rows.push_back("row one");
  new_rows.push_back("row two");
  Screen.drawToScreen(new_rows);
  usleep(3*1000*1000);
  Screen.refreshScreen();
  usleep(3*1000*1000);
  return 0;
}
