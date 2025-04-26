#pragma once
class Screen
{
private:
	const size_t  _w;
	const size_t _h;
	size_t _x, _y;
	char* _content;
public:
	Screen(const size_t w, const size_t h, char* pc=0)
		: _w(w), _h(h), _x(0), _y(0)
	{
		
	}


};

