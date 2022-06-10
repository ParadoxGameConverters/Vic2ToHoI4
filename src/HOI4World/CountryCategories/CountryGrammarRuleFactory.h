#ifndef COUNTRY_GRAMMAR_RULE_FACTORY_H
#define COUNTRY_GRAMMAR_RULE_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/CountryCategories/CountryGrammarRule.h"



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