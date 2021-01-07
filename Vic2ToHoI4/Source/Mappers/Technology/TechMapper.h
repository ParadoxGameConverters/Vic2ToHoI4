#ifndef TECH_MAPPER
#define TECH_MAPPER


#include "Parser.h"
#include "ResearchBonusMapping.h"
#include "TechMapping.h"
#include <map>
#include <memory>
#include <string>
#include <vector>



namespace Mappers
{

class TechMapper
{
  public:
	class Factory;

	[[nodiscard]] auto getAllTechMappings() const { return techMappings; }

  private:
	std::vector<TechMapping> techMappings;
};

} // namespace Mappers



namespace mappers
{

class techMapper: commonItems::parser
{
  public:
	techMapper(const std::vector<Mappers::TechMapping>& _techMap,
		 const std::vector<Mappers::ResearchBonusMapping>& _researchBonusMap):
		 techMap(_techMap),
		 researchBonusMap(_researchBonusMap){};
	~techMapper() = default;

	auto getAllTechMappings() const { return techMap; }
	auto getAllResearchBonuses() const { return researchBonusMap; }

  private:
	techMapper(const techMapper&) = delete;
	techMapper(techMapper&&) = delete;
	techMapper& operator=(const techMapper&) = delete;
	techMapper& operator=(techMapper&&) = delete;

	std::vector<Mappers::TechMapping> techMap;
	std::vector<Mappers::ResearchBonusMapping> researchBonusMap;
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