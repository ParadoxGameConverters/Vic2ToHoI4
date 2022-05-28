#include "OutModifier.h"



std::ostream& HoI4::operator<<(std::ostream& output, const HoI4::Modifier& modifier)
{
	output << modifier.getName() << " = {\n";
	if (!modifier.getIcon().empty())
	{
		output << "\ticon = " << modifier.getIcon() << "\n";
	}
	if (!modifier.getEnable().empty())
	{
		output << "\tenable " << modifier.getEnable() << "\n";
	}
	if (!modifier.getRemoveTrigger().empty())
	{
		output << "\tremove_trigger " << modifier.getRemoveTrigger() << "\n";
	}
	output << "\n";
	for (auto [variable, value]: modifier.getEffects())
	{
		output << "\t" << variable << " = " << value << "\n";
	}
	output << "}\n";

	return output;
}