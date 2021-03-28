#include "CountryCategories.h"
#include "CountryGrammarFactory.h"



std::map<std::string, HoI4::tagsAndExtras> HoI4::createCountryCategories()
{
	const auto countryGrammar = CountryGrammarFactory().importCountryGrammar();

	std::map<std::string, tagsAndExtras> categories;
	for (const auto& countryGrammarRule: countryGrammar)
	{
		if (auto category = categories.find(countryGrammarRule.category); category != categories.end())
		{
			category->second.emplace(countryGrammarRule.tag, countryGrammarRule.extra);
		}
		else
		{
			categories.emplace(countryGrammarRule.category,
				 tagsAndExtras{{countryGrammarRule.tag, countryGrammarRule.extra}});
		}
	}

	return categories;
}