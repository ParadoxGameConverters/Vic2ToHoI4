#include "CountryGrammarRuleFactory.h"
#include "external/common_items/ParserHelpers.h"
#include "external/common_items/StringUtils.h"



HoI4::CountryGrammarRuleFactory::CountryGrammarRuleFactory()
{
	registerKeyword("category", [this](std::istream& theStream) {
		countryGrammarRule.category = commonItems::getString(theStream);
	});
	registerKeyword("vic2_tag", [this](std::istream& theStream) {
		countryGrammarRule.tag = commonItems::getString(theStream);
	});
	registerKeyword("extra", [this](std::istream& theStream) {
		countryGrammarRule.extra = commonItems::stringOfItem(theStream).getString();
		countryGrammarRule.extra->erase(0, countryGrammarRule.extra->find_first_not_of(" ="));
		countryGrammarRule.extra = commonItems::remQuotes(*countryGrammarRule.extra);
	});
}


HoI4::CountryGrammarRule HoI4::CountryGrammarRuleFactory::importCountryGrammarRule(std::istream& theStream)
{
	countryGrammarRule.category.clear();
	countryGrammarRule.tag.clear();
	countryGrammarRule.extra.reset();
	parseStream(theStream);
	return countryGrammarRule;
}