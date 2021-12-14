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

	[[nodiscard]] bool isLeader() { return leader_ideology_.has_value(); }
	[[nodiscard]] const auto& getLeaderIdeology() const { return *leader_ideology_; }
	[[nodiscard]] const auto& getLeaderTraits() const { return leader_traits_; }

  private:
	std::string id_ = "Nomen_Nescio";
	std::string name_ = "Nomen Nescio"; // Nescio Nomen (or N.N.) literally means "I don't know the name" and is
													// sometimes used when the name of a person is unknown
	std::vector<Portrait> portraits_;

	std::optional<std::string> leader_ideology_;
	std::vector<std::string> leader_traits_;
};

} // namespace HoI4



#endif // HOI4_CHARACTERS_CHARACTER_H