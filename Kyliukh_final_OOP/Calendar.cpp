#include "Calendar.h"

const time_t currentTime = time(nullptr);
const int currentYear = localtime(&currentTime)->tm_year + 1900;

class Calendar::Year
{
	struct Month
	{
		Sequence<Event> events;
	};

	int _year;
	Month* _months[12];

public:
	Year(int year = currentYear) : _year(year), _months()
	{
		for (int i = 0; i < 12; ++i)
			_months[i] = nullptr;
	}
};