#include "Screen.h"

Screen::Screen(const size_t h)
	: _h(h), _cursorX(0), _cursorY(0)
{
    ifstream file("lorem.txt", std::ios::binary);
    if (!file.is_open())
		throw std::runtime_error("Could not open file");

    char* line = new char[ROW_LENGTH];
    size_t row = 0;
    while (file.read(line, ROW_LENGTH))
    {  
        strncpy_s(_content[row], line, ROW_LENGTH);
        row++;
    }

    delete[] line;
    file.close();
}

void Screen::print(ostream& out) const
{
	for (size_t i = 0; i < _h; ++i)
	{
		for (size_t j = 0; j < ROW_LENGTH; ++i)
		{
			if (i == _cursorY && j == _cursorX)
				out << "\033[32m" << _content[i][j] << "\033[0m";
			else
				out << _content[i][j];
		}
		out << '\n';
	}
}

ostream& operator<<(ostream& out, const Screen& screen)
{
    screen.print(out);
	return out;
}
