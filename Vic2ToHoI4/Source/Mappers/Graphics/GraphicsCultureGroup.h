#ifndef GRAPHICS_CULTURE_GROUP_H
#define GRAPHICS_CULTURE_GROUP_H



#include "Parser.h"
#include <map>
#include <string>
#include <vector>



namespace Mappers
{

class GraphicsCultureGroup
{
  public:
	class Factory;

	[[nodiscard]] const auto& getArmyPortraits() const { return armyPortraits; }
	[[nodiscard]] const auto& getNavyPortraits() const { return navyPortraits; }
	[[nodiscard]] const auto& getMaleMonarchPortraits() const { return maleMonarchPortraits; }
	[[nodiscard]] const auto& getFemaleMonarchPortraits() const { return femaleMonarchPortraits; }
	[[nodiscard]] const auto& getLeaderPortraits() const { return leaderPortraits; }
	[[nodiscard]] const auto& getIdeologyMinisterPortraits() const { return ideologyMinisterPortraits; }
	[[nodiscard]] const auto& getMaleOperativePortraits() const { return maleOperativePortraits; }
	[[nodiscard]] const auto& getFemaleOperativePortraits() const { return femaleOperativePortraits; }
	[[nodiscard]] const auto& getGraphicalCulture() const { return graphicalCulture; }
	[[nodiscard]] const auto& getGraphicalCulture2D() const { return graphicalCulture2D; }

  private:
	std::vector<std::string> armyPortraits;
	std::vector<std::string> navyPortraits;
	std::vector<std::string> maleMonarchPortraits;
	std::vector<std::string> femaleMonarchPortraits;
	std::map<std::string, std::vector<std::string>> leaderPortraits;
	std::map<std::string, std::vector<std::string>> ideologyMinisterPortraits;
	std::vector<std::string> maleOperativePortraits;
	std::vector<std::string> femaleOperativePortraits;
	std::string graphicalCulture;
	std::string graphicalCulture2D;
};

} // namespace Mappers



#endif // GRAPHICS_CULTURE_GROUP_H