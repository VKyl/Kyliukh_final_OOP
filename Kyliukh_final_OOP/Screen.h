#pragma once
#include <iostream>
#include <fstream>
#include <stdexcept>

using std::ifstream, std::ostream;

const size_t ROW_LENGTH = 80;
const size_t ROW_COUNT = 24;

class Screen
{
private:
	mutable size_t _cursorX; 
	mutable size_t _cursorY;
	const size_t _h;
	char _content[ROW_LENGTH][ROW_COUNT];
public:
	Screen(const size_t h);

	~Screen() = default;

	void print(ostream& out) const;
};


ostream& operator<<(ostream& out, const Screen& screen);
