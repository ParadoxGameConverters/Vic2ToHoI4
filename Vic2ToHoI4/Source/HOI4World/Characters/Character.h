#ifndef HOI4_CHARACTERS_CHARACTER_H
#define HOI4_CHARACTERS_CHARACTER_H



#include "HOI4World/Characters/Portrait.h"
#include <optional>
#include <string>
#include <vector>



namespace HoI4
{


class Character
{
  public:
	class Factory;

	[[nodiscard]] const auto& getId() const { return id_; }
	[[nodiscard]] const auto& getName() const { return name_; }
	[[nodiscard]] const auto& getPortraits() const { return portraits_; }

	[[nodiscard]] bool isLeader() const { return leader_ideology_.has_value(); }
	[[nodiscard]] const auto& getLeaderIdeology() const { return *leader_ideology_; }
	[[nodiscard]] const auto& getLeaderTraits() const { return leader_traits_; }

	[[nodiscard]] bool isCommander() const { return is_commander_; }
	[[nodiscard]] const auto& getCommanderTraits() const { return commander_traits_; }
	[[nodiscard]] const auto& getCommanderSkill() const { return commander_skill_; }
	[[nodiscard]] const auto& getCommanderAttackSkill() const { return commander_attack_skill_; }
	[[nodiscard]] const auto& getCommanderDefenseSkill() const { return commander_defense_skill_; }
	[[nodiscard]] const auto& getCommanderPlanningSkill() const { return commander_planning_skill_; }
	[[nodiscard]] const auto& getCommanderLogiticsSkill() const { return commander_logistics_skill_; }

  private:
	std::string id_ = "nomen_nescio";
	std::string name_ = "Nomen Nescio"; // Nescio Nomen (or N.N.) literally means "I don't know the name" and is
													// sometimes used when the name of a person is unknown
	std::vector<Portrait> portraits_;

	std::optional<std::string> leader_ideology_;
	std::vector<std::string> leader_traits_;

	bool is_commander_ = false;
	std::vector<std::string> commander_traits_;
	int commander_skill_ = 1;
	int commander_attack_skill_ = 1;
	int commander_defense_skill_ = 1;
	int commander_planning_skill_ = 1;
	int commander_logistics_skill_ = 1;
};

} // namespace HoI4



#endif // HOI4_CHARACTERS_CHARACTER_H