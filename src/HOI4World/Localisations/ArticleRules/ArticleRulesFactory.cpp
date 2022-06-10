#include "src/HOI4World/Localisations/ArticleRules/ArticleRulesFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/Localisations/ArticleRules/ArticleRuleBuilder.h"
#include "src/HOI4World/Localisations/ArticleRules/ArticleRulesDefinition.h"



HoI4::ArticleRules::Factory::Factory()
{
	registerKeyword("link", [this](std::istream& theStream) {
		const ArticleRulesDefinition definition(theStream);

		std::vector<ArticleRule> articleRules;
		for (const auto& matcher: definition.getMatchers())
		{
			articleRules.push_back(*ArticleRule::Builder()
												 .setMatcher(std::regex(matcher))
												 .setReplacement(definition.getReplacement())
												 .build());
		}

		if (rules->rules.contains(definition.getLanguage()))
		{
			auto& languageRules = rules->rules.at(definition.getLanguage());
			languageRules.insert(languageRules.end(), articleRules.begin(), articleRules.end());
		}
		else
		{
			rules->rules[definition.getLanguage()] = articleRules;
		}
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<HoI4::ArticleRules> HoI4::ArticleRules::Factory::getRules(const std::string& rulesFile)
{
	rules = std::make_unique<ArticleRules>();
	parseFile(rulesFile);

	return std::move(rules);
}
