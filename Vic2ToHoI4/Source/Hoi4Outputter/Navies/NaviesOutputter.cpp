#include "NaviesOutputter.h"



void HoI4::outputLegacyNavies(const HoI4::Navies& navies, std::ostream& output)
{
	output << "units = {\n";
	for (const auto& navy: navies.getMtgNavies())
	{
		output << navy;
	}
	output << "}\n";
}


void HoI4::outputMtgNavies(const HoI4::Navies& navies, std::ostream& output)
{
	output << "units = {\n";
	for (const auto& navy: navies.getLegacyNavies())
	{
		output << navy;
	}
	output << "}\n";
}