#include "OutMtgShipTypeNames.h"
#include "src/HOI4World/Navies/MtgShipTypeNames.h"



void HoI4::outMtgShipTypeNames(std::ostream& out, const MtgShipTypeNames& shipTypeNames, const std::string_view tag)
{
	out << shipTypeNames.getType() << " = {\n";
	out << "\tname = " << shipTypeNames.getTheme() << "\n";
	out << "\n";
	out << "\tfor_countries = { " << tag << " }\n";
	out << "\n";
	out << "\ttype = ship\n";
	out << "\tship_types = { ";
	for (const auto& shipType: shipTypeNames.getShipTypes())
	{
		out << shipType << " ";
	}
	out << "}\n";
	out << "\n";
	out << "\tprefix = \"" << shipTypeNames.getPrefix() << "\"\n";
	out << "\tfallback_name = \"" << shipTypeNames.getFallbackName() << "\"\n";
	out << "\n";
	out << "\tunique = {\n";
	out << "\t\t";
	for (const auto& name: shipTypeNames.getNames())
	{
		out << "\"" << name << "\" ";
	}
	out << "\n";
	out << "\t}\n";
	out << "}\n";
	out << "\n";
}