#include "TechMapper.h"
#include "ParserHelpers.h"
#include "ResearchBonusMapping.h"
#include "ResearchBonusMappingFactory.h"
#include "TechMappingFactory.h"



class researchBonusMap: commonItems::parser
{
  public:
	explicit researchBonusMap(std::istream& theStream);

	auto getMappings() const { return mappings; }

  private:
	std::vector<Mappers::ResearchBonusMapping> mappings;
};


researchBonusMap::researchBonusMap(std::istream& theStream)
{
	Mappers::ResearchBonusMapping::Factory researchBonusMappingFactory;

	registerKeyword("link", [this, &researchBonusMappingFactory](std::istream& theStream) {
		const auto theMapping = researchBonusMappingFactory.importResearchBonusMapping(theStream);
		mappings.push_back(*theMapping);
	});

	parseStream(theStream);
}


mappers::techMapperFile::techMapperFile()
{
	std::vector<Mappers::TechMapping> techMappings;
	std::vector<Mappers::ResearchBonusMapping> researchBonusMappings;

	registerKeyword("bonus_map", [this, &researchBonusMappings](std::istream& theStream) {
		researchBonusMap theBonusMap(theStream);
		researchBonusMappings = theBonusMap.getMappings();
	});

	parseFile("Configurables/tech_mapping.txt");
	theTechMapper = std::make_unique<techMapper>(techMappings, researchBonusMappings);
}