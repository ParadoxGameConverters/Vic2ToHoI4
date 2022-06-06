#include "LanguageReplacementRules.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "external/common_items/StringUtils.h"



HoI4::LanguageReplacementRules::LanguageReplacementRules(std::istream& theStream)
{
	registerRegex(R"("[^"]+")", [this](const std::string& matcher, std::istream& theStream) {
		LanguageReplacementRule theRule(commonItems::remQuotes(matcher), theStream);
		theRules.push_back(theRule);
	});
	registerKeyword(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}