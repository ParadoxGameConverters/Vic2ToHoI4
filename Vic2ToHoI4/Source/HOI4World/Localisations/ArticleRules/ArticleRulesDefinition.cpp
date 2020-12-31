#include "ArticleRulesDefinition.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::ArticleRulesDefinition::ArticleRulesDefinition(std::istream& theStream)
{
	registerKeyword("language", [this](std::istream& theStream) {
		language = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("matcher", [this](std::istream& theStream) {
		matchers.push_back(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("replacement", [this](std::istream& theStream) {
		replacement = commonItems::singleString{theStream}.getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}