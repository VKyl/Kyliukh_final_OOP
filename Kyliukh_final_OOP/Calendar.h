#pragma once
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <ctime>
#include "Event.h"
#include "Sequence.h"

using std::time_t, std::time, std::ostream;

const size_t MAX_YEARS = 10;
const size_t SEMESTER_LENGTH = 12;
const size_t MONTH_AMOUNT = 12;

int currentYear();

class Calendar
{
public:

    class Year
    {
    public:
        class Month;

    private:
        unsigned int _year;
        mutable Month* _months[MONTH_AMOUNT];

    public:
        Year(unsigned int year);
        ~Year();
		const unsigned int year() const { return _year; };
        const Month& operator[](size_t month) const;
    };

private:
    Year* _years[MAX_YEARS];
    size_t _currentYear;
    size_t _currentMonth;

public:
    Calendar() : _years(), _currentYear(0), _currentMonth(1)
    {
        time_t currentTime = time(nullptr);
		initiateYear();
    }

    ~Calendar()
    {
        clear();
    }

	const Year& currentYear() const { return *_years[_currentYear]; };
    const Year::Month& currentMonth() const { return currentYear()[_currentMonth]; };
    //void addEvent(const Event& event);
	void nextMonth();
	void previousMonth();
    //void removeEvent(const Event& event);
    //void printYearEvents() const;
    void clear();

private:
    void initiateYear();
};

class Calendar::Year::Month
{
private:
	unsigned int _month;
    mutable Sequence<Event*> _events;

public:
    Month(unsigned int m): _month(m), _events(10) 
    {
		for (int i = 0; i < _events.size(); ++i)
			_events[i] = nullptr;
    }

    ~Month()
    {
		for (int i = 0; i < _events.size(); ++i)
			delete _events[i];
    }

	const unsigned int month() const { return _month; }
    const Event& operator[](size_t index) const;
};

ostream& operator<<(ostream& out, const Calendar& c);
ostream& operator<<(ostream& out, const Calendar::Year& y);
ostream& operator<<(ostream& out, const Calendar::Year::Month& m);