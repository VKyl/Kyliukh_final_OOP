#include "Date.h"

const char Date::monthNames[12][4] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

const Date Date::defaultDate(1, Jan, 2000);

void Date::fillDate(unsigned int d, unsigned int m, unsigned int y)
{
	_day = d ? d : defaultDate._day;
	_month = m ? m : defaultDate._month;
	_year = y ? y : defaultDate._year;
	validateDate();
}

void Date::validateDate()
{
	unsigned int numberOfDays = 0;
	switch (_month)
	{
	case Apr: case Jun: case Sep: case Nov:
		numberOfDays = 30;
		break;
	case Jan: case Mar: case May: case Jul: case Aug: case Oct: case Dec:
		numberOfDays = 31;
		break;
	case Feb:
		numberOfDays = 28 + leapYear();
	}
	if (_day > numberOfDays)
		throw std::invalid_argument("Invalid day for the month");
}


ostream& operator<<(ostream& os, const Date& date)
{
	os << date.day() << ' ' << date.monthName() << ' ' << date.year();
	return os;
}