#ifndef COUNTRY_MAPPER_FACTORY_H
#define COUNTRY_MAPPER_FACTORY_H



#include "CountryMapping.h"
#include "CountryMappingRuleFactory.h"
#include "Parser.h"
#include "V2World/World/World.h"
#include <memory>



namespace Mappers
{

class CountryMapper::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<CountryMapper> importCountryMapper(const Vic2::World& srcWorld, bool debug);

  private:
	void readRules();
	void createMappings(const Vic2::World& srcWorld, bool debug);
	void resetMappingData();
	void makeOneMapping(const std::string& Vic2Tag, bool debug);
	[[nodiscard]] bool tagIsAlreadyAssigned(const std::string& HoI4Tag) const;
	[[nodiscard]] std::string generateNewHoI4Tag();
	void mapToNewTag(const std::string& Vic2Tag, const std::string& HoI4Tag, bool debug);

	CountryMappingRuleFactory countryMappingRuleFactory;
	std::unique_ptr<CountryMapper> countryMapper;
	char generatedHoI4TagPrefix = 'X';
	int generatedHoI4TagSuffix = 0;
};

} // namespace Mappers



#endif // COUNTRY_MAPPER_FACTORY_H