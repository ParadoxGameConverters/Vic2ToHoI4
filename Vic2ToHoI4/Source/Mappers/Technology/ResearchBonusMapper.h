#ifndef RESEARCH_BONUS_MAPPER_H
#define RESEARCH_BONUS_MAPPER_H



#include "ResearchBonusMapping.h"
#include <vector>



namespace Mappers
{

class ResearchBonusMapper
{
  public:
	class Factory;

	[[nodiscard]] auto getResearchBonusMappings() const { return researchBonusMappings; }

  private:
	std::vector<ResearchBonusMapping> researchBonusMappings;
};

} // namespace Mappers



#endif // RESEARCH_BONUS_MAPPER_H