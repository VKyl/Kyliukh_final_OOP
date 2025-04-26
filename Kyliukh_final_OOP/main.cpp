#include <iostream>
#include "Date.h"
#include "Event.h"

// use date > 1970
int main()
{
	Date d(2, 1, 1970);
	Event e(d, Meeting, 1, "Project meeting", "Discuss project status");
	std::cout << e << std::endl;
	return 0;
}