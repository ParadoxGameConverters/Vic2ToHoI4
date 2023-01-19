#include "src/HOI4World/IntelligenceAgencies/IntelligenceAgencyLogos.h"
#include "src/HOI4World/IntelligenceAgencies/IntelligenceAgencyLogoMapping.h"



std::string HoI4::IntelligenceAgencyLogos::getLogo(const std::string& culture)
{
	if (const auto logo = cultureToLogoMap.find(culture); logo != cultureToLogoMap.end())
	{
		return logo->second;
	}

	const auto randomValue = static_cast<int>(std::uniform_int_distribution<int>{1, 8}(generator));
	return "GFX_intelligence_agency_logo_generic_" + std::to_string(randomValue);
}


HoI4::IntelligenceAgencyLogos::Factory::Factory()
{
	registerKeyword("link", [this](std::istream& theStream) {
		IntelligenceAgencyLogoMapping mapping(theStream);
		for (const auto& culture: mapping.takeCultures())
		{
			cultureToLogoMap[culture] = mapping.getLogo();
		}
	});
}


std::unique_ptr<HoI4::IntelligenceAgencyLogos> HoI4::IntelligenceAgencyLogos::Factory::getIntelligenceAgencyLogos()
{
	parseFile("Configurables/IntelligenceAgencyLogos.txt");

	return std::make_unique<IntelligenceAgencyLogos>(std::map<std::string, std::string>(cultureToLogoMap));
}