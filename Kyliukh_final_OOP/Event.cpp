#include "Event.h"

std::ostream& operator<<(std::ostream& os, const Event& event)
{
	os << "Event: " << event.title() << "\n"
		<< "Date: " << event.date() << "\n";
	if (event.hasTime())
	{
		os << "Time: " << event.time() << "\n";
	}
	os << "Type: " << event.type() << "\n"
		<< "Priority: " << event.priority() << "\n"
		<< "Description: " << event.description() << "\n";
	return os;
}