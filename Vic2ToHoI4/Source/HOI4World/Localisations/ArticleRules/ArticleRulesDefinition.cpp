#include "ArticleRulesDefinition.h"
#include "ParserHelpers.h"



HoI4::ArticleRulesDefinition::ArticleRulesDefinition(std::istream& theStream)
{
	registerKeyword("language", [this](const std::string& unused, std::istream& theStream) {
		language = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("matcher", [this](const std::string& unused, std::istream& theStream) {
		matchers.push_back(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("result", [this](const std::string& unused, std::istream& theStream) {
		result = commonItems::singleString{theStream}.getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}