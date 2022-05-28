#include "ResearchBonusMapperFactory.h"



Mappers::ResearchBonusMapper::Factory::Factory()
{
	registerKeyword("link", [this](std::istream& theStream) {
		researchBonusMapper->researchBonusMappings.push_back(
			 *researchBonusMappingFactory.importResearchBonusMapping(theStream));
	});
}


std::unique_ptr<Mappers::ResearchBonusMapper> Mappers::ResearchBonusMapper::Factory::importResearchBonusMapper()
{
	researchBonusMapper = std::make_unique<ResearchBonusMapper>();
	parseFile("Configurables/research_bonus_mappings.txt");
	return std::move(researchBonusMapper);
}