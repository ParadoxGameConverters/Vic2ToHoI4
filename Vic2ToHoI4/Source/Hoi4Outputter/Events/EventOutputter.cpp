#include "EventOutputter.h"



std::ofstream& HoI4::operator << (std::ofstream& out, const Event& theEvent)
{
	out << theEvent.type << " = {\n";
	out << "	id = " << theEvent.id << "\n";
	out << "	title = " << theEvent.title << "\n";
	for (auto description: theEvent.descriptions)
	{
		out << "\t" << description << "\n";
	}
	out << "	picture = " << theEvent.picture << "\n";
	if (theEvent.majorEvent)
	{
		out << "	\n";
		out << "	major = yes\n";
	}
	out << "\n";
	if (theEvent.triggeredOnly)
	{
		out << "	is_triggered_only = yes\n";
	}
	if (theEvent.hidden)
	{
		out << "	hidden = yes\n";
	}

	if (!theEvent.trigger.empty())
	{
		out << "\n";
		out << "	trigger " << theEvent.trigger << "\n";
	}

	if (!theEvent.meanTimeToHappen.empty())
	{
		out << "\n";
		out << "	mean_time_to_happen " << theEvent.meanTimeToHappen << "\n";
	}

	if (!theEvent.immediate.empty())
	{
		out << "\n";
		out << "	immediate " << theEvent.immediate << "\n";
	}

	for (auto option: theEvent.options)
	{
		out << "\n";
		out << "	option " << option << "\n";
	}

	out << "}\n";

	return out;
}