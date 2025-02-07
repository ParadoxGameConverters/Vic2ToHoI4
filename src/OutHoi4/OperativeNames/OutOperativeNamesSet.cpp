#include "src/OutHoi4/OperativeNames/OutOperativeNamesSet.h"
#include <fstream>



void HoI4::outputOperativeNamesSet(const OperativeNamesSet& operativeNamesSet, const std::filesystem::path& outputName)
{
	std::ofstream out("output" / outputName / "common/units/codenames_operatives" / operativeNamesSet.getFilename());

	out << operativeNamesSet.getWrapper() << " = {\n";
	out << "\tname = " << operativeNamesSet.getName() << "\n";
	out << "\n";

	out << "\tfor_countries = { ";
	for (const auto& country: operativeNamesSet.getCountries())
	{
		out << country << ' ';
	}
	out << "}\n";
	out << "\n";

	out << "\ttype = codename\n";
	out << "\n";
	out << "\tfallback_name = \"Agent %d\"";
	out << "\n";

	out << "\tunique = {\n";
	for (const auto& name: operativeNamesSet.getNames())
	{
		out << "\t\t\"" << name << "\"\n";
	}
	out << "\t}\n";

	out << "}";

	out.close();
}