#include "IntelligenceAgencies.h"
#include "IntelligenceAgencyLogos.h"



std::unique_ptr<HoI4::IntelligenceAgencies> HoI4::IntelligenceAgencies::Factory::createIntelligenceAgencies(
	 const std::map<std::string, std::shared_ptr<Country>>& countries,
	 Names& names)
{
	std::vector<IntelligenceAgency> theAgencies;

	const auto intelligenceAgencyLogos = IntelligenceAgencyLogos::Factory().getIntelligenceAgencyLogos();
	for (const auto& country: countries)
	{
		theAgencies.emplace_back(IntelligenceAgency{*country.second, names, *intelligenceAgencyLogos});
	}
	theAgencies.emplace_back(IntelligenceAgency{"Rooke", "GFX_intelligence_agency_logo_generic_1"});
	theAgencies.emplace_back(IntelligenceAgency{"Tower", "GFX_intelligence_agency_logo_generic_2"});
	theAgencies.emplace_back(IntelligenceAgency{"Snake", "GFX_intelligence_agency_logo_generic_3"});
	theAgencies.emplace_back(IntelligenceAgency{"Stag", "GFX_intelligence_agency_logo_generic_4"});
	theAgencies.emplace_back(IntelligenceAgency{"Golden Lion", "GFX_intelligence_agency_logo_generic_5"});
	theAgencies.emplace_back(IntelligenceAgency{"Arrow", "GFX_intelligence_agency_logo_generic_6"});
	theAgencies.emplace_back(IntelligenceAgency{"Lion Head", "GFX_intelligence_agency_logo_generic_7"});
	theAgencies.emplace_back(IntelligenceAgency{"Golden Eagle", "GFX_intelligence_agency_logo_generic_8"});

	return std::make_unique<IntelligenceAgencies>(std::move(theAgencies));
}