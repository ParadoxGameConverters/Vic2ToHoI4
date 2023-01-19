#ifndef SUBSTITUTES_IMPORTER_H
#define SUBSTITUTES_IMPORTER_H



#include "external/common_items/ConvenientParser.h"
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

} // namespace HoI4



#endif // SUBSTITUTES_IMPORTER_H