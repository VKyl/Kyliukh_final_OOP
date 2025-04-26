#include <iostream>
#include "Date.h"
#include "Event.h"
#include "Calendar.h"

// use date > 1970
int main()
{
	Date d(12, 1, 2025);
	//Event e(d, Meeting, 1, "Project meeting", "Discuss project status");
	Calendar c;

	//c.addEvent(e);
	c.markDate(d);
	std::cout << c << std::endl;
	c.nextMonth();
	std::cout << c << std::endl;
	c.previousMonth();
	std::cout << c << std::endl;
	return 0;
}