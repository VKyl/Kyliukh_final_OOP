#pragma once
#include <iostream>
#include <fstream>
#include <stdexcept>

using std::ifstream, std::ostream;

const size_t ROW_LENGTH = 81;
const size_t ROW_COUNT = 24;

class Screen
{
private:
	mutable size_t _cursorX; 
	mutable size_t _cursorY;
	mutable size_t _scrollY;
	size_t _h;
	char _content[ROW_COUNT][ROW_LENGTH + 1];
public:
	Screen(const size_t h);
	Screen(const Screen&);
	Screen& operator=(const Screen&);
	Screen(Screen&&) noexcept;
	Screen& operator=(Screen&&) noexcept;

	~Screen() = default;

	void print(ostream& out) const;
	void setCursor(size_t x, size_t y) const
	{
		if (x > ROW_LENGTH || y > _h)
			throw std::out_of_range("Cursor position out of range");
		_cursorX = x;
		_cursorY = y;
	}
	void replace(char c)
	{
		_content[_cursorY][_cursorX] = c;
	}

	void left() const { setCursor(_cursorX, _cursorY); }
	void right() const { setCursor(_cursorX, _cursorY); }
	void up() const { setCursor(_cursorX, _cursorY); }
	void down() const { setCursor(_cursorX, _cursorY); }
	void scrollDown() const { if (_scrollY + _h < ROW_COUNT)++_scrollY; }
	void scrollUp() const { if (_scrollY > 0) --_scrollY; }
};


ostream& operator<<(ostream& out, const Screen& screen);
