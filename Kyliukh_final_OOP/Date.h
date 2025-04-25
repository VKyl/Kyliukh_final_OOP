#pragma once
#include <iostream>

using std::ostream;

class Date
{
private:
	unsigned int _day, _month, _year;
	const static char monthNames[12][4];
	static const Date defaultDate;

public:
	enum Month
	{
		January = 1, February, March, April, May, June,
		July, August, September, October, November, December
	};

	Date(unsigned int d = 0, unsigned int m = 0, unsigned int y = 0)
	{
		fillDate(d, m, y);
	}

	Date(unsigned int d, Month m, unsigned int y)
	{
		fillDate(d, m, y);
	}

	Date(const Date& other) = default;

	~Date() = default;

	const unsigned int day() const { return _day; }
	const unsigned int month() const { return _month; }
	const unsigned int year() const { return _year; }

	const char* monthName() const { return monthNames[_month - 1]; }

private:
	void fillDate(unsigned int  d, unsigned int m, unsigned int y)
	{
		_day = d ? d : defaultDate._day;
		_month = m ? m : defaultDate._month;
		_year = y ? y : defaultDate._year;
	}
};

ostream& operator<<(ostream& os, const Date& date);