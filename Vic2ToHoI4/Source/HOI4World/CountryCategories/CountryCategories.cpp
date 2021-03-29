#include "CountryCategories.h"
#include "CountryGrammarFactory.h"
#include "Log.h"



void insertIntoCategories(const std::string& categoryName,
	 const std::string& tag,
	 const std::optional<std::string>& extra,
	 std::map<std::string, HoI4::TagsAndExtras>& categories)
{
	if (auto category = categories.find(categoryName); category != categories.end())
	{
		category->second.emplace(tag, extra);
	}
	else
	{
		categories.emplace(categoryName, HoI4::TagsAndExtras{{tag, extra}});
	}
}


void applyAllGrammarRules(const Mappers::CountryMapper& countryMapper,
	 std::set<std::string>& mappedTags,
	 std::map<std::string, HoI4::TagsAndExtras>& categories)
{
	for (const auto& countryGrammarRule: HoI4::CountryGrammarFactory().importCountryGrammar())
	{
		const auto possibleTag = countryMapper.getHoI4Tag(countryGrammarRule.tag);
		if (!possibleTag)
		{
			continue;
		}

		insertIntoCategories(countryGrammarRule.category, *possibleTag, countryGrammarRule.extra, categories);
		mappedTags.insert(*possibleTag);
	}
}


void handleMissedCountries(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries,
	 std::set<std::string>& mappedTags,
	 std::map<std::string, HoI4::TagsAndExtras>& categories)
{
	for (const auto& [tag, unused]: countries)
	{
		if (mappedTags.contains(tag))
		{
			continue;
		}

		Log(LogLevel::Warning) << tag << " was not in any language category. Defaulting to tag_mscne";
		insertIntoCategories("tag_mscne", tag, std::nullopt, categories);
	}
}


std::map<std::string, HoI4::TagsAndExtras> HoI4::createCountryCategories(const Mappers::CountryMapper& countryMapper,
	 const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries)
{
	std::map<std::string, TagsAndExtras> categories;

	std::set<std::string> mappedTags;
	applyAllGrammarRules(countryMapper, mappedTags, categories);
	handleMissedCountries(countries, mappedTags, categories);

	return categories;
}