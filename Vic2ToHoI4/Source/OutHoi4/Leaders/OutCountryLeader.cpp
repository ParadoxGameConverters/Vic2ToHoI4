#include "OutCountryLeader.h"



void HoI4::outputCountryLeader(std::ostream& output, const HoI4::CountryLeader& leader)
{
	output << "create_country_leader = {\n";
	output << "    name = \"" << leader.getName() << "\"\n";
	output << "    desc = \"" << leader.getDescription() << "\"\n";
	output << "    picture = \"" << leader.getPicture() << "\"\n";
	output << "    expire = \"1965.1.1\"\n";
	output << "    ideology = " << leader.getIdeology() << "\n";
	output << "    traits = {\n";
	output << "    }\n";
	output << "}\n";
}