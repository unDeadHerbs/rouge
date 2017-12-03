#ifndef __UDH_META_FRAME__
#define __UDH_META_FRAME__

#include "udh_frame.hpp"
#include <vector>
#include <utility>
#include <string>

/**
 */


template <bool autoRender=true>
class udh_meta_frame;

template <>
class udh_meta_frame<false>{
private:
  std::vector<std::pair<std::pair<int,int>,udh_frame*> > children;
  //TODO:make these weak pointers to the frame's internal buffer
  udh_frame rendered;
  void kill_kids_outside_house();
public:
  std::string operator[](uint rhs)const;
  char operator[](std::pair<uint,uint> rhs)const;
  std::pair<uint,uint> size()const;
  void resize(uint rows,uint cols);
  void drop_row();
  void place(udh_frame& sub_frame,uint row=0,uint col=0);
  void place(udh_frame& sub_frame,std::pair<uint,uint> pos);
  udh_frame clip(uint from_row,uint from_col,uint rows,uint cols)const;
  void clear();
  udh_frame render();
};

template <>
class udh_meta_frame<true>{
private:
  std::vector<std::pair<std::pair<uint,uint>,udh_frame*> > children;
  //TODO:make these weak pointers to the frame's internal buffer
  std::pair<uint,uint> s;
  void kill_kids_outside_house();
public:
  std::string operator[](uint rhs)const;
  char operator[](std::pair<uint,uint> rhs)const;
  std::pair<uint,uint> size()const;
  void resize(uint rows,uint cols);
  void drop_row();
  void place(udh_frame& sub_frame,uint row=0,uint col=0);
  void place(udh_frame& sub_frame,std::pair<uint,uint> pos);
  udh_frame clip(uint from_row,uint from_col,uint rows,uint cols)const;
  void clear();
  udh_frame render()const;
};

#include "udh_meta_frame.tpp"

#endif
