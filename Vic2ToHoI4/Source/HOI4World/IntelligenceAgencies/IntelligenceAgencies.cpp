#include "IntelligenceAgencies.h"



std::unique_ptr<HoI4::IntelligenceAgencies> HoI4::IntelligenceAgencies::Factory::createIntelligenceAgencies(
	 const std::map<std::string, std::shared_ptr<Country>>& countries,
	 namesMapper& theNamesMapper)
{
	std::vector<IntelligenceAgency> theAgencies;
	for (const auto& country: countries)
	{
		theAgencies.emplace_back(IntelligenceAgency{*country.second, theNamesMapper});
	}

	return std::make_unique<IntelligenceAgencies>(std::move(theAgencies));
}