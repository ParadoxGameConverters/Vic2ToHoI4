#ifndef GRAPHICS_CULTURE_GROUP_H
#define GRAPHICS_CULTURE_GROUP_H



#include "Parser.h"
#include <map>
#include <string>
#include <vector>



namespace Mappers
{

class GraphicsCultureGroup: commonItems::parser
{
  public:
	explicit GraphicsCultureGroup(std::istream& theStream);

	auto getArmyPortraits() const { return armyPortraits; }
	auto getNavyPortraits() const { return navyPortraits; }
	auto getMaleMonarchPortraits() const { return maleMonarchPortraits; }
	auto getFemaleMonarchPortraits() const { return femaleMonarchPortraits; }
	auto getLeaderPortraits() const { return leaderPortraits; }
	auto getIdeologyMinisterPortraits() const { return ideologyMinisterPortraits; }
	auto getGraphicalCulture() const { return graphicalCulture; }
	auto getGraphicalCulture2D() const { return graphicalCulture2D; }

  private:
	std::vector<std::string> armyPortraits;
	std::vector<std::string> navyPortraits;
	std::vector<std::string> maleMonarchPortraits;
	std::vector<std::string> femaleMonarchPortraits;
	std::map<std::string, std::vector<std::string>> leaderPortraits;
	std::map<std::string, std::vector<std::string>> ideologyMinisterPortraits;
	std::string graphicalCulture;
	std::string graphicalCulture2D;
};

} // namespace Mappers



#endif // GRAPHICS_CULTURE_GROUP_H