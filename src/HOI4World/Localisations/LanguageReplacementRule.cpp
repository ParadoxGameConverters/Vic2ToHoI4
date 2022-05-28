#include "LanguageReplacementRule.h"
#include "LanguageReplacements.h"



HoI4::LanguageReplacementRule::LanguageReplacementRule(const std::string& _matcher, std::istream& theStream):
	 matcher(_matcher, std::regex::icase)
{
	LanguageReplacements theReplacements(theStream);
	replacements = theReplacements.getReplacements();
}