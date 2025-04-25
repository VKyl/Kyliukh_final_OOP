#include "Date.h"

const char Date::monthNames[12][4] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

const Date Date::defaultDate(1, Jan, 2000);

const unsigned int Date::numberOfDays(const unsigned int m) const
{
	switch (m)
	{
	case Apr: case Jun: case Sep: case Nov:
		return 30;
	case Jan: case Mar: case May: case Jul: case Aug: case Oct: case Dec:
		return 31;
	case Feb:
		return 28 + leapYear();
	default:
		throw std::invalid_argument("Invalid month");
	}
}

void Date::fillDate(unsigned int d, unsigned int m, unsigned int y)
{
	_day = d ? d : defaultDate._day;
	_month = m ? m : defaultDate._month;
	_year = y ? y : defaultDate._year;
	validateDate();
}

const unsigned int Date::monthToDaysFromBegin() const
{
	unsigned int days = 0;
	for (int i = 0; i < _month; ++i)
	{
		days += numberOfDays(i);
	}
	return days;
}

void Date::validateDate()
{
	unsigned int numberOfDays = this->numberOfDays(_month);
	
	if (_day == 0 || _day > numberOfDays || _year == 0)
		throw std::invalid_argument("Invalid day for the month");
}

void Date::normalizeDate()
{
	if (_day == 0 || _year == 0) throw std::invalid_argument("Invalid date");

	_year += _month / 12; 
	_month %= 12;

	unsigned int numberOfDays = this->numberOfDays(_month);
	while (_day > numberOfDays)
	{
		_day -= numberOfDays;
		_month++;
		numberOfDays = this->numberOfDays(_month);
	}
}

const unsigned int Date::toDays() const
{
	const unsigned int yearsToDays = (_year * 365) + (_year / 4) - (_year / 100) + (_year / 400);
	return yearsToDays + monthToDaysFromBegin() + _day;
}

const bool operator==(const Date& d1, const Date& d2)
{
	return d1.day() == d2.day()
		&& d1.month() == d2.month()
		&& d1.year() == d2.year();
}

const bool operator!=(const Date& d1, const Date& d2)
{
	return !(d1 == d2);
}

const bool operator<(const Date& d1, const Date& d2)
{
	if (d1.year() != d2.year())
		return d1.year() < d2.year();
	if (d1.month() != d2.month())
		return d1.month() < d2.month();
	return d1.day() < d2.day();
}

const bool operator>(const Date& d1, const Date& d2)
{
	return d2 < d1;
}	

const Date& operator++(Date& d)
{
	d.setDay(d.day() + 1);
	return d;
}

const Date& operator++(Date& d, int)
{
	Date temp = d;
	++d;
	return temp;
}

const Date& operator--(Date& d)
{
	if (d.day() != 1)
	{
		d.setDay(d.day() - 1);
		return d;
	}

	if (d.month() == 0)
	{
		d.setYear(d.year() - 1);
		d.setMonth(11);
	}
	else
	{
		d.setMonth(d.month() - 1);

	}
	
	d.setDay(d.daysInMonth() - 1);
	return d;
}

const Date& operator--(Date& d, int)
{
	Date temp = d;
	--d;
	return temp;
}

const Date& operator+(const Date& d1, const unsigned int d)
{
	Date res = d1;
	res.setDay(res.day() + d);
	return res;
}

const Date& operator-(const Date& d1, const unsigned int d)
{
	Date res(1, 0, 1);
	res.setDay(d1.toDays() - d);
	return res;
}

ostream& operator<<(ostream& os, const Date& date)
{
	os << date.day() << ' ' << date.monthName() << ' ' << date.year();
	return os;
}