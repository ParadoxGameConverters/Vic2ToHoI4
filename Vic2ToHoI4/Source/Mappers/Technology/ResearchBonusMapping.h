#ifndef RESEARCH_BONUS_MAPPING_H
#define RESEARCH_BONUS_MAPPING_H



#include <map>
#include <set>
#include <string>



namespace Mappers
{

class ResearchBonusMapping
{
  public:
	class Factory;

	[[nodiscard]] auto& getVic2Requirements() const { return vic2Requirements; }
	[[nodiscard]] auto& getResearchBonuses() const { return researchBonuses; }

  private:
	std::set<std::string> vic2Requirements;
	std::map<std::string, int> researchBonuses;
};

} // namespace Mappers



#endif // RESEARCH_BONUS_MAPPING_H