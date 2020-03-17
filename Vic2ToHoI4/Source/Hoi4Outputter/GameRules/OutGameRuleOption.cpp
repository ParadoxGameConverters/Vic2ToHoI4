#include "OutGameRuleOption.h"



std::ostream& HoI4::operator<<(std::ostream& output, const HoI4::GameRuleOption& option)
{
	output << "\toption = {\n";
	output << "\t\tname = " << option.name << "\n";
	output << "\t\ttext = " << option.text << "\n";
	output << "\t\tdesc = " << option.description << "\n";
	if (option.allowAchievements)
	{
		output << "\t\tallow_achievements = " << (option.allowAchievements == true ? "yes" : "no") << "\n";
	}
	output << "\t}\n";

	return output;
}