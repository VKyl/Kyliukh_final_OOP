#pragma once
#include <iostream>
#include "Date.h"
#include "Time.h"

enum EventType
{
    Meeting,
    Reminder,
    Task,
    Celebration,
    Other
};

const std::string EventTypeNames[] = {
    "Meeting",
    "Reminder",
    "Task",
    "Celebration",
    "Other"
};

class Event
{
private:
    Date _date;               
    Time _time;               
    unsigned int _type;       
    int _priority;            
    std::string _title;       
    std::string _description;
    bool _hasTime;            

public:
    Event(
        const Date& date,
        const EventType type,
        int priority,
        const std::string& title,
        const std::string& description
    ) : _date(date), _time(0,0,0), _type(type), 
        _priority(priority), _title(title), 
        _description(description), _hasTime(false)
    {

    }

    Event(
        const Date& date, 
        const Time& time, 
        const EventType type, 
        int priority, 
        const std::string& title, 
        const std::string& description
    ): _date(date), _time(time), _type(type),
        _priority(priority), _title(title), 
        _description(description), _hasTime(true)
    {
    }

    const Date& date() const { return _date; }
    const Time& time() const { return _time; }
    const std::string& type() const { return eventTypeName(_type); }
    int priority() const { return _priority; }
    const std::string& title() const { return _title; }
    const std::string& description() const { return _description; }
    bool hasTime() const { return _hasTime; }

	static const std::string& eventTypeName(EventType type) { return EventTypeNames[type]; }
private:
    static const std::string& eventTypeName(unsigned int type) { return EventTypeNames[type]; }

};

std::ostream& operator<<(std::ostream& os, const Event& event);
