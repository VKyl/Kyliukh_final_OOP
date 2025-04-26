#include <iostream>
#include "Date.h"
#include "Event.h"
#include "Calendar.h"

// use date > 1970
int main()
{
	Date d1(12, 1, 2025);
	Date d2(15, 1, 2025);

	//Event e(d, Meeting, 1, "Project meeting", "Discuss project status");
	Calendar c;

	//c.addEvent(e);
	c.markDate(d1);
	c.markDate(d2);
	std::cout << c << std::endl;
	c.nextMonth();
	std::cout << c << std::endl;
	c.previousMonth();
	std::cout << c << std::endl;

	const Sequence<Event*> eventsByType = c.filter(Type, Important);
	const Sequence<Event*> eventByTimeSpan = c.filterByTimespan(Date(1, 1, 2025), Date(13, 1, 2025));
	for (int i = 0; i < eventByTimeSpan.size(); ++i)
	{
		std::cout << *eventByTimeSpan[i] << std::endl;
	}

	return 0;
}