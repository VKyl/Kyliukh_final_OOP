#include "Date.h"

const char Date::monthNames[12][4] = {
	"Jan", "Feb", "Mar", "Apr", "May", "Jun",
	"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

const Date Date::defaultDate(1, January, 2000);

ostream& operator<<(ostream& os, const Date& date)
{
	os << date.day() << " " << date.monthName() << " " << date.year();
	return os;
}