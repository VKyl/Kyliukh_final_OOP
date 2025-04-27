#include <iostream>
#include "Date.h"
#include "Event.h"
#include "Screen.h"
#include "Calendar.h"

// In lab I count dates valid only from 1900y (Unix Epoch)
void task1to5();
void task6to8();

int main()
{
	task1to5();
	task6to8();
	std::cout << "Unfortunately, I don't have time"
		<< "to implement the rest of the tasks, due to other factors :(.\n"
		<< "Waiting for your review!" << std::endl;
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
	std::cout << "Added event e2 to calendar:\n";
	std::cout << c << std::endl;

	c.markDate(d1);
	std::cout << "Marked date d1 in calendar:\n";
	std::cout << c << std::endl;

	c.markDate(d2);
	std::cout << "Marked date d2 in calendar:\n";
	std::cout << c << std::endl;

	c.nextMonth();
	std::cout << "Moved to next month:\n";
	std::cout << c << std::endl;

	std::cout << "Moved to previous month:\n";
	c.previousMonth();
	std::cout << c << std::endl;


	const Sequence<Event*> eventsByType = c.filter(Type, Important);

	std::cout << "Events of type Important:\n";
	for (int i = 0; i < eventsByType.size(); ++i)
	{
		std::cout << *eventsByType[i] << std::endl;
	}

	std::cout << "Marked my BDay:\n";
	c.addEvent({ Date(9, Date::May, 2025), Important, 1, "My BD", "" });
	std::cout << c << std::endl;

	std::cout << "Marked Valentin's BDay\n";
	c.addEvent({ { 25, Date::Apr, 2025 }, Important, 1, "Valentine's Bday", "" });
	std::cout << c << std::endl;

	std::cout << "Marked Bjorn Stroustrup's BDay\n";
	c.addEvent({{ 30, Date::Dec, 2025 }, Important, 1, "Bjorn Stroustrup's Bday", ""});
	std::cout << c << std::endl;

	std::cout << "Marked Linus Torvalds' BDay\n";
	c.addEvent({{ 28, Date::Dec, 2025 }, Important, 1, "Linus Torvalds BDay", ""});
	std::cout << c << std::endl;

	const Sequence<Event*> eventByTimeSpan = c.filterByTimespan(Date(1, 1, 2025), Date(13, 12, 2026));

	std::cout << "Events in timespan from 01.01.2025 to 1.01.2026:\n";
	for (int i = 0; i < eventByTimeSpan.size(); ++i)
	{
		std::cout << *eventByTimeSpan[i] << std::endl;
	}
}

void task6to8()
{
	Screen screen(12);
	std::cout << "Initial screen screen(12) 12 - number of rows:\n";
	std::cout << screen << std::endl;

	screen.setCursor(1, 1);
	screen.replace('A');
	std::cout << "Moved cursor to 1,1 and replaced char to A:\n";
	std::cout << screen << std::endl;

	Screen screen2(screen);
	std::cout << "Screen2 (screen's copy):\n";
	std::cout << screen2 << std::endl;

	screen.setCursor(5, 3);
	screen.replace('S');
	std::cout << "Moved cursor to 5,3 and replaced char to S:\n";
	std::cout << screen << std::endl;

	Screen screen3(std::move(screen));
	std::cout << "Screen3 (screen's move):\n";
	std::cout << screen3 << std::endl;
}