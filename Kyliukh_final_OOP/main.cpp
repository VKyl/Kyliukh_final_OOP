#include <iostream>
#include "Date.h"
#include "Event.h"
#include "Screen.h"
#include "Calendar.h"

// In lab I count dates valid only from 1900y (Unix Epoch)
void task1to5();

int main()
{
	task1to5();
	
	Screen screen(12);
	screen.setCursor(1, 1);
	screen.replace('A');
	std::cout << screen << std::endl;
	return 0;
}

void task1to5()
{
	std::cout << "Tasks from 1-5:\n";
	Date d1(12, 1, 2025);
	Date d2(15, 1, 2026);
	Time t(12, 23, 5);

	Event e(d1, t, Meeting, 1, "Project meeting", "Discuss project status");
	Event e2({ 13, 2, 2027 }, Other, 5, "Team building", "Fun activities together");

	std::cout << "Date d1(12, 1, 2025): " << d1 << '\n';
	std::cout << "Date d2(15, 1, 2026): " << d2 << '\n';
	std::cout << "Time t(12, 23, 5): " << t << "\n\n";

	std::cout << "e(d1,t, ...): \n" << e << '\n';
	std::cout << "e2({13, 2, 2027}, ...): \n" << e2 << '\n';

	Calendar c;

	c.addEvent(e);
	std::cout << "Added event e to calendar:\n";
	std::cout << c << std::endl;

	c.addEvent(e2);
	std::cout << "Added event e2 to calendar (not in currently visible timespan):\n";
	std::cout << c << std::endl;

	c.markDate(d1);
	std::cout << "Marked date d1 in calendar:\n";
	std::cout << c << std::endl;

	c.markDate(d2);
	std::cout << "Marked date d2 in calendar:\n";
	std::cout << c << std::endl;

	c.nextMonth();
	std::cout << c << std::endl;

	c.previousMonth();
	std::cout << c << std::endl;


	const Sequence<Event*> eventsByType = c.filter(Type, Important);

	std::cout << "Events of type Important:\n";
	for (int i = 0; i < eventsByType.size(); ++i)
	{
		std::cout << *eventsByType[i] << std::endl;
	}

	const Sequence<Event*> eventByTimeSpan = c.filterByTimespan(Date(1, 1, 2025), Date(13, 12, 2026));

	std::cout << "Events in timespan from 01.01.2025 to 13.12.2026:\n";
	for (int i = 0; i < eventByTimeSpan.size(); ++i)
	{
		std::cout << *eventByTimeSpan[i] << std::endl;
	}
}