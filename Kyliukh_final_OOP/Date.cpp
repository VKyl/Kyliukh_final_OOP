#include "Date.h"

const unsigned int UNIX_EPOCH = 1970;
const unsigned int UNIX_EPOCH_DAYS = 719527;

const int Date::monthDaysFromBegin[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

const Date Date::defaultDate(1, Jan, UNIX_EPOCH);

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

void Date::validateDate()
{
    if (_month < 1 || _month > 12)
        throw std::invalid_argument("Invalid month");

    unsigned int numberOfDays = this->numberOfDays(_month);

    if (_day == 0 || _day > numberOfDays || _year < 1970)
        throw std::invalid_argument("Invalid day for the month");
}

void Date::normalizeDate()
{
    if (_day == 0 || _year < 1970) throw std::invalid_argument("Invalid date");

    _year += (_month - 1) / 12;
    _month = (_month - 1) % 12 + 1;

    while (_day > (365 + leapYear()))
    {
        _day -= 365 + leapYear();
        _year++;
    }

    while (_day > numberOfDays(_month))
    {
        _day -= numberOfDays(_month++);
        _year += (_month - 1) / 12;
        _month = (_month - 1) % 12 + 1;
    }
}

const unsigned int Date::toDays() const
{
    const unsigned int yearDaysFromBegin = (_year * 365) + (_year / 4) - (_year / 100) + (_year / 400);
    return yearDaysFromBegin +
        Date::monthDaysFromBegin[_month - 1] +
        leapYear() +
        (_day - 1) -
        UNIX_EPOCH_DAYS;
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

const Date operator++(Date& d, int)
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

    if (d.month() == 1)
    {
        d.setYear(d.year() - 1);
        d.setMonth(12);
    }
    else
    {
        d.setMonth(d.month() - 1);
    }

    d.setDay(d.daysInMonth());
    return d;
}

const Date& Date::operator+=(const unsigned int days)
{
    *this = *this + days;
	return *this;
}

const Date& Date::operator-=(const unsigned int days)
{
    *this = *this - days;
    return *this;
}

const Date operator--(Date& d, int)
{
    Date temp = d;
    --d;
    return temp;
}

const Date operator+(const Date& d1, const unsigned int d)
{
    Date res = d1;
    res.setDay(res.day() + d);
    return res;
}

const Date operator-(const Date& d1, const unsigned int d)
{
    Date res;
    res.setDay(1 + d1.toDays() - d);
    return res;
}

ostream& operator<<(ostream& out, const Date& date)
{
    out << date.day() << ' ' << date.monthName() << ' ' << date.year();
    return out;
}
