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
		Jan = 1, Feb, Mar, Apr, May, Jun,
		Jul, Aug, Sep, Oct, Nov, Dec
	};

	Date(unsigned int d = 0, unsigned int m = 0, unsigned int y = 0)
	{
		fillDate(d, Month(m), y);
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
	const bool leapYear() const { return _year % 4 == 0; }

private:
	void fillDate(unsigned int  d, unsigned int m, unsigned int y);
	void validateDate();
};

ostream& operator<<(ostream& os, const Date& date);