#pragma once
#include <ctime>
#include <iostream>
#include <stdexcept>
#include "Event.h"
#include "Sequence.h"

using std::time_t, std::time, std::localtime;

const size_t MAX_YEARS = 10;

class Calendar
{
private:
	class Year;
	Year* _years[MAX_YEARS];
	size_t _currentYear;
	size_t _currentMonth;
	
public:
	Calendar() : _years(), _currentYear(1970), _currentMonth(1)
	{
		time_t currentTime = time(nullptr);
		_currentYear = 0;
		_currentMonth = 1;
	}

	~Calendar()
	{
		clear();
	}

	void addEvent(const Event& event);
	void removeEvent(const Event& event);
	void printEvents() const;
	void clear();
private:
	void initiateYear();
};

