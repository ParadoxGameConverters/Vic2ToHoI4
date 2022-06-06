#ifndef RESEARCH_BONUS_MAPPER_FACTORY_H
#define RESEARCH_BONUS_MAPPER_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "ResearchBonusMapper.h"
#include "ResearchBonusMappingFactory.h"
#include <memory>



namespace Mappers
{

class ResearchBonusMapper::Factory: commonItems::parser
{
  public:
	Factory();

	std::unique_ptr<ResearchBonusMapper> importResearchBonusMapper();

  private:
	ResearchBonusMapping::Factory researchBonusMappingFactory;

	std::unique_ptr<ResearchBonusMapper> researchBonusMapper;
};

} // namespace Mappers



#endif // RESEARCH_BONUS_MAPPER_FACTORY_H