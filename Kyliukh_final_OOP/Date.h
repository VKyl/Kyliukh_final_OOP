#pragma once
#include <cmath>
#include <iostream>

using std::ostream;

const static char monthNames[12][4] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

class Date
{
private:
	unsigned int _year, _month, _day;
	const static int monthDaysFromBegin[12];
	static const Date defaultDate;

public:
	enum Month
	{
		Jan=1, Feb, Mar, Apr, May, Jun,
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
	Date& operator=(const Date& other) = default;

	Date(Date&& other) = default;
	Date& operator=(Date&& other) = default;

	~Date() = default;

	const unsigned int day() const { return _day; }
	const unsigned int month() const { return _month; }
	const unsigned int year() const { return _year; }

	void setDay(unsigned int d) { _day = d; normalizeDate(); }
	void setMonth(unsigned int m) { _month = m; normalizeDate(); }
	void setYear(unsigned int y) { _year = y; normalizeDate(); }

	const char* monthName() const { return monthNames[_month-1]; }
	const bool leapYear() const { return _year % 4 == 0; }
	const unsigned int daysInMonth() const { return numberOfDays(_month); }
	const unsigned int toDays() const;

	const Date& operator+= (const unsigned int days);
	const Date& operator-= (const unsigned int days);
private:
	const unsigned int numberOfDays(const unsigned int month) const;

	void fillDate(unsigned int  d, unsigned int m, unsigned int y);
	void validateDate();
	void normalizeDate();
};

const bool operator==(const Date& d1, const Date& d2);
const bool operator!=(const Date& d1, const Date& d2);
const bool operator<(const Date& d1, const Date& d2);
const bool operator>(const Date& d1, const Date& d2);

const Date& operator++(Date& d);
const Date& operator--(Date& d);
const Date operator++(Date& d, int);
const Date operator--(Date& d, int);
		  
const Date operator+(const Date& d1, const unsigned int days);
const Date operator-(const Date& d1, const unsigned int days);

ostream& operator<<(ostream& os, const Date& date);