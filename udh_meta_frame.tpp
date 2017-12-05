#ifndef __UDH_META_FRAME_TPP__
#define __UDH_META_FRAME_TPP__

#include "debug.hpp"
#include "udh_meta_frame.hpp"

void udh_meta_frame::kill_kids_outside_house() {
	// loop though kids and remove them if their pos is outside
	// if pos is negitive will have to check child size
}

std::string udh_meta_frame::operator[](uint rhs) const {
	return render()[rhs];
}

char udh_meta_frame::operator[](std::pair<uint, uint> rhs) const {
	return render()[rhs];
}

std::pair<uint, uint> udh_meta_frame::size() const {
	return s;
}

void udh_meta_frame::resize(uint rows, uint cols) {
	s= std::make_pair(rows, cols);
	kill_kids_outside_house();
}

void udh_meta_frame::place(udh_frame &sub_frame, uint row, uint col) {
	place(sub_frame, std::make_pair(row, col));
}

void udh_meta_frame::place(udh_frame &sub_frame, std::pair<uint, uint> pos) {
	// check for if killed
	children.push_back(std::make_pair(pos, &sub_frame));
}

udh_frame udh_meta_frame::clip(uint from_row, uint from_col, uint rows,
                               uint cols) const {
	return render().clip(from_row, from_col, rows, cols);
}

void udh_meta_frame::clear() {
	children.clear();
}

udh_frame udh_meta_frame::render() const {
	udh_frame rendered(s);
	for (auto &c : children) rendered.place(*c.second, c.first);
	return rendered;
}

#endif
