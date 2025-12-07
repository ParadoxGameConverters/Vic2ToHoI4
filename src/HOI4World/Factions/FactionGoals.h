#ifndef FACTION_GOALS_H
#define FACTION_GOALS_H



#include "external/common_items/Parser.h"
#include "src/HOI4World/Factions/FactionGoal.h"



namespace HoI4
{

class FactionGoals: commonItems::parser
{
  public:
	FactionGoals();
	FactionGoals(std::istream& theStream);

	void updateFactionGoals(const std::set<std::string>& majorIdeologies);

	void updateDefeatOfAntiIdeologyGoal(const std::string& ideology, const std::set<std::string>& majorIdeologies);
	void updateGuardiansOfPeaceGoal(const std::set<std::string>& majorIdeologies);

	[[nodiscard]] const auto& getImportedGoals() const { return importedGoals; }

  private:
	std::map<std::string, std::vector<FactionGoal>> importedGoals;
	std::vector<FactionGoal> ideologicalGoals;
};


} // namespace HoI4



#endif // FACTION_GOALS_H