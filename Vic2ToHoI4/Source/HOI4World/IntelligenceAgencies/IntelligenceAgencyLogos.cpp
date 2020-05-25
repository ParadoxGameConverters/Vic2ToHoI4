#include "IntelligenceAgencyLogos.h"



std::string HoI4::IntelligenceAgencyLogos::getLogo(const std::string& culture)
{
	if (const auto logo = cultureToLogoMap.find(culture); logo != cultureToLogoMap.end())
	{
		return logo->second;
	}

	return "GFX_intelligence_agency_logo_generic_1";
}