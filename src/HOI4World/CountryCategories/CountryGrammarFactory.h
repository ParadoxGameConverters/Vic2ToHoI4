#ifndef COUNTRY_GRAMMAR_FACTORY_H
#define COUNTRY_GRAMMAR_FACTORY_H



#include "CountryGrammarRule.h"
#include "CountryGrammarRuleFactory.h"
#include "external/common_items/ConvenientParser.h"
#include <vector>



namespace HoI4
{

class CountryGrammarFactory: commonItems::parser
{
  public:
	CountryGrammarFactory();
	std::vector<CountryGrammarRule> importCountryGrammar();

  private:
	CountryGrammarRuleFactory countryGrammarRuleFactory;

	std::vector<CountryGrammarRule> countryGrammarRules;
};

} // namespace HoI4



#endif // COUNTRY_GRAMMAR_FACTORY_H