#include "CountryCategories.h"
#include "CountryGrammarFactory.h"
#include "Log.h"



std::optional<std::string> expandIdeologyInExtra(const std::optional<std::string>& extra,
	 const std::set<std::string>& majorIdeologies)
{
	if (!extra)
	{
		return extra;
	}

	auto finalString = *extra;
	for (const auto& [ideology, placeholderText, fullText]:
		 std::vector<std::tuple<std::string, std::string, std::string>>{{"absolutist", "$ABSOLUTIST", "has_government = absolutist"},
			  {"communism", "$COMMUNISM", "has_government = communism"},
			  {"democratic", "$DEMOCRATIC", "has_government = democratic"},
			  {"fascism", "$FASCISM", "has_government = fascism"},
			  {"radical", "$RADICAL", "has_government = radical"},
		 {"neutrality", "$NEUTRALITY", "has_government = neutrality"}})
	{
		if (majorIdeologies.contains(ideology))
		{
			while (finalString.find(placeholderText) != std::string::npos)
			{
				finalString.replace(finalString.find(placeholderText), placeholderText.size(), fullText);
			}
		}
		else
		{
			std::regex placeholderRegexWithSpace("\\" + placeholderText + " ");
			finalString = std::regex_replace(finalString, placeholderRegexWithSpace, "");
			std::regex placeholderRegex("\\" + placeholderText);
			finalString = std::regex_replace(finalString, placeholderRegex, "");
		}
	}

	if (finalString == "")
	{
		return std::nullopt;
	}
	if (finalString == "NOT = { }")
	{
		return std::nullopt;
	}
	return finalString;
}


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
	 const std::set<std::string>& majorIdeologies,
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

		insertIntoCategories(countryGrammarRule.category,
			 *possibleTag,
			 expandIdeologyInExtra(countryGrammarRule.extra, majorIdeologies),
			 categories);
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
	 const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries,
	 const std::set<std::string>& majorIdeologies)
{
	std::map<std::string, TagsAndExtras> categories;

	std::set<std::string> mappedTags;
	applyAllGrammarRules(countryMapper, majorIdeologies, mappedTags, categories);
	handleMissedCountries(countries, mappedTags, categories);

	return categories;
}