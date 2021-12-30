#ifndef HOI4WORLD_CHARACTERS_COMMANDER_DATA_H
#define HOI4WORLD_CHARACTERS_COMMANDER_DATA_H



#include <string>
#include <vector>



namespace HoI4
{

enum class CommanderLevel
{
	CorpsCommander,
	FieldMarshal
};


class CommanderData
{
  public:
	explicit CommanderData(CommanderLevel level,
		 std::vector<std::string> traits,
		 int skill,
		 int attack_skill,
		 int defense_skill,
		 int planning_skill,
		 int logistics_skill):
		 level_(level),
		 traits_(std::move(traits)), skill_(skill), attack_skill_(attack_skill), defense_skill_(defense_skill),
		 planning_skill_(planning_skill), logistics_skill_(logistics_skill)
	{
	}

	[[nodiscard]] const auto& getLevel() const { return level_; }
	[[nodiscard]] const auto& getTraits() const { return traits_; }
	[[nodiscard]] const auto& getSkill() const { return skill_; }
	[[nodiscard]] const auto& getAttackSkill() const { return attack_skill_; }
	[[nodiscard]] const auto& getDefenseSkill() const { return defense_skill_; }
	[[nodiscard]] const auto& getPlanningSkill() const { return planning_skill_; }
	[[nodiscard]] const auto& getLogisticsSkill() const { return logistics_skill_; }

	[[nodiscard]] bool operator==(const CommanderData&) const = default;

  private:
	CommanderLevel level_ = CommanderLevel::CorpsCommander;
	std::vector<std::string> traits_;
	int skill_ = 1;
	int attack_skill_ = 1;
	int defense_skill_ = 1;
	int planning_skill_ = 1;
	int logistics_skill_ = 1;
};

} // namespace HoI4



#endif // HOI4WORLD_CHARACTERS_COMMANDER_DATA_H