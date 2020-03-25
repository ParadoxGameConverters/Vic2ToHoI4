#include "OutGameRule.h"



std::ostream& HoI4::operator<<(std::ostream& output, const GameRule& rule)
{
	output << rule.key << " = {\n";
	output << "\tname = \"" << rule.name << "\"\n";
	if (rule.requiredDlc)
	{
		output << "\trequired_dlc = \"" << *rule.requiredDlc << "\"\n";
	}
	output << "\tgroup = \"" << rule.group << "\"\n";
	if (rule.icon)
	{
		output << "\ticon = \"" << *rule.icon << "\"\n";
	}
	for (const auto& option: rule.options)
	{
		output << option;
	}
	output << "}\n";

	return output;
}