#ifndef GRAPHICS_MAPPER_H
#define GRAPHICS_MAPPER_H



#include <map>
#include <optional>
#include <string>
#include <vector>



namespace Mappers
{

using culturesAndGroupsToPortraitsMap = std::map<std::string, std::vector<std::string>>;
using ideologyToPortraitsMap = std::map<std::string, culturesAndGroupsToPortraitsMap>;
using culturesAndGroupsToGraphicalCultureMap = std::map<std::string, std::string>;


class GraphicsMapper
{
  public:
	class Factory;

	[[nodiscard]] std::vector<std::string> getArmyPortraits(const std::string& culture,
		 const std::string& cultureGroup) const;
	[[nodiscard]] std::vector<std::string> getNavyPortraits(const std::string& culture,
		 const std::string& cultureGroup) const;
	[[nodiscard]] std::vector<std::string> getMaleMonarchPortraits(const std::string& culture,
		 const std::string& cultureGroup) const;
	[[nodiscard]] std::vector<std::string> getFemaleMonarchPortraits(const std::string& culture,
		 const std::string& cultureGroup) const;
	[[nodiscard]] std::string getLeaderPortrait(const std::string& culture,
		 const std::string& cultureGroup,
		 const std::string& ideology);
	[[nodiscard]] std::vector<std::string> getLeaderPortraits(const std::string& culture,
		 const std::string& cultureGroup,
		 const std::string& ideology) const;
	[[nodiscard]] std::vector<std::string> getFemalePortraits(const std::string& culture,
		 const std::string& cultureGroup,
		 const std::string& type) const;
	[[nodiscard]] std::string getIdeologyMinisterPortrait(const std::string& culture,
		 const std::string& cultureGroup,
		 const std::string& ideology);
	[[nodiscard]] std::vector<std::string> getMaleOperativePortraits(const std::string& culture,
		 const std::string& cultureGroup) const;
	[[nodiscard]] std::vector<std::string> getFemaleOperativePortraits(const std::string& culture,
		 const std::string& cultureGroup) const;
	[[nodiscard]] std::optional<std::string> getGraphicalCulture(const std::string& culture,
		 const std::string& cultureGroup) const;
	[[nodiscard]] std::optional<std::string> get2dGraphicalCulture(const std::string& culture,
		 const std::string& cultureGroup) const;

  private:
	[[nodiscard]] std::vector<std::string> getLeaderPortraits(const std::string& cultureOrGroup,
		 const std::string& ideology) const;
	[[nodiscard]] std::vector<std::string> getIdeologyMinisterPortraits(const std::string& cultureOrGroup,
		 const std::string& ideology) const;

	culturesAndGroupsToPortraitsMap armyPortraitMappings;
	culturesAndGroupsToPortraitsMap navyPortraitMappings;
	culturesAndGroupsToPortraitsMap maleMonarchMappings;
	culturesAndGroupsToPortraitsMap femaleMonarchMappings;
	ideologyToPortraitsMap leaderPortraitMappings;
	ideologyToPortraitsMap femalePortraitMappings;
	ideologyToPortraitsMap ideologyMinisterMappings;
	culturesAndGroupsToPortraitsMap maleOperativeMappings;
	culturesAndGroupsToPortraitsMap femaleOperativeMappings;
	culturesAndGroupsToGraphicalCultureMap graphicalCultureMap;
	culturesAndGroupsToGraphicalCultureMap graphicalCulture2dMap;

	std::map<std::pair<std::string, std::string>, int> leaderPortraitIndexes;
	std::map<std::pair<std::string, std::string>, int> ministerPortraitIndexes;
};

} // namespace Mappers



#endif // GRAPHICS_MAPPER_H