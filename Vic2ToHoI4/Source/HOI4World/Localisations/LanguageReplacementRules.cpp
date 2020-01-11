#include "LanguageReplacementRules.h"
#include "ParserHelpers.h"
#include "StringUtils.h"



HoI4::LanguageReplacementRules::LanguageReplacementRules(std::istream& theStream)
{
	registerKeyword(std::regex("\"[^\"]+\""), [this](const std::string& matcher, std::istream& theStream)
	{
		LanguageReplacementRule theRule(stringutils::remQuotes(matcher), theStream);
		theRules.push_back(theRule);
	});
	registerKeyword(std::regex("[a-zA-Z0-9_\\.:]+"), commonItems::ignoreItem);

	parseStream(theStream);
}