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
        class Month
        {
        private:
            unsigned int _month;
            mutable Sequence<Event*> _events;

        public:
            Month(unsigned int m) : _month(m), _events(10)
            {
                for (int i = 0; i < _events.size(); ++i)
                    _events[i] = nullptr;
            }

            Month(const Month & other) = delete;
            Month& operator=(const Month & other) = delete;

            Month(Month && other) = delete;
            Month& operator=(Month && other) = delete;

            ~Month()
            {
                for (int i = 0; i < _events.size(); ++i)
                    delete _events[i];
            }

            const unsigned int month() const { return _month; }
            void addEvent(const Event & event)
            {
                _events.add(new Event(event));
            }

            const Event& operator[](size_t index) const;
        };

    private:
        unsigned int _year;
        mutable Month* _months[MONTH_AMOUNT];

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

        const Month& operator[](size_t month) const;
        const Month& operator[](size_t month);

    private:
        void initiateMonth (size_t month) const;
    };

private:
    mutable Year* _years[MAX_YEARS];
    size_t _currentYear;
    size_t _currentMonth;

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

    const Year::Month& currentMonth() const { return currentYear()[_currentMonth]; };
    const Year::Month& currentMonth() { return currentYear()[_currentMonth]; };

    void addEvent(const Event& event);
	void markDate(const Date& date);
	void nextMonth();
	void previousMonth();
    //void removeEvent(const Event& event);
    //void printYearEvents() const;
    void clear();

private:
    void initiateYear();
};

ostream& operator<<(ostream& out, const Calendar& c);
ostream& operator<<(ostream& out, const Calendar::Year& y);
ostream& operator<<(ostream& out, const Calendar::Year::Month& m);