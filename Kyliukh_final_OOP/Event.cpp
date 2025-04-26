#include "Event.h"

ostream& operator<<(ostream& out, const Event& event)
{
	out << "Event: " << event.title() << "\n"
		<< "Date: " << event.date() << "\n";
	if (event.hasTime())
	{
		out << "Time: " << event.time() << "\n";
	}
	out << "Type: " << event.type() << "\n"
		<< "Priority: " << event.priority() << "\n"
		<< "Description: " << event.description() << "\n";
	return out;
}