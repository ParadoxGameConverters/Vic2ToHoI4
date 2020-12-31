#include "LanguageReplacementRules.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"
#include "StringUtils.h"



HoI4::LanguageReplacementRules::LanguageReplacementRules(std::istream& theStream)
{
	registerRegex(R"("[^"]+")", [this](const std::string& matcher, std::istream& theStream) {
		LanguageReplacementRule theRule(commonItems::remQuotes(matcher), theStream);
		theRules.push_back(theRule);
	});
	registerKeyword(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}