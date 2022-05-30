#include "CountryCategories.h"
#include "CountryGrammarFactory.h"
#include "Log.h"
#include <ranges>
#include <unordered_set>



std::optional<std::string> expandIdeologyInExtra(const std::optional<std::string>& extra,
	 const std::set<std::string>& majorIdeologies)
{
	if (!extra)
	{
		return std::nullopt;
	}

	auto finalString = *extra;
	for (const auto& [ideology, placeholderText, fullText]:
		 std::vector<std::tuple<std::string, std::string, std::string>>{
			  {"absolutist", "$ABSOLUTIST", "has_government = absolutist"},
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

	if (finalString.empty())
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
	std::unordered_set<std::string> definedCategories;
	for (const auto& countryGrammarRule: HoI4::CountryGrammarFactory().importCountryGrammar())
	{
		definedCategories.insert(countryGrammarRule.category);
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

	for (const auto& category: definedCategories)
	{
		categories.emplace(category, HoI4::TagsAndExtras{});
	}
}


void handleMissedCountries(const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries,
	 std::set<std::string>& mappedTags,
	 std::map<std::string, HoI4::TagsAndExtras>& categories,
	 bool debug)
{
	for (const auto& tag: countries | std::views::keys)
	{
		if (mappedTags.contains(tag))
		{
			continue;
		}

		if (debug)
		{
			Log(LogLevel::Warning) << tag << " was not in any language category. Defaulting to tag_mscne";
		}
		insertIntoCategories("tag_mscne", tag, std::nullopt, categories);
	}
}


std::map<std::string, HoI4::TagsAndExtras> HoI4::createCountryCategories(const Mappers::CountryMapper& countryMapper,
	 const std::map<std::string, std::shared_ptr<HoI4::Country>>& countries,
	 const std::set<std::string>& majorIdeologies,
	 bool debug)
{
	std::map<std::string, TagsAndExtras> categories;

	std::set<std::string> mappedTags;
	applyAllGrammarRules(countryMapper, majorIdeologies, mappedTags, categories);
	handleMissedCountries(countries, mappedTags, categories, debug);

	return categories;
}