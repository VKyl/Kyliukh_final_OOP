#include <iostream>
#include "Date.h"
#include "Event.h"
#include "Calendar.h"

// use date > 1970
int main()
{
	//Date d(2, 1, 2025);
	Event e({2, 1, 2025}, Meeting, 1, "Project meeting", "Discuss project status");
	Calendar c;

	c.addEvent(e);
	std::cout << c << std::endl;
	return 0;
}