#include "ArticleRulesDefinition.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



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