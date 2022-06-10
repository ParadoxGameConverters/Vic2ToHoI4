#ifndef COUNTRY_MAPPER_FACTORY_H
#define COUNTRY_MAPPER_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/Mappers/Country/CountryMapper.h"
#include "src/Mappers/Country/CountryMappingRuleFactory.h"
#include "src/V2World/World/World.h"
#include <memory>
#include <unordered_set>



namespace Mappers
{

class CountryMapper::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<CountryMapper> importCountryMapper(const Vic2::World& srcWorld, bool debug);
	[[nodiscard]] std::string generateNewHoI4Tag();

  private:
	void readRules();
	void createMappings(const Vic2::World& srcWorld, bool debug);
	void resetMappingData();
	void makeOneMapping(const std::string& Vic2Tag, bool debug);
	[[nodiscard]] bool tagIsAlreadyAssigned(const std::string& HoI4Tag) const;
	void mapToNewTag(const std::string& Vic2Tag, const std::string& HoI4Tag, bool debug);

	CountryMappingRuleFactory countryMappingRuleFactory;
	std::map<std::string, std::string> Vic2TagToHoI4TagsRules;
	std::unordered_set<std::string> assignedTags;
	char generatedHoI4TagPrefix = 'X';
	int generatedHoI4TagSuffix = 0;

	std::unique_ptr<CountryMapper> countryMapper;
};

} // namespace Mappers



#endif // COUNTRY_MAPPER_FACTORY_H