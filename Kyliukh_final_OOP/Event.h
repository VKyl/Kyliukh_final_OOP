#pragma once
#include <iostream>
#include "Date.h"
#include "Time.h"
using std::ostream, std::string;

enum EventType
{
    Meeting,
    Reminder,
    Task,
    Celebration,
    Important,
    Other
};

const string EventTypeNames[] = {
    "Meeting",
    "Reminder",
    "Task",
    "Celebration",
	"Important date",
    "Other"
};

class Event
{
private:
    Date _date;               
    Time _time;               
    unsigned int _type;       
    int _priority;            
    string _title;       
    string _description;
    bool _hasTime;            

public:
    Event(
        const Date& date,
        const EventType type,
        int priority,
        const string& title,
        const string& description
    ) : _date(date), _time(0,0,0), _type(type), 
        _priority(priority), _title(title), 
        _description(description), _hasTime(false)
    {}

    Event(
        const Date& date, 
        const Time& time, 
        const EventType type, 
        int priority, 
        const string& title, 
        const string& description
    ): _date(date), _time(time), _type(type),
        _priority(priority), _title(title), 
        _description(description), _hasTime(true)
    {
        if (_time.hours() > 24)
            throw std::invalid_argument("Day has only 24 hours (unfortunately)");
    }

	Event(const Event& other) = default;
	Event(Event&& other) = default;
	Event& operator=(const Event& other) = default;
	Event& operator=(Event&& other) = default;

    const Date& date() const { return _date; }
    const Time& time() const { return _time; }

	const unsigned int typeCode() const { return _type; }
    const string& type() const { return eventTypeName(EventType(_type)); }

    int priority() const { return _priority; }
    const string& title() const { return _title; }
    const string& description() const { return _description; }
    bool hasTime() const { return _hasTime; }

	static const string& eventTypeName(EventType type) { return EventTypeNames[type]; }
};

ostream& operator<<(ostream& out, const Event& event);
