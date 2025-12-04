#ifndef FACTION_GOALS_H
#define FACTION_GOALS_H



#include "external/common_items/Parser.h"
#include "src/HOI4World/Factions/FactionGoal.h"



namespace HoI4
{

class FactionGoals: commonItems::parser
{
  public:
	FactionGoals() = default;
	FactionGoals(const std::set<std::string>& majorIdeologies);

	void importFactionGoals(const std::filesystem::path& fileName);

	[[nodiscard]] const auto& getImportedGoals() const { return importedGoals; }

  private:
	std::map<std::string, std::shared_ptr<FactionGoal>> importedGoals;
};


} // namespace HoI4



#endif // FACTION_GOALS_H