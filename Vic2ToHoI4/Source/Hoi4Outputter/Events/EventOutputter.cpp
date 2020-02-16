#include "EventOutputter.h"
#include "EventOptionOutputter.h"



std::ostream& HoI4::operator<<(std::ostream& out, const Event& theEvent)
{
	out << theEvent.type << " = {\n";
	out << "\tid = " << theEvent.id << "\n";
	out << "\ttitle = " << theEvent.title << "\n";
	for (const auto& description: theEvent.descriptions)
	{
		out << "\tdesc " << description << "\n";
	}
	out << "\tpicture = " << theEvent.picture << "\n";
	if (theEvent.majorEvent)
	{
		out << "\t\n";
		out << "\tmajor = yes\n";
	}
	out << "\n";
	if (theEvent.triggeredOnly)
	{
		out << "\tis_triggered_only = yes\n";
	}
	if (theEvent.hidden)
	{
		out << "\thidden = yes\n";
	}

	if (!theEvent.trigger.empty())
	{
		out << "\n";
		out << "\ttrigger " << theEvent.trigger << "\n";
	}

	if (theEvent.fireOnlyOnce)
	{
		out << "\n";
		out << "\tfire_only_once = yes\n";
	}

	if (!theEvent.meanTimeToHappen.empty())
	{
		out << "\n";
		out << "\tmean_time_to_happen " << theEvent.meanTimeToHappen << "\n";
	}

	if (!theEvent.immediate.empty())
	{
		out << "\n";
		out << "\timmediate " << theEvent.immediate << "\n";
	}

	for (const auto& option: theEvent.options)
	{
		out << "\n";
		out << option << "\n";
	}

	out << "}\n";

	return out;
}