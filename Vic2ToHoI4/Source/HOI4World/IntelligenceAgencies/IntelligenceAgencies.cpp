#include "IntelligenceAgencies.h"
#include "IntelligenceAgencyLogos.h"



std::unique_ptr<HoI4::IntelligenceAgencies> HoI4::IntelligenceAgencies::Factory::createIntelligenceAgencies(
	 const std::map<std::string, std::shared_ptr<Country>>& countries,
	 Names& names)
{
	std::vector<IntelligenceAgency> theAgencies;

	IntelligenceAgencyLogos intelligenceAgencyLogos = IntelligenceAgencyLogos::Factory::getIntelligenceAgencyLogos();
	for (const auto& country: countries)
	{
		theAgencies.emplace_back(IntelligenceAgency{*country.second, names, intelligenceAgencyLogos});
	}

	return std::make_unique<IntelligenceAgencies>(std::move(theAgencies));
}