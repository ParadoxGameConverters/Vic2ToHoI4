#include "OutEvent.h"
#include "OutEventOption.h"



std::ostream& HoI4::operator<<(std::ostream& out, const Event& theEvent)
{
	out << theEvent.type << " = {\n";
	out << "\tid = " << theEvent.id << "\n";
	if (theEvent.title)
	{
		out << "\ttitle = " << *theEvent.title << "\n";
	}
	for (const auto& description: theEvent.descriptions)
	{
		out << "\tdesc " << description << "\n";
	}
	if (theEvent.picture)
	{
		out << "\tpicture = " << *theEvent.picture << "\n";
	}
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
		if (*theEvent.hidden)
		{
			out << "\thidden = yes\n";
		}
		else
		{
			out << "\thidden = no\n";
		}
	}

	if (!theEvent.trigger.empty())
	{
		out << "\n";
		out << "\ttrigger " << theEvent.trigger << "\n";
	}

	if (theEvent.fireOnlyOnce)
	{
		out << "\n";
		if (*theEvent.fireOnlyOnce)
		{
			out << "\tfire_only_once = yes\n";
		}
		else
		{
			out << "\tfire_only_once = no\n";
		}
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