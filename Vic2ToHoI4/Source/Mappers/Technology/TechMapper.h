#ifndef TECH_MAPPER
#define TECH_MAPPER


#include "Parser.h"
#include <map>
#include <memory>
#include <set>
#include <string>



namespace mappers
{

class techMapper: commonItems::parser
{
  public:
	techMapper(const std::map<std::string, std::set<std::string>>& _techMap,
		 const std::map<std::string, std::set<std::string>>& _nonMtgNavalTechMap,
		 const std::map<std::string, std::set<std::string>>& _mtgNavalTechMap,
		 const std::map<std::string, std::map<std::string, float>>& _researchBonusMap):
		 techMap(_techMap),
		 researchBonusMap(_researchBonusMap), nonMtgNavalTechMap(_nonMtgNavalTechMap),
		 mtgNavalTechMap(_mtgNavalTechMap){};
	~techMapper() = default;

	auto getAllTechMappings() const { return techMap; }
	auto getAllNonMtgNavalTechMappings() const { return nonMtgNavalTechMap; }
	auto getAllMtgNavalTechMappings() const { return mtgNavalTechMap; }
	auto getAllResearchBonuses() const { return researchBonusMap; }

  private:
	techMapper(const techMapper&) = delete;
	techMapper(techMapper&&) = delete;
	techMapper& operator=(const techMapper&) = delete;
	techMapper& operator=(techMapper&&) = delete;

	std::map<std::string, std::set<std::string>> techMap;
	std::map<std::string, std::set<std::string>> nonMtgNavalTechMap;
	std::map<std::string, std::set<std::string>> mtgNavalTechMap;
	std::map<std::string, std::map<std::string, float>> researchBonusMap;
};


class techMapperFile: commonItems::parser
{
  public:
	techMapperFile();
	~techMapperFile() = default;

	std::unique_ptr<techMapper> takeTechMapper() { return std::move(theTechMapper); }

  private:
	techMapperFile(const techMapperFile&) = delete;
	techMapperFile(techMapperFile&&) = delete;
	techMapperFile& operator=(const techMapperFile&) = delete;
	techMapperFile& operator=(techMapperFile&&) = delete;

	std::unique_ptr<techMapper> theTechMapper;
};

} // namespace mappers



#endif // TECH_MAPPER