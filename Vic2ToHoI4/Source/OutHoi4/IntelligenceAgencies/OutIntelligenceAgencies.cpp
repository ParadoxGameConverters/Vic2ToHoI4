#include "OutIntelligenceAgencies.h"
#include "OSCompatibilityLayer.h"
#include "OutIntelligenceAgency.h"
#include <fstream>



void HoI4::outputIntelligenceAgencies(const IntelligenceAgencies& intelligenceAgencies, const std::string& outputName)
{
	Utils::TryCreateFolder("output/" + outputName + "/common/intelligence_agencies/");
	std::ofstream out("output/" + outputName + "/common/intelligence_agencies/00_intelligence_agencies.txt");

	for (const auto& intelligenceAgency: intelligenceAgencies.getIntelligenceAgencies())
	{
		out << intelligenceAgency << "\n";
	}
}