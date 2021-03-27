#ifndef GRAPHICS_MAPPER_H_
#define GRAPHICS_MAPPER_H_



#include "GraphicsCultureGroupFactory.h"
#include "Parser.h"
#include <map>
#include <optional>
#include <random>
#include <string>
#include <vector>



namespace Mappers
{

using cultureGroupToPortraitsMap = std::map<std::string, std::vector<std::string>>;
using ideologyToPortraitsMap = std::map<std::string, cultureGroupToPortraitsMap>;
using cultureGroupToGraphicalCultureMap = std::map<std::string, std::string>;


class GraphicsMapper: commonItems::parser
{
  public:
	void init();

	[[nodiscard]] std::vector<std::string> getArmyPortraits(const std::string& cultureGroup) const;
	[[nodiscard]] std::vector<std::string> getNavyPortraits(const std::string& cultureGroup) const;
	[[nodiscard]] std::vector<std::string> getMaleMonarchPortraits(const std::string& cultureGroup) const;
	[[nodiscard]] std::vector<std::string> getFemaleMonarchPortraits(const std::string& cultureGroup) const;
	[[nodiscard]] std::string getLeaderPortrait(const std::string& cultureGroup, const std::string& ideology);
	[[nodiscard]] std::string getIdeologyMinisterPortrait(const std::string& cultureGroup, const std::string& ideology);
	[[nodiscard]] std::optional<std::string> getGraphicalCulture(const std::string& cultureGroup) const;
	[[nodiscard]] std::optional<std::string> get2dGraphicalCulture(const std::string& cultureGroup) const;

  private:
	GraphicsCultureGroup::Factory graphicsCultureGroupFactory;

	void loadLeaderPortraitMappings(const std::string& cultureGroup,
		 const std::map<std::string, std::vector<std::string>>& portraitMappings);
	void loadIdeologyMinisterPortraitMappings(const std::string& cultureGroup,
		 const std::map<std::string, std::vector<std::string>>& portraitMappings);

	[[nodiscard]] std::vector<std::string> getLeaderPortraits(const std::string& cultureGroup,
		 const std::string& ideology) const;
	[[nodiscard]] std::vector<std::string> getIdeologyMinisterPortraits(const std::string& cultureGroup,
		 const std::string& ideology) const;

	cultureGroupToPortraitsMap armyPortraitMappings;
	cultureGroupToPortraitsMap navyPortraitMappings;
	cultureGroupToPortraitsMap maleMonarchMappings;
	cultureGroupToPortraitsMap femaleMonarchMappings;
	ideologyToPortraitsMap leaderPortraitMappings;
	ideologyToPortraitsMap ideologyMinisterMappings;
	cultureGroupToGraphicalCultureMap graphicalCultureMap;
	cultureGroupToGraphicalCultureMap graphicalCulture2dMap;

	std::mt19937 rng;
};

} // namespace Mappers



#endif // GRAPHICS_MAPPER_H_