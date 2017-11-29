#include "udh_ncurses.hpp"
#include "debug.hpp"

udh_screen::udh_screen(){
  static bool first=true;
  assert(first);
  first=false;
  win=0;
  initilizeNcurses();
}
udh_screen::~udh_screen(){
  distructScreen();
}

void udh_screen::correctDiffabledisplaySize(){
  debug(3,"correctDiffabledisplaySize");
  debug(4,"setting size to "+std::to_string(screenRows)+":"+std::to_string(screenCols));
  if(diffabledisplay.size()!=0){
    debugv(4,"size was "+std::to_string(diffabledisplay.size())+":"+std::to_string(diffabledisplay[0].size()));
  }else{
    debugv(4,"size was 0:0");
  }
  if(diffabledisplay.size()!=screenRows){
    for(uint i=diffabledisplay.size();i<screenRows;i++){
      diffabledisplay.push_back(std::deque<char>(' '));
    }
    for(uint i=diffabledisplay.size();i>screenRows;i--){
      diffabledisplay.pop_back();
    }
  }
  if(diffabledisplay.size() && diffabledisplay[0].size()!=screenCols){
    for(uint j=0;j<diffabledisplay.size();j++){
      debugv(5,"row size was "+std::to_string(diffabledisplay[j].size()));
      for(uint i=diffabledisplay[j].size();i<screenCols;i++){
	diffabledisplay[j].push_back(' ');
      }
      for(uint i=diffabledisplay[j].size();i>screenCols;i--){
	diffabledisplay[j].pop_back();
      }
      debugv(5,"row size is now "+std::to_string(diffabledisplay[j].size()));
    }
  }
  if(diffabledisplay.size()!=0){
    debugv(4,"size is now "+std::to_string(diffabledisplay.size())+":"+std::to_string(diffabledisplay[0].size()));
  }else{
    debugv(4,"size is now 0:0");
  }
}

void udh_screen::initilizeNcurses(){
  initscr();
  cbreak();
  noecho();
  keypad(stdscr,TRUE);
  nodelay(stdscr,TRUE);
  getmaxyx(stdscr,screenRows,screenCols);
  debug(2,"screen size set to "+std::to_string(screenRows)+":"+std::to_string(screenCols));
  win=newwin(screenRows,screenCols,0,0);
  //mainbuffer.setSize(screenRows,screenCols);
  correctDiffabledisplaySize();
  refreshScreen();
}

void udh_screen::refreshScreen(){
  if(!refreshed){
    //clear();
    wrefresh(win);
    //refresh();
    //doupdate();
    //redrawwin(win);
    refreshed=true;
  }
  //return false;
}

void udh_screen::drawToScreen(std::deque<std::string> lines){
  //TODO ablility to update a rectangle of the screen
  debug(2,"drawToScreen");
  for(uint r=0;r<diffabledisplay.size()&&r<lines.size();r++){
    if(r<lines.size()){
      debugv(2,lines[r]);
      debugv(2,"cliping to length"+std::to_string(diffabledisplay[r].size()));
    }
    for(uint c=0;c<diffabledisplay[r].size()&&c<lines[r].size();c++){
      wmove(win,r,c);
      debugv(5,"diffabledisplay cursor moved");
      if(lines[r]/*.c_str()*/[c]!=diffabledisplay[r][c]){
	debug(5,"update diffabledisplay location "+std::to_string(r)+","+std::to_string(c)+" to "+lines[r].c_str()[c]);
	diffabledisplay[r][c]=lines[r].c_str()[c];
	waddch(win,lines[r].c_str()[c]);
      }
    }
  }
}

void udh_screen::updateScreen(){
  debug(2,"updating screen");
  correctDiffabledisplaySize();
  auto lines=std::deque<std::string>();//=mainbuffer.screen();
  for(auto l:lines){
    debug(2,l);
  }
  drawToScreen(lines);
  //mainbuffer.getCursor(cursorRow,cursorCol);
  wmove(win,cursorRow,cursorCol);
  refreshed=false;
  debug(2,"refresh");
  refreshScreen();
}

void udh_screen::screenResizedTriger(int code){
  debug(1,"screenResizedTriger: "+std::to_string(code));
  getmaxyx(win,screenRows,screenCols);
  //mainbuffer.setSize(screenRows,screenCols);
  refreshed=false;
  updateScreen();
}

void udh_screen::distructScreen(){
  endwin();
}

int udh_screen::getKey(){
  int ch;
  ch=getch();
  return ch;
}
