#include "IntelligenceAgencyLogos.h"
#include "IntelligenceAgencyLogoMapping.h"
#include <sstream>



std::string HoI4::IntelligenceAgencyLogos::getLogo(const std::string& culture)
{
	if (const auto logo = cultureToLogoMap.find(culture); logo != cultureToLogoMap.end())
	{
		return logo->second;
	}

	return "GFX_intelligence_agency_logo_generic_1";
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
	std::stringstream input;
	input << "link = { culture = north_german logo = GFX_intelligence_agency_logo_ger}";
	parseStream(input);

	return std::make_unique<IntelligenceAgencyLogos>(std::map<std::string, std::string>(cultureToLogoMap));
}