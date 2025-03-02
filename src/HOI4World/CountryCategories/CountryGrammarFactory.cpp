#include "src/HOI4World/CountryCategories/CountryGrammarFactory.h"



HoI4::CountryGrammarFactory::CountryGrammarFactory()
{
	registerKeyword("link", [this](std::istream& theStream) {
		countryGrammarRules.push_back(countryGrammarRuleFactory.importCountryGrammarRule(theStream));
	});
}


std::vector<HoI4::CountryGrammarRule> HoI4::CountryGrammarFactory::importCountryGrammar()
{
	countryGrammarRules.clear();
	parseFile(std::filesystem::path("Configurables/CountryGrammar.txt"));
	return countryGrammarRules;
}