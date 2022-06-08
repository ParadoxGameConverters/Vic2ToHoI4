#include "src/OutHoi4/Events/OutEventOption.h"



std::ostream& HoI4::operator<<(std::ostream& out, const EventOption& theOption)
{
	out << "\toption = {\n";
	if (!theOption.name.empty())
	{
		out << "\t\tname = " << theOption.name << "\n";
	}
	if (!theOption.trigger.empty())
	{
		out << "\t\ttrigger = {\n";
		out << "\t\t\t" << theOption.trigger << "\n";
		out << "\t\t}\n";
	}
	if (!theOption.aiChance.empty())
	{
		out << "\t\tai_chance " << theOption.aiChance << "\n";
	}
	for (const auto& scriptBlock: theOption.scriptBlocks)
	{
		out << "\t\t" << scriptBlock << "\n";
	}
	if (!theOption.hiddenEffect.empty())
	{
		out << "\t\thidden_effect " << theOption.hiddenEffect << "\n";
	}
	out << "\t}";

	return out;
}