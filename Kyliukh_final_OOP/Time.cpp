#include "Time.h"

void Time::setHours(unsigned int h)
{
	_hours = h;
}

void Time::setMinutes(unsigned int m)
{
	_minutes = m;
	normalizeTime();
}

void Time::setSeconds(unsigned int s)
{
	_seconds = s;
	normalizeTime();
}

void Time::normalizeTime()
{
	_hours += (_minutes + (_seconds / 60)) / 60;
	_minutes = (_minutes + (_seconds / 60))%60;
	_seconds %= 60;
}

unsigned int Time::toSeconds() const
{
	return _seconds + _minutes * 60 + _hours * 3600;
}

unsigned int Time::fromSeconds(unsigned int s)
{
	_seconds = s % 60;
	_minutes = (s / 60) % 60;
	_hours = (s / 3600) % 24;
	return s;
}

bool operator==(const Time& t1, const Time& t2)
{
	return (
		t1.hours() == t2.hours() 
		&& t1.minutes() == t2.minutes() 
		&& t1.seconds() == t2.seconds()
		);
}

bool operator!=(const Time& t1, const Time& t2)
{
	return !(t1 == t2);
}

bool operator<(const Time& t1, const Time& t2)
{
	if (t1.hours() != t2.hours()) return t1.hours() < t2.hours();
	if (t1.minutes() != t2.minutes()) return t1.minutes() < t2.minutes();
	return t1.seconds() < t2.seconds();
}

bool operator>(const Time& t1, const Time& t2)
{
	return t2 < t1;
}

const Time operator++(Time& t)
{
	t.setSeconds(t.seconds() + 1);
	return t;
}

const Time operator--(Time& t)
{
	const unsigned int newTime = t.toSeconds() - 1;
	t.fromSeconds(newTime);
	return t;
}

const Time operator++(Time& t, int)
{
	Time temp = t;
	t.setSeconds(t.seconds() + 1);
	return temp;
}

const Time operator--(Time& t, int)
{
	Time temp = t;
	--t;
	return temp;
}

const Time operator+(const Time& t1, const Time& t2)
{
	return Time(
		t1.seconds() + t2.seconds(), 
		t1.minutes() + t2.minutes(), 
		t1.hours() + t2.hours()
	);
}

const Time operator-(const Time& t1, const Time& t2)
{
	if (t1 < t2) 
		throw std::invalid_argument("1st argument with Time operator- can't be less than 2nd");

	Time result = Time(0, 0, 0);
	const int resultSeconds = t1.toSeconds() - t2.toSeconds();
	result.fromSeconds(resultSeconds);
	return result;
}

ostream& operator<<(ostream& os, const Time& t)
{
	os << t.hours() << "h:" << t.minutes() << "m:" << t.seconds() << 's';
	return os;
}

