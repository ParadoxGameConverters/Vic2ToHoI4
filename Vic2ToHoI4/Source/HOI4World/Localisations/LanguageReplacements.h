#ifndef LANGUAGE_REPLACEMENTS_H
#define LANGUAGE_REPLACEMENTS_H




#include "newParser.h"
#include <map>
#include <string>



namespace HoI4
{

class LanguageReplacements: commonItems::parser
{
	public:
		LanguageReplacements(std::istream& theStream);

		const auto& getReplacements() const { return replacements; }

	private:
		std::map<std::string, std::string> replacements;
};

}



#endif // LANGUAGE_REPLACEMENTS_H