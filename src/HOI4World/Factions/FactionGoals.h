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

	std::shared_ptr<FactionGoal> getGoal(const std::string& goalId);

	[[nodiscard]] const auto& getImportedGoals() const { return importedGoals; }
	[[nodiscard]] const auto& getIdeologicalGoals() const { return ideologicalGoals; }
	[[nodiscard]] const auto& getVariables() const { return variables; }

  private:
	std::map<std::string, std::vector<std::shared_ptr<FactionGoal>>> importedGoals;
	std::vector<FactionGoal> ideologicalGoals;
	std::map<std::string, double> variables;
};


} // namespace HoI4



#endif // FACTION_GOALS_H