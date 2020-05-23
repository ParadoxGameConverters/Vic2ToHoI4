#ifndef CULTURE_GROUP_NAMES_H
#define CULTURE_GROUP_NAMES_H



#include "Parser.h"
#include <map>
#include <string>
#include <vector>



namespace HoI4
{

class CultureGroupNames: commonItems::parser
{
  public:
	explicit CultureGroupNames(std::istream& theStream);

	[[nodiscard]] auto takeMaleNames() { return std::move(maleNamesMap); }
	[[nodiscard]] auto takeSurnames() { return std::move(surnamesMap); }

  private:
	std::map<std::string, std::vector<std::string>> maleNamesMap;
	std::map<std::string, std::vector<std::string>> surnamesMap;
};

} // namespace HoI4



#endif // CULTURE_GROUP_NAMES_H