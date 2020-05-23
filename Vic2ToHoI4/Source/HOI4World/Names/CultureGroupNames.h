#ifndef CULTURE_GROUP_NAMES_H
#define CULTURE_GROUP_NAMES_H



#include "Parser.h"
#include <map>
#include <string>
#include <vector>



namespace HoI4
{

class cultureGroup: commonItems::parser
{
  public:
	explicit cultureGroup(std::istream& theStream);

	[[nodiscard]] auto getMaleNames() const { return maleNamesMap; }
	[[nodiscard]] auto getSurnames() const { return surnamesMap; }

  private:
	std::map<std::string, std::vector<std::string>> maleNamesMap;
	std::map<std::string, std::vector<std::string>> surnamesMap;
};

} // namespace HoI4



#endif // CULTURE_GROUP_NAMES_H