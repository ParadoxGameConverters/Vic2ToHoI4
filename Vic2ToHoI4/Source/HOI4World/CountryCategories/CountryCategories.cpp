#include "CountryCategories.h"
#include "CountryGrammarFactory.h"



std::map<std::string, HoI4::TagsAndExtras> HoI4::createCountryCategories(const Mappers::CountryMapper& countryMapper)
{
	const auto countryGrammar = CountryGrammarFactory().importCountryGrammar();

	std::map<std::string, TagsAndExtras> categories;
	for (const auto& countryGrammarRule: countryGrammar)
	{
		const auto possibleTag = countryMapper.getHoI4Tag(countryGrammarRule.tag);
		if (!possibleTag)
		{
			continue;
		}
		
		if (auto category = categories.find(countryGrammarRule.category); category != categories.end())
		{
			category->second.emplace(*possibleTag, countryGrammarRule.extra);
		}
		else
		{
			categories.emplace(countryGrammarRule.category, TagsAndExtras{{*possibleTag, countryGrammarRule.extra}});
		}
	}

	return categories;
}