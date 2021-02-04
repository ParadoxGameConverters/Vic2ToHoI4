#ifndef GRAPHICS_MAPPER_H_
#define GRAPHICS_MAPPER_H_



#include "Parser.h"
#include <map>
#include <optional>
#include <random>
#include <string>
#include <vector>



typedef std::map<std::string, std::vector<std::string>> cultureGroupToPortraitsMap;
typedef std::map<std::string, cultureGroupToPortraitsMap> ideologyToPortraitsMap;
typedef std::map<std::string, std::string> cultureGroupToGraphicalCultureMap;



class graphicsMapper: commonItems::parser
{
  public:
	graphicsMapper() noexcept {};
	void init();
	~graphicsMapper() = default;

	class Builder;

	const std::vector<std::string>& getArmyPortraits(const std::string& cultureGroup);
	const std::vector<std::string>& getNavyPortraits(const std::string& cultureGroup);
	std::string getLeaderPortrait(const std::string& cultureGroup, const std::string& ideology);
	std::string getIdeologyMinisterPortrait(const std::string& cultureGroup, const std::string& ideology);
	std::string getGeneralPortrait(const std::string& cultureGroup) const;
	std::optional<std::string> getGraphicalCulture(const std::string& cultureGroup) const;
	std::optional<std::string> get2dGraphicalCulture(const std::string& cultureGroup) const;

  private:
	graphicsMapper(const graphicsMapper&) = delete;
	graphicsMapper& operator=(const graphicsMapper&) = delete;

	void loadLeaderPortraitMappings(const std::string& cultureGroup,
		 const std::map<std::string, std::vector<std::string>>& portraitMappings);
	void loadIdeologyMinisterPortraitMappings(const std::string& cultureGroup,
		 const std::map<std::string, std::vector<std::string>>& portraitMappings);

	std::optional<std::vector<std::string>> getLeaderPortraits(const std::string& cultureGroup,
		 const std::string& ideology) const;
	std::optional<std::vector<std::string>> getIdeologyMinisterPortraits(const std::string& cultureGroup,
		 const std::string& ideology) const;

	cultureGroupToPortraitsMap armyPortraitMappings;
	cultureGroupToPortraitsMap navyPortraitMappings;
	ideologyToPortraitsMap leaderPortraitMappings;
	ideologyToPortraitsMap ideologyMinisterMappings;
	cultureGroupToGraphicalCultureMap graphicalCultureMap;
	cultureGroupToGraphicalCultureMap graphicalCulture2dMap;

	std::mt19937 rng;
};



#endif // GRAPHICS_MAPPER_H_