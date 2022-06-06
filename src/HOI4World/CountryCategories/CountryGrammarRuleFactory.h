#ifndef COUNTRY_GRAMMAR_RULE_FACTORY_H
#define COUNTRY_GRAMMAR_RULE_FACTORY_H



#include "CountryGrammarRule.h"
#include "external/common_items/ConvenientParser.h"



namespace HoI4
{

class CountryGrammarRuleFactory: commonItems::parser
{
  public:
	CountryGrammarRuleFactory();
	CountryGrammarRule importCountryGrammarRule(std::istream& theStream);

  private:
	CountryGrammarRule countryGrammarRule;
};

} // namespace HoI4



#endif // COUNTRY_GRAMMAR_RULE_FACTORY_H