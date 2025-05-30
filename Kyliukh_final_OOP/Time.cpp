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

Time& Time::fromSeconds(unsigned int s)
{
	_seconds = s % 60;
	_minutes = (s / 60) % 60;
	_hours = (s / 3600) % 24;
	return *this;
}

const Time& Time::operator+=(const unsigned int seconds)
{
	*this = *this + seconds;
	return *this;
}

const Time& Time::operator-=(const unsigned int seconds)
{
	*this = *this - seconds;
	return *this;
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

const Time& operator++(Time& t)
{
	t.setSeconds(t.seconds() + 1);
	return t;
}

const Time& operator--(Time& t)
{
	const unsigned int newTime = t.toSeconds() - 1;
	return t.fromSeconds(newTime);
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

const Time operator+(const Time& t1, const unsigned int s)
{
	return Time(
		t1.seconds() + s, 
		t1.minutes(), 
		t1.hours()
	);
}

const Time operator-(const Time& t1, const unsigned int s)
{
	const unsigned int seconds = t1.toSeconds();
	if ( seconds < s) 
		throw std::invalid_argument("1st argument with Time operator- can't be less than 2nd");

	Time result = Time(0, 0, 0);
	const int resultSeconds = seconds - s;
	return result.fromSeconds(resultSeconds);
}

ostream& operator<<(ostream& out, const Time& t)
{
	out << t.hours() << "h:" << t.minutes() << "m:" << t.seconds() << 's';
	return out;
}

