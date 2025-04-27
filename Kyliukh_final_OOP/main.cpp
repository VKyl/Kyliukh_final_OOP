#include <iostream>
#include "Date.h"
#include "Event.h"
#include "Screen.h"
#include "Calendar.h"

// use date > 1970
int main()
{
	/*Date d1(12, 1, 2025);
	Date d2(15, 1, 2026);
	Time t(12, 23, 5);
	Event e(d1, t, Meeting, 1, "Project meeting", "Discuss project status");
	Calendar c;

	c.addEvent(e);
	c.markDate(d1);
	c.markDate(d2);
	std::cout << c << std::endl;
	c.nextMonth();
	std::cout << c << std::endl;
	c.previousMonth();
	std::cout << c << std::endl;

	const Sequence<Event*> eventsByType = c.filter(Type, Important);
	const Sequence<Event*> eventByTimeSpan = c.filterByTimespan(Date(1, 1, 2025), Date(13, 12, 2026));
	for (int i = 0; i < eventByTimeSpan.size(); ++i)
	{
		std::cout << *eventByTimeSpan[i] << std::endl;
	}*/
	Screen screen(12);
	screen.setCursor(1, 1);
	screen.replace('A');
	std::cout << screen << std::endl;
	return 0;
}