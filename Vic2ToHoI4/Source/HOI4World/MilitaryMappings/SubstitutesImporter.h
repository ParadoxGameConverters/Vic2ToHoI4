#ifndef SUBSTITUTES_IMPORTER_H
#define SUBSTITUTES_IMPORTER_H



#include "Parser.h"
#include <map>
#include <string>



namespace HoI4
{

class substitutesImporter: commonItems::parser
{
	public:
		explicit substitutesImporter(std::istream& theStream);

		[[nodiscard]] auto getSubstitutes() const { return substitutes; }

	private:
		std::map<std::string, std::string> substitutes;
};

}



#endif // SUBSTITUTES_IMPORTER_H