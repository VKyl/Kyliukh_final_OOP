#include "Calendar.h"

struct tm buf;
const char* SEP = "\n============================\n";

static bool (* const filters[FILTERS_AMOUNT])(const Event&, unsigned int) =
{
	[](const Event& e, unsigned int type) -> bool { return e.typeCode() == type; },
	[](const Event& e, unsigned int priority) -> bool { return e.priority() == priority; },
	[](const Event& e, unsigned int month) -> bool { return e.date().month() == month; }
};

int currentYear()
{
	auto now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	std::tm buf;
	std::tm* parts = nullptr;

	if (localtime_s(&buf, &now_c) == 0)
	{
		parts = &buf;
	}
	else
	{
		throw std::runtime_error("Failed to get local time");
	}

	return 1900 + parts->tm_year;
}

const Calendar::Month& Calendar::currentMonth() const
{
	return currentYear()[_currentMonth];
}

const Calendar::Month& Calendar::currentMonth()
{
	return currentYear()[_currentMonth];
}

const Event& Calendar::Month::operator[](size_t index) const
{
	return *_events[index];
}

Calendar::Year::Year(unsigned int year) : _year(year), _months()
{
	if (_year < 1970 || year > ::currentYear())
		throw std::invalid_argument("Year must be >= 1970");

	for (int i = 0; i < MONTH_AMOUNT; ++i)
		_months[i] = nullptr;
}
Calendar::Year::~Year()
{
	for (int i = 0; i < MONTH_AMOUNT; ++i)
		delete _months[i];
}

const Sequence<Event*> Calendar::filter(FilterType type, unsigned int queryParam)
{
	if (type >= FILTERS_AMOUNT)
		throw std::out_of_range("Filter type must be in range [0, 2]");
	return currentMonth().filter(filters[type], queryParam);
}

const Sequence<Event*> Calendar::Month::filter(bool(*filter)(const Event&, unsigned int), unsigned int queryParam) const
{
	Sequence<Event*> filteredEvents(10);
	for (int i = 0; i < _events.size(); ++i)
		if (filter(*_events[i], queryParam))
			filteredEvents.add(new Event(*_events[i]));
	
	return filteredEvents;
}

const Sequence<Event*> Calendar::filterByTimespan(const Date& d1, const Date& d2) const
{
	if (d1 > d2)
		throw std::invalid_argument("First date must be earlier than the second one");
	return currentMonth().filterByTimespan(d1, d2);
}

const Sequence<Event*> Calendar::Month::filterByTimespan(const Date& d1, const Date& d2) const
{
	Sequence<Event*> filteredEvents(10);
	for (int i = 0; i < _events.size(); ++i)
		if (_events[i]->date() >= d1 && _events[i]->date() <= d2)
			filteredEvents.add(new Event(*_events[i]));

	return filteredEvents;
}


const Calendar::Month& Calendar::Year::operator[](size_t month)  const
{
	if (month < 1 || month > MONTH_AMOUNT)
		throw std::out_of_range("Month must be in range [1, 12]");

	initiateMonth(month);
	return *(_months[month - 1]);
}

const Calendar::Month& Calendar::Year::operator[](size_t month)
{
	if (month < 1 || month > MONTH_AMOUNT)
		throw std::out_of_range("Month must be in range [1, 12]");
	
	initiateMonth(month);

	return *(_months[month - 1]);
}

void Calendar::Year::initiateMonth(size_t month) const
{
	if (_months[month - 1] == nullptr)
		_months[month - 1] = new Month(month, Date::numberOfDays(month, _year));
}

void Calendar::clear()
{
	for (size_t i = 0; i < MAX_YEARS; ++i)
	{
		delete _years[i];
		_years[i] = nullptr;
	}
}

void Calendar::initiateYear()
{
	if (_years[_currentYear] == nullptr)
		_years[_currentYear] = new Year(::currentYear() + _currentYear);
}

void Calendar::nextMonth()
{
	if (_currentMonth == MONTH_AMOUNT)
	{
		_currentMonth = 1;
		++_currentYear;
	}
	else
	{
		++_currentMonth;
	}
	if (_years[_currentYear] == nullptr)
		initiateYear();
}

void Calendar::previousMonth()
{
	if (_currentMonth != 1)
	{
		--_currentMonth;
		return;
	}

	if (_currentYear == 0)
		throw std::out_of_range("You can't travel back in time!");

	--_currentMonth;
	--_currentYear;
}

void Calendar::addEvent(const Event& event)
{
	const unsigned int eventYear = event.date().year();
	const unsigned int currentYear = ::currentYear();
	if (eventYear > currentYear + MAX_YEARS)
		throw std::out_of_range("You can't travel that far into the future!");
	if (eventYear < currentYear)
		throw std::out_of_range("You can't travel into the past!");
	
	_currentYear = event.date().year() - ::currentYear();
	initiateYear();
	_years[_currentYear]->addEvent(event);
}

ostream& operator<<(ostream& out, const Calendar& c)
{
	out << SEP 
		<< "Current year is: " << c.currentYear().year()
		<< "\nCurrent month is: " << c.currentMonth() 
		<< SEP;
	return out;
}

ostream& operator<<(ostream& out, const Calendar::Year& y)
{
	out << y.year();
	return out;
}

ostream& operator<<(ostream& out, const Calendar::Month& m)
{
	out << monthNames[m.month() - 1] << '\n';
	unsigned int dayOfTheWeek = Date::dayOfTheWeek(1, m.month(), m.year());

	out << "Su  Mo  Tu  We  Th  Fr  Sa\n";
	for (int i = 0; i < dayOfTheWeek; ++i)
		out << "    ";

	const int columns = 7; 
	for (int day = 1; day <= m.daysAmount(); ++day)
	{
		if (m.isDayMarked(day))
			out << setw(2) << "\033[31m" << day << "\033[0m  ";
		else
			out << setw(2) << day << "  ";
		
		if ((day + dayOfTheWeek) % columns == 0)
			out << '\n';
	}

	return out;
}