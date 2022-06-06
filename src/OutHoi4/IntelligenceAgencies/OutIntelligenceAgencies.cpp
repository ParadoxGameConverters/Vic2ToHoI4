#include "OutIntelligenceAgencies.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "OutIntelligenceAgency.h"
#include <fstream>



void HoI4::outputIntelligenceAgencies(const IntelligenceAgencies& intelligenceAgencies, const std::string& outputName)
{
	if (!commonItems::TryCreateFolder("output/" + outputName + "/common/intelligence_agencies/"))
	{
		throw std::runtime_error("Could not create output/" + outputName + "/common/intelligence_agencies/");
	}
	std::ofstream out("output/" + outputName + "/common/intelligence_agencies/00_intelligence_agencies.txt");
	if (!out.is_open())
	{
		throw std::runtime_error(
			 "Could not create output/" + outputName + "/common/intelligence_agencies/00_intelligence_agencies.txt");
	}

	for (const auto& intelligenceAgency: intelligenceAgencies.getIntelligenceAgencies())
	{
		out << intelligenceAgency << "\n";
	}
}