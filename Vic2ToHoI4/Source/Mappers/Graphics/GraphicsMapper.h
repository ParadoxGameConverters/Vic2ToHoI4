#ifndef GRAPHICS_MAPPER_H
#define GRAPHICS_MAPPER_H



#include <map>
#include <optional>
#include <string>
#include <vector>



namespace Mappers
{

using cultureGroupToPortraitsMap = std::map<std::string, std::vector<std::string>>;
using ideologyToPortraitsMap = std::map<std::string, cultureGroupToPortraitsMap>;
using cultureGroupToGraphicalCultureMap = std::map<std::string, std::string>;


class GraphicsMapper
{
  public:
	class Factory;

	[[nodiscard]] std::vector<std::string> getArmyPortraits(const std::string& cultureGroup) const;
	[[nodiscard]] std::vector<std::string> getNavyPortraits(const std::string& cultureGroup) const;
	[[nodiscard]] std::vector<std::string> getMaleMonarchPortraits(const std::string& cultureGroup) const;
	[[nodiscard]] std::vector<std::string> getFemaleMonarchPortraits(const std::string& cultureGroup) const;
	[[nodiscard]] std::string getLeaderPortrait(const std::string& cultureGroup, const std::string& ideology);
	[[nodiscard]] std::string getIdeologyMinisterPortrait(const std::string& cultureGroup, const std::string& ideology);
	[[nodiscard]] std::vector<std::string> getMaleOperativePortraits(const std::string& cultureGroup) const;
	[[nodiscard]] std::vector<std::string> getFemaleOperativePortraits(const std::string& cultureGroup) const;
	[[nodiscard]] std::optional<std::string> getGraphicalCulture(const std::string& cultureGroup) const;
	[[nodiscard]] std::optional<std::string> get2dGraphicalCulture(const std::string& cultureGroup) const;

  private:
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
	cultureGroupToPortraitsMap maleOperativeMappings;
	cultureGroupToPortraitsMap femaleOperativeMappings;
	cultureGroupToGraphicalCultureMap graphicalCultureMap;
	cultureGroupToGraphicalCultureMap graphicalCulture2dMap;

	std::map<std::pair<std::string, std::string>, int> leaderPortraitIndexes;
	std::map<std::pair<std::string, std::string>, int> ministerPortraitIndexes;
};

} // namespace Mappers



#endif // GRAPHICS_MAPPER_H