#ifndef ALL_REPLACEMENT_RULES_H
#define ALL_REPLACEMENT_RULES_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/Localisations/LanguageReplacementRules.h"
#include <map>
#include <optional>
#include <string>



namespace HoI4
{

class AllReplacementRules: commonItems::parser
{
  public:
	AllReplacementRules(std::istream& theStream);

	std::optional<LanguageReplacementRules> getRulesForLanguage(const std::string& language);

  private:
	std::map<std::string, LanguageReplacementRules> rulesInLanguages;
};

} // namespace HoI4



#endif // ALL_REPLACEMENT_RULES_H