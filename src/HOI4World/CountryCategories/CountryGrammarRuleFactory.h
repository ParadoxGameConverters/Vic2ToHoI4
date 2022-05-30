#ifndef COUNTRY_GRAMMAR_RULE_FACTORY_H
#define COUNTRY_GRAMMAR_RULE_FACTORY_H



#include "CountryGrammarRule.h"
#include "Parser.h"



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