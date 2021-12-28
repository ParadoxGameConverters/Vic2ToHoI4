#ifndef HOI4WORLD_CHARACTERS_ADMIRAL_DATA_H
#define HOI4WORLD_CHARACTERS_ADMIRAL_DATA_H



#include <string>
#include <vector>



namespace HoI4
{

class AdmiralData
{
  public:
	AdmiralData(std::vector<std::string> traits,
		 int skill,
		 int attack_skill,
		 int defense_skill,
		 int maneuvering_skill,
		 int coordination_skill):
		 traits_(std::move(traits)),
		 skill_(skill), attack_skill_(attack_skill), defense_skill_(defense_skill), maneuvering_skill_(maneuvering_skill),
		 coordination_skill_(coordination_skill)
	{
	}

	[[nodiscard]] const auto& getTraits() const { return traits_; }
	[[nodiscard]] const auto& getSkill() const { return skill_; }
	[[nodiscard]] const auto& getAttackSkill() const { return attack_skill_; }
	[[nodiscard]] const auto& getDefenseSkill() const { return defense_skill_; }
	[[nodiscard]] const auto& getManeuveringSkill() const { return maneuvering_skill_; }
	[[nodiscard]] const auto& getCoordinationSkill() const { return coordination_skill_; }

  private:
	std::vector<std::string> traits_;
	int skill_ = 1;
	int attack_skill_ = 1;
	int defense_skill_ = 1;
	int maneuvering_skill_ = 1;
	int coordination_skill_ = 1;
};

} // namespace HoI4



#endif // HOI4WORLD_CHARACTERS_ADMIRAL_DATA_H