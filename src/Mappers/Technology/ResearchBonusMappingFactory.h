#ifndef RESEARCH_BONUS_MAPPING_FACTORY_H
#define RESEARCH_BONUS_MAPPING_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/Mappers/Technology/ResearchBonusMapping.h"
#include <memory>



namespace Mappers
{

class ResearchBonusMapping::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<ResearchBonusMapping> importResearchBonusMapping(std::istream& theStream);

  private:
	std::unique_ptr<ResearchBonusMapping> researchBonusMapping;
};

} // namespace Mappers



#endif // RESEARCH_BONUS_MAPPING_FACTORY_H