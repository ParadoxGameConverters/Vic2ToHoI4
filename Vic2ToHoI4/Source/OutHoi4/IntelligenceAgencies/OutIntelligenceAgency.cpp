#include "OutIntelligenceAgency.h"



std::ostream& HoI4::operator<<(std::ostream& output, const IntelligenceAgency& intelligenceAgency)
{
	output << "intelligence_agency = {\n";
	output << "\tpicture = " << intelligenceAgency.getLogo() << "\n";
	output << "\tnames = { ";
	for (const auto& name: intelligenceAgency.getNames())
	{
		output << '"' << name << "\" ";
	}
	output << "}\n";
	output << "\tdefault = { tag = " << intelligenceAgency.getCountry()
			 << " } available = { original_tag = " << intelligenceAgency.getCountry() << " }\n";
	output << "}\n";

	return output;
}
