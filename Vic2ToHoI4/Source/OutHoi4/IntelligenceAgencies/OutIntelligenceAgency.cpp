#include "OutIntelligenceAgency.h"



std::ostream& HoI4::operator<<(std::ostream& output, const IntelligenceAgency& intelligenceAgency)
{
	output << "intelligence_agency = {\n";
	output << "\tpicture = " << intelligenceAgency.getLogo() << "\n";
	output << "\tnames = { \"" << intelligenceAgency.getName() << "\" }\n";
	output << "\tdefault = { tag = " << intelligenceAgency.getCountry() << " }\n";
	output << "\tavailable = { original_tag = " << intelligenceAgency.getCountry() << " }\n";
	output << "}\n";

	return output;
}