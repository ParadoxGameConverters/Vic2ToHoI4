#ifndef LANGUAGE_REPLACEMENT_RULE_H
#define LANGUAGE_REPLACEMENT_RULE_H



#include "newParser.h"
#include <map>
#include <regex>
#include <string>



namespace HoI4
{

class LanguageReplacementRule: commonItems::parser
{
	public:
		LanguageReplacementRule(const std::string& matcher, std::istream& theStream);

		const auto& getMatcher() const { return matcher; }
		const auto& getReplacements() const { return replacements; }

	private:
		std::regex matcher;
		std::map<std::string, std::string> replacements;
};

}



#endif // LANGUAGE_REPLACEMENT_RULE_H