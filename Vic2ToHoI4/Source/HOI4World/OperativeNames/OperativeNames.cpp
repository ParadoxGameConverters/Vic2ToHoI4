#include "OperativeNames.h"
#include "V2World/Country.h"
#include "OperativeNamesMappings.h"
#include "OperativeNamesMappingsFactory.h"



void HoI4::OperativeNames::addCountriesToNameSets(
	 const std::map<std::string, std::shared_ptr<Country>>& countries)
{
	const auto mappings = OperativeNamesMappings::Factory{}.getMappings();
	for (const auto& country: countries)
	{
		const auto& culture = country.second->getSourceCountry().getPrimaryCulture();
		const auto& namesSetName = mappings.getMatchingNamesSet(culture);
		if (auto namesSet = operativeNamesSets.find(namesSetName); namesSet != operativeNamesSets.end())
		{
			namesSet->second.addCountry(country.first);
		}
	}
}