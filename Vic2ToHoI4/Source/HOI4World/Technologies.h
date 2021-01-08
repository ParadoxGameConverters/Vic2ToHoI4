#ifndef TECHNOLGIES_H_
#define TECHNOLGIES_H_



#include "Mappers/Technology/ResearchBonusMapper.h"
#include "Mappers/Technology/TechMapper.h"
#include <map>
#include <set>
#include <string>



namespace HoI4
{

class technologies
{
  public:
	technologies() = default;
	~technologies() = default;

	class Builder;

	technologies(const Mappers::TechMapper& techMapper,
		 const Mappers::ResearchBonusMapper& researchBonusMapper,
		 const std::set<std::string>& oldTechnologiesAndInventions);

	void setResearchBonus(const std::string& tech, int bonus);

	[[nodiscard]] int getTechnologyCount() const;
	[[nodiscard]] bool hasTechnology(const std::string& technology) const;

	[[nodiscard]] const auto& getTechnologies() const { return technologiesByLimits; }
	[[nodiscard]] const auto& getResearchBonuses() const { return researchBonuses; }

  private:
	// technologies are sorted by limits that can be applied to them
	std::map<std::string, std::set<std::string>> technologiesByLimits;

	std::map<std::string, int> researchBonuses;
};

} // namespace HoI4


#endif // TECHNOLGIES_H_