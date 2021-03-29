#include "CountryCategories.h"
#include "CountryGrammarFactory.h"
#include "Log.h"



std::map<std::string, HoI4::TagsAndExtras> HoI4::createCountryCategories(const Mappers::CountryMapper& countryMapper,
	 const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries)
{
	const auto countryGrammar = CountryGrammarFactory().importCountryGrammar();

	std::set<std::string> mappedTags;

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
		mappedTags.insert(*possibleTag);
	}

	for (const auto& [tag, unused]: countries)
	{
		if (mappedTags.contains(tag))
		{
			continue;
		}

		Log(LogLevel::Warning) << tag << " was not in any language category. Defaulting to tag_mscne";
		if (auto category = categories.find("tag_mscne"); category != categories.end())
		{
			category->second.emplace(tag, std::nullopt);
		}
		else
		{
			categories.emplace("tag_mscne", TagsAndExtras{{tag, std::nullopt}});
		}
	}

	return categories;
}