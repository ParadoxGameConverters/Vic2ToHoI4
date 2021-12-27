#ifndef HOI4_CHARACTERS_CHARACTER_H
#define HOI4_CHARACTERS_CHARACTER_H



#include "HOI4World/Characters/CountryLeaderData.h"
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

	[[nodiscard]] const auto& getCountryLeaderData() const { return country_leader_data_; }

	[[nodiscard]] bool isCommander() const { return is_commander_; }
	[[nodiscard]] const auto& getCommanderTraits() const { return commander_traits_; }
	[[nodiscard]] const auto& getCommanderSkill() const { return commander_skill_; }
	[[nodiscard]] const auto& getCommanderAttackSkill() const { return commander_attack_skill_; }
	[[nodiscard]] const auto& getCommanderDefenseSkill() const { return commander_defense_skill_; }
	[[nodiscard]] const auto& getCommanderPlanningSkill() const { return commander_planning_skill_; }
	[[nodiscard]] const auto& getCommanderLogisticsSkill() const { return commander_logistics_skill_; }

	[[nodiscard]] bool isAdmiral() const { return is_admiral_; }
	[[nodiscard]] const auto& getAdmiralTraits() const { return admiral_traits_; }
	[[nodiscard]] const auto& getAdmiralSkill() const { return admiral_skill_; }
	[[nodiscard]] const auto& getAdmiralAttackSkill() const { return admiral_attack_skill_; }
	[[nodiscard]] const auto& getAdmiralDefenseSkill() const { return admiral_defense_skill_; }
	[[nodiscard]] const auto& getAdmiralManeuveringSkill() const { return admiral_maneuvering_skill_; }
	[[nodiscard]] const auto& getAdmiralCoordinationSkill() const { return admiral_coordination_skill_; }

  private:
	std::string id_ = "nomen_nescio";
	std::string name_ = "Nomen Nescio"; // Nescio Nomen (or N.N.) literally means "I don't know the name" and is
													// sometimes used when the name of a person is unknown
	std::vector<Portrait> portraits_;

	std::optional<CountryLeaderData> country_leader_data_;

	bool is_commander_ = false;
	std::vector<std::string> commander_traits_;
	int commander_skill_ = 1;
	int commander_attack_skill_ = 1;
	int commander_defense_skill_ = 1;
	int commander_planning_skill_ = 1;
	int commander_logistics_skill_ = 1;

	bool is_admiral_ = false;
	std::vector<std::string> admiral_traits_;
	int admiral_skill_ = 1;
	int admiral_attack_skill_ = 1;
	int admiral_defense_skill_ = 1;
	int admiral_maneuvering_skill_ = 1;
	int admiral_coordination_skill_ = 1;
};

} // namespace HoI4



#endif // HOI4_CHARACTERS_CHARACTER_H