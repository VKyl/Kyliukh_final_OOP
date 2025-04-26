#include "Calendar.h"

struct tm buf;
const char* SEP = "\n============================\n";

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


const Event& Calendar::Year::Month::operator[](size_t index) const
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

const Calendar::Year::Month& Calendar::Year::operator[](size_t month) const
{
	if (month < 1 || month > MONTH_AMOUNT)
		throw std::out_of_range("Month must be in range [1, 12]");

	if (_months[month - 1] == nullptr)
		_months[month - 1] = new Month(month);

	return *(_months[month - 1]);
}



void Calendar::clear()
{
	for (size_t i = 0; i < MAX_YEARS; ++i)
		delete _years[i];
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
		--_currentYear;
		return;
	}

	if (_currentYear == 0)
		throw std::out_of_range("You can't travel back in time!");

	--_currentMonth;
	--_currentYear;
}

ostream& operator<<(ostream& out, const Calendar& c)
{
	out << SEP 
		<< "Calendar:"
		<< "\nCurrent year is: " << c.currentYear().year()
		<< "\nCurrent month is: " << c.currentMonth() 
		<< SEP;
	return out;
}

ostream& operator<<(ostream& out, const Calendar::Year& y)
{
	out << y.year();
	return out;
}

ostream& operator<<(ostream& out, const Calendar::Year::Month& m)
{
	out << monthNames[m.month() - 1];
	return out;
}