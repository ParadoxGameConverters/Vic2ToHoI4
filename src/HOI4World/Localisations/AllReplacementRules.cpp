#include "AllReplacementRules.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::AllReplacementRules::AllReplacementRules(std::istream& theStream)
{
	registerRegex("[a-zA-Z_]+", [this](const std::string& language, std::istream& theStream) {
		LanguageReplacementRules theRules(theStream);
		rulesInLanguages.insert(std::make_pair(language, theRules));
	});
	registerKeyword(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}


std::optional<HoI4::LanguageReplacementRules> HoI4::AllReplacementRules::getRulesForLanguage(
	 const std::string& language)
{
	if (auto rules = rulesInLanguages.find(language); rules != rulesInLanguages.end())
	{
		return rules->second;
	}
	else
	{
		return std::nullopt;
	}
}