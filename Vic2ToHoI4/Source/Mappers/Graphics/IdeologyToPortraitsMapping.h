#ifndef IDEOLOGY_TO_PORTRAITS_MAPPING_H
#define IDEOLOGY_TO_PORTRAITS_MAPPING_H



#include "Parser.h"
#include <map>
#include <string>
#include <vector>



namespace Mappers
{

class IdeologyToPortraitsMapping: commonItems::parser
{
  public:
	explicit IdeologyToPortraitsMapping(std::istream& theStream);

	auto getMap() const { return theMap; }

  private:
	std::map<std::string, std::vector<std::string>> theMap;
};

} // namespace Mappers



#endif // IDEOLOGY_TO_PORTRAITS_MAPPING_H