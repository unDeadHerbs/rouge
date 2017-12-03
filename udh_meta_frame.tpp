#ifndef __UDH_META_FRAME_TPP__
#define __UDH_META_FRAME_TPP__

#include "debug.hpp"
#include "udh_meta_frame.hpp"

template <bool autoRender>
void udh_meta_frame<autoRender>::kill_kids_outside_house() {
	// loop though kids and remove them if their pos is outside
	// if pos is negitive will have to check child size
}

template <>
std::string udh_meta_frame<false>::operator[](uint rhs) const {
	return rendered[rhs];
}

template <>
std::string udh_meta_frame<true>::operator[](uint rhs) const {
	return render()[rhs];
}

template <>
har udh_meta_frame<false>::operator[](std::pair<uint, uint> rhs) const {
	return rendered[rhs];
}

template <>
har udh_meta_frame<true>::operator[](std::pair<uint, uint> rhs) const {
	return render()[rhs];
}

template <>
std::pair<uint, uint> udh_meta_frame<false>::size() const {
	return rendered.size();
}

template <>
std::pair<uint, uint> udh_meta_frame<true>::size() const {
	return s;
}

template <>
void udh_meta_frame<false>::resize(uint rows, uint cols) {
	rendered.resize(rows, cols);
	kill_kids_outside_house();
}

template <>
void udh_meta_frame<true>::resize(uint rows, uint cols) {
	s= std::make_pair(rows, cols);
	kill_kids_outside_house();
}

template <>
void udh_meta_frame<false>::drop_row() {
	rendered.drop_row();
	kill_kids_outside_house();
}

template <>
void udh_meta_frame<false>::drop_row() {
	s.first--;
	kill_kids_outside_house();
}

template <bool autoRender>
void udh_meta_frame<autoRender>::place(udh_frame &sub_frame, uint row,
                                       uint col) {
	place(sub_frame, std::make_pair(row, col));
}

template <bool autoRender>
void udh_meta_frame<autoRender>::place(udh_frame &sub_frame,
                                       std::pair<uint, uint> pos) {
	children.push_back(std::make_pair(pos, &sub_frame));
}

template <>
udh_frame udh_meta_frame<false>::clip(uint from_row, uint from_col, uint rows,
                                      uint cols) const {
	return rendered.clip(from_row, from_col, rows, cols);
}

template <>
udh_frame udh_meta_frame<true>::clip(uint from_row, uint from_col, uint rows,
                                     uint cols) const {
	return render().clip(from_row, from_col, rows, cols);
}

template <bool autoRender>
void udh_meta_frame<autoRender>::clear() {
	children.clear();
}

template <>
void udh_meta_frame<false>::render() {
	rendered.clear();
	for (c : children) rendered.place(*c.second, c.first);
	return rendered;
}

template <>
udh_frame udh_meta_frame<true>::render() const {
	udh_frame rendered(size);
	for (c : children) rendered.place(*c.second, c.first);
	return rendered;
}

#endif
