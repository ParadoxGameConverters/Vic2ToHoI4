#include "src/HOI4World/OperativeNames/OperativeNames.h"
#include "src/HOI4World/OperativeNames/OperativeNamesMappings.h"
#include "src/HOI4World/OperativeNames/OperativeNamesMappingsFactory.h"
#include "src/V2World/Countries/Country.h"



void HoI4::OperativeNames::addCountriesToNameSets(const std::map<std::string, std::shared_ptr<Country>>& countries)
{
	const auto mappings = OperativeNamesMappings::Factory().getMappings();
	for (const auto& country: countries)
	{
		const auto& culture = country.second->getPrimaryCulture();
		const auto& namesSetName = mappings.getMatchingNamesSet(culture);
		if (auto namesSet = operativeNamesSets.find(namesSetName); namesSet != operativeNamesSets.end())
		{
			namesSet->second.addCountry(country.first);
		}
	}
}