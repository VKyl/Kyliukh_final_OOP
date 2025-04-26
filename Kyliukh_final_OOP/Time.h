#pragma once
#include <iostream>
#include <stdexcept>

using std::ostream;

class Time
{
private:
	unsigned int _hours, _minutes, _seconds;

public:
	Time(unsigned int _s, unsigned int _m, unsigned _h)
		: _seconds(_s), _minutes(_m), _hours(_h)
	{
		normalizeTime();
	}

	Time(const Time& other) = default;
	Time(Time&& other) = default;
	~Time() = default;

	Time& operator=(const Time& other) = default;
	Time& operator=(Time&& other) = default;

	const unsigned int hours() const { return _hours; }
	const unsigned int minutes() const { return _minutes; }
	const unsigned int seconds() const { return _seconds; }

	void setHours(unsigned int h);
	void setMinutes(unsigned int m);
	void setSeconds(unsigned int s);

	unsigned int toSeconds() const;
	Time& fromSeconds(unsigned int s);

	const Time& operator+=(const unsigned int seconds);
	const Time& operator-=(const unsigned int seconds);

private:
	void normalizeTime();
};

bool operator==(const Time& t1, const Time& t2);
bool operator!=(const Time& t1, const Time& t2);
bool operator<(const Time& t1, const Time& t2);
bool operator>(const Time& t1, const Time& t2);

const Time& operator++(Time& t);
const Time& operator--(Time& t);
const Time operator++(Time& t, int);
const Time operator--(Time& t, int);

const Time operator+(const Time& t1, const unsigned int s);
const Time operator-(const Time& t1, const unsigned int s);

ostream& operator<<(ostream& out, const Time& t);

