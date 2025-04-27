#pragma once
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <functional>
#include <iomanip>
#include <ctime>
#include "Event.h"
#include "Sequence.h"

using std::time_t, std::time, std::ostream, std::setw;

const size_t MAX_YEARS = 10;
const size_t SEMESTER_LENGTH = 12;
const size_t MONTH_AMOUNT = 12;
const size_t FILTERS_AMOUNT = 3;

static enum FilterType
{
	Type,
	Priority,
	Month
};

extern bool(* const filters[FILTERS_AMOUNT])(const Event&, unsigned int);

int currentYear();

class Calendar
{
public:
    class Year;
    class Month;

private:
    mutable Year* _years[MAX_YEARS];
    mutable size_t _currentYear;
    mutable size_t _currentMonth;

public:
    Calendar() : _years(), _currentYear(0), _currentMonth(1)
    {
        time_t currentTime = time(nullptr);
		initiateYear();
    }

	Calendar(const Calendar& other) = delete;
	Calendar& operator=(const Calendar& other) = delete;
	Calendar(Calendar&& other) = delete;
	Calendar& operator=(Calendar&& other) = delete;

    ~Calendar()
    {
        clear();
    }

	const Year& currentYear() const { return *_years[_currentYear]; };
    const Year& currentYear() { return *_years[_currentYear]; };

    const Calendar::Month& currentMonth() const;
    const Calendar::Month& currentMonth();

    const Sequence<Event*> filter(FilterType type, unsigned int queryParam);
    const Sequence<Event*> filterByTimespan(const Date& d1, const Date& d2) const;

    static const Date semesterEndDate(const Date& start) { return start + SEMESTER_LENGTH * 7; }

    void addEvent(const Event& event);
    void markDate(const Date& date) { addEvent({date, Important, 1, "", ""}); };
	void nextMonth();
	void previousMonth();
    void nextYear() const;
    void previousYear() const;
    void goToMonth(Date::Month m);
    void clear();

private:
    void initiateYear(unsigned int y = 0) const;
};

class Calendar::Month
{
private:
    unsigned int _month;
    const size_t _days_amount;
    bool* _days;
    mutable Sequence<Event*> _events;

public:
    Month(unsigned int m, const size_t n) :
        _month(m), _days_amount(n), _days(nullptr), _events(10)
    {
        _days = new bool[n] {};
        for (int i = 0; i < _events.size(); ++i)
            _events[i] = nullptr;
    }

    Month(const Month& other) = delete;
    Month& operator=(const Month& other) = delete;

    Month(Month&& other) = delete;
    Month& operator=(Month&& other) = delete;

    ~Month()
    {
        for (int i = 0; i < _events.size(); ++i)
        {
            delete _events[i];
			_events[i] = nullptr;
        }
    }

    const unsigned int month() const { return _month; }
    const unsigned int month() { return _month; }
    const size_t daysAmount() const { return _days_amount; }
    const size_t daysAmount() { return _days_amount; }
    const unsigned int year() const { return _month; }
    const unsigned int year() { return _month; }

    const Sequence<Event*> filter(bool(*filter)(const Event&, unsigned int), unsigned int queryParam) const;
    const Sequence<Event*> filterByTimespan(const Date& d1, const Date& d2) const;

    const bool isDayMarked(size_t day) const
    {
        if (day < 1 || day > _days_amount)
            throw std::out_of_range("Day must be in range [1, 31]");
        return _days[day - 1];
    }

    void addEvent(const Event& event)
    {
        _days[event.date().day() - 1] = true;
        _events.add(new Event(event));
    }

    const Event& operator[](size_t index) const;
};

class Calendar::Year
{
private:
    unsigned int _year;
    mutable Calendar::Month* _months[MONTH_AMOUNT];

public:
    Year(unsigned int year);

    Year(const Year& other) = delete;
    Year& operator=(const Year& other) = delete;
    Year(Year&& other) = delete;
    Year& operator=(Year&& other) = delete;

    ~Year();

    void addEvent(const Event& event)
    {
        initiateMonth(event.date().month());
        (_months[event.date().month() - 1])->addEvent(event);
    }

    const unsigned int year() const { return _year; };
    const unsigned int year() { return _year; };

    const Calendar::Month& operator[](size_t month) const;
    const Calendar::Month& operator[](size_t month);
    void initiateMonth(size_t month) const;
};

ostream& operator<<(ostream& out, const Calendar& c);
ostream& operator<<(ostream& out, const Calendar::Year& y);
ostream& operator<<(ostream& out, const Calendar::Month& m);