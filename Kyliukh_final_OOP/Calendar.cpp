#include "Calendar.h"

const time_t currentTime = time(nullptr);
const size_t MONTH_AMOUNT = 12;
const unsigned int currentYear = localtime(&currentTime)->tm_year + 1900;

class Calendar::Year
{
	class Month
	{
	private:
		mutable Sequence<Event> _events;
	public:
		Month(): _events(10) {}
		~Month() = default;
		const Event& operator[](size_t index) const
		{
			if (index >= _events.size())
				throw std::out_of_range("Index out of range");
			return _events[index];
		}
	};

	unsigned int _year;
	mutable Month* _months[MONTH_AMOUNT];

public:
	Year(unsigned int year = currentYear) : _year(year), _months()
	{
		if (_year < 1970 || year > currentYear)
			throw std::invalid_argument("Year must be >= 1970");

		for (int i = 0; i < MONTH_AMOUNT; ++i)
			_months[i] = nullptr;
	}
	~Year()
	{
		for (int i = 0; i < MONTH_AMOUNT; ++i)
			delete _months[i];
	}

	const Month& operator[](size_t month) const
	{
		if (month < 1 || month > MONTH_AMOUNT)
			throw std::out_of_range("Month must be in range [1, 12]");
		if (_months[month - 1] == nullptr)
			_months[month - 1] = new Month();
		return *(_months[month - 1]);
	}
};



void Calendar::clear()
{
	for (size_t i = 0; i < MAX_YEARS; ++i)
		delete _years[i];
}

void Calendar::initiateYear()
{
	if (_years[_currentYear] == nullptr)
		_years[_currentYear] = new Year(_currentYear);
}