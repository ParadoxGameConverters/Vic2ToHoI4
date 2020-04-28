#ifndef LANGUAGE_REPLACEMENT_RULES
#define LANGUAGE_REPLACEMENT_RULES



#include "LanguageReplacementRule.h"
#include "Parser.h"
#include <vector>



namespace HoI4
{

class LanguageReplacementRules: commonItems::parser
{
	public:
		LanguageReplacementRules(std::istream& theStream);

		const auto& getTheRules() const { return theRules; }

	private:
		std::vector<LanguageReplacementRule> theRules;
};

}



#endif // LANGUAGE_REPLACEMENT_RULES