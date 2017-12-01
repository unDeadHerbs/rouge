#include "udh_frame.hpp"

std::string &udh_frame::operator[](int rhs) {
	return frame[rhs];
}

void udh_frame::push_back(std::string row) {
	frame.push_back(row);
}

uint udh_frame::size() const {
	return frame.size();
}

void udh_frame::pop_back() {
	frame.pop_back();
}
