#include "OutCountryCategory.h"



void HoI4::outputCountryCategory(std::ostream& out, const std::string& category, const TagsAndExtras& tagsAndExtras)
{
	out << category << "= {\n";
	out << "\tOR = {\n";
	for (const auto& [tag, extra]: tagsAndExtras)
	{
		if (!extra)
		{
			out << "\t\ttag = " << tag << "\n";
		}
		else
		{
			out << "\t\tAND = {\n";
			out << "\t\t\ttag = " << tag << "\n";
			out << "\t\t\t" << *extra << "\n";
			out << "\t\t}\n";
		}
	}
	out << "\t}\n";
	out << "}\n";
	out << "\n";
}