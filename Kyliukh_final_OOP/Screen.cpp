#include "Screen.h"

Screen::Screen(const size_t h)
	: _h(h), _cursorX(0), _cursorY(0), _scrollY(0), _content()
{
    ifstream file("filler.txt", std::ios::binary);
    if (!file.is_open())
		throw std::runtime_error("Could not open file");

	char line[ROW_LENGTH + 1] = {0};
    size_t row = 0;
    while (file.read(line, ROW_LENGTH))
    {  
        strncpy_s(_content[row++], line, ROW_LENGTH);
    }

    file.close();
}

Screen::Screen(const Screen& other)
	: _h(other._h), _cursorX(other._cursorX), _cursorY(other._cursorY), _scrollY(other._scrollY)
{
	if (this == &other)
		return;
	for (size_t i = 0; i < ROW_COUNT; ++i)
		strncpy_s(_content[i], other._content[i], ROW_LENGTH);
}

Screen& Screen::operator=(const Screen& other)
{
	if (this == &other)
		return *this;
	_h = other._h;
	_cursorX = other._cursorX;
	_cursorY = other._cursorY;
	_scrollY = other._scrollY;
	for (size_t i = 0; i < ROW_COUNT; ++i)
		strncpy_s(_content[i], other._content[i], ROW_LENGTH);
	return *this;
}

Screen::Screen(Screen&& other) noexcept
	: _h(other._h), _cursorX(other._cursorX), _cursorY(other._cursorY), _scrollY(other._scrollY)
{
	if (this == &other)
		return;
	for (size_t i = 0; i < ROW_COUNT; ++i)
	{
		strncpy_s(_content[i], other._content[i], ROW_LENGTH);
	}
}

Screen& Screen::operator=(Screen&& other) noexcept
{
	if (this == &other)
		return *this;
	_h = other._h;
	_cursorX = other._cursorX;
	_cursorY = other._cursorY;
	_scrollY = other._scrollY;
	for (size_t i = 0; i < ROW_COUNT; ++i)
	{
		strncpy_s(_content[i], other._content[i], ROW_LENGTH);
	}
	return *this;
}

void Screen::print(ostream& out) const
{
	out << "Lines from " << _scrollY << " to " << _scrollY + _h << "\n";
	for (size_t i = _scrollY; i < _scrollY + _h; ++i)
	{
		for (size_t j = 0; j < ROW_LENGTH; ++j)
		{
			if (i == _cursorY && j == _cursorX)
				out << "\033[32m" << _content[i][j] << "\033[0m";
			else
				out << _content[i][j];
		}
	}
}

ostream& operator<<(ostream& out, const Screen& screen)
{
    screen.print(out);
	return out;
}
