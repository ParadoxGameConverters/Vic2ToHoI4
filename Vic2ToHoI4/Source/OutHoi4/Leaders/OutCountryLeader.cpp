#include "OutCountryLeader.h"



void HoI4::outputCountryLeader(std::ostream& output, const HoI4::CountryLeader& leader)
{
	output << "create_country_leader = {\n";
	output << "\tname = \"" << leader.getName() << "\"\n";
	output << "\tdesc = \"" << leader.getDescription() << "\"\n";
	output << "\tpicture = \"" << leader.getPicture() << "\"\n";
	output << "\texpire = \"1965.1.1\"\n";
	output << "\tideology = " << leader.getIdeology() << "\n";
	output << "\ttraits = {\n";
	for (const auto& trait: leader.getTraits())
	{
		output << "\t\t" << trait << "\n";
	}
	output << "\t}\n";
	output << "}\n";
}