#include "IntelligenceAgencyLogos.h"
#include "IntelligenceAgencyLogoMapping.h"



std::string HoI4::IntelligenceAgencyLogos::getLogo(const std::string& culture)
{
	if (const auto logo = cultureToLogoMap.find(culture); logo != cultureToLogoMap.end())
	{
		return logo->second;
	}

	const std::uniform_int_distribution<int> generator(1, 8);
	return "GFX_intelligence_agency_logo_generic_" + std::to_string(static_cast<int>(generator(rng)));
}


HoI4::IntelligenceAgencyLogos::Factory::Factory()
{
	registerKeyword("link", [this](const std::string& unused, std::istream& theStream) {
		IntelligenceAgencyLogoMapping mapping(theStream);
		for (const auto& culture: mapping.takeCultures())
		{
			cultureToLogoMap[culture] = mapping.takeLogo();
		}
	});
}


std::unique_ptr<HoI4::IntelligenceAgencyLogos> HoI4::IntelligenceAgencyLogos::Factory::getIntelligenceAgencyLogos()
{
	parseFile("DataFiles/IntelligenceAgencyLogos.txt");

	return std::make_unique<IntelligenceAgencyLogos>(std::map<std::string, std::string>(cultureToLogoMap));
}