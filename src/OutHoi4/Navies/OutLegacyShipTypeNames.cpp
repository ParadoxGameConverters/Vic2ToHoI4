#include "OutLegacyShipTypeNames.h"
#include "src/HOI4World/Navies/LegacyShipTypeNames.h"



void HoI4::outLegacyShipTypeNames(std::ostream& out, const LegacyShipTypeNames& shipTypeNames)
{
	out << "\t" << shipTypeNames.getType() << " = {\n";
	out << "\t\tprefix = \"" << shipTypeNames.getPrefix() << "\"\n";
	out << "\t\tgeneric = { \"" << shipTypeNames.getGenericName() << "\" }\n";
	out << "\t\tunique = {\n";
	out << "\t\t\t";
	for (const auto& name: shipTypeNames.getNames())
	{
		out << "\"" << name << "\" ";
	}
	out << "\n";
	out << "\t\t}\n";
	out << "\t}\n";
	out << "\n";
}