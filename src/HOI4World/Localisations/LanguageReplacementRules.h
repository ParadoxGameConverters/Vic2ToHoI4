#ifndef LANGUAGE_REPLACEMENT_RULES
#define LANGUAGE_REPLACEMENT_RULES



#include "src/HOI4World/Localisations/LanguageReplacementRule.h"
#include "external/common_items/ConvenientParser.h"
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

} // namespace HoI4



#endif // LANGUAGE_REPLACEMENT_RULES