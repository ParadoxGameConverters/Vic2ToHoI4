#include "src/OutHoi4/IntelligenceAgencies/OutIntelligenceAgencies.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/OutHoi4/IntelligenceAgencies/OutIntelligenceAgency.h"
#include <fstream>



void HoI4::outputIntelligenceAgencies(const IntelligenceAgencies& intelligenceAgencies,
	 const std::filesystem::path& outputName)
{
	const std::filesystem::path folder = "output" / outputName / "common/intelligence_agencies/";
	if (!std::filesystem::create_directories(folder))
	{
		throw std::runtime_error("Could not create " + folder.string());
	}

	const std::filesystem::path file = folder / "00_intelligence_agencies.txt";
	std::ofstream out(file);
	if (!out.is_open())
	{
		throw std::runtime_error("Could not create " + file.string());
	}

	for (const auto& intelligenceAgency: intelligenceAgencies.getIntelligenceAgencies())
	{
		out << intelligenceAgency << "\n";
	}
}