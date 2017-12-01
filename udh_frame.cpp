#include "udh_frame.hpp"
#include "debug.hpp"

udh_frame::udh_frame(char ch) {
	frame.push_back("");
	frame[0].push_back(ch);
}

udh_frame::udh_frame(std::string s) {
	frame.push_back(s);
}

std::string &udh_frame::operator[](uint rhs) {
	return frame[rhs];
}

char &udh_frame::operator[](std::pair<uint, uint> rhs) {
	return frame[rhs.first][rhs.second];
}

void udh_frame::add_row(std::string row) {
	frame.push_back(row);
}

std::pair<uint, uint> udh_frame::size() const {
	return std::make_pair(frame.size(), frame.size() ? frame[0].size() : 0);
}

void udh_frame::resize(uint rows, uint cols) {
	debug(3, "resize frame");
	debug(4, "setting size to " + std::to_string(rows) + ":"
	             + std::to_string(cols));
	debugv(4, "size was " + std::to_string(size().first) + ":"
	              + std::to_string(size().second));
	if (frame.size() != rows) {
		for (uint i= frame.size(); i < rows; i++) frame.push_back("");
		for (uint i= frame.size(); i > rows; i--) frame.pop_back();
	}
	for (uint j= 0; j < frame.size(); j++) {
		if (frame[j].size() != cols) {
			debugv(5, "row size was "
			              + std::to_string(frame[j].size()));
			for (uint i= frame[j].size(); i < cols; i++)
				frame[j].push_back(' ');
			for (uint i= frame[j].size(); i > cols; i--)
				frame[j].pop_back();
			debugv(5, "row size is now "
			              + std::to_string(frame[j].size()));
		}
	}
	if (frame.size() != 0)
		debugv(4, "size is now " + std::to_string(frame.size()) + ":"
		              + std::to_string(frame[0].size()));
	else
		debugv(4, "size is now 0:0");
}

void udh_frame::drop_row() {
	frame.pop_back();
}

void udh_frame::place(udh_frame sub, int row, int col) {
	debug(2, "Placing sub-Frame");
	for (uint r= std::max(0, row);
	     r < size().first && r - row < sub.size().first; r++) {
		for (uint c= std::max(0, col);
		     c < frame[r].size() && c - col < sub[r - row].size();
		     c++) {
			debug(5, "update display location " + std::to_string(r)
			             + "," + std::to_string(c) + " to "
			             + sub[r - row][c - col]);
			frame[r][c]= sub[r - row][c - col];
		}
	}
}
void udh_frame::place(udh_frame sub, std::pair<int, int> pos) {
	place(sub, pos.first, pos.second);
}
