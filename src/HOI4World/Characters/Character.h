#ifndef HOI4_CHARACTERS_CHARACTER_H
#define HOI4_CHARACTERS_CHARACTER_H



#include "HOI4World/Characters/AdmiralData.h"
#include "HOI4World/Characters/AdvisorData.h"
#include "HOI4World/Characters/CommanderData.h"
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

	[[nodiscard]] const auto& getAdvisorData() const { return advisor_data; }
	[[nodiscard]] const auto& getCountryLeaderData() const { return country_leader_data_; }
	[[nodiscard]] const auto& getCommanderData() const { return commander_data_; }
	[[nodiscard]] const auto& getAdmiralData() const { return admiral_data_; }

	[[nodiscard]] bool operator==(const Character& rhs) const = default;

  private:
	std::string id_ = "nomen_nescio";
	std::string name_ = "Nomen Nescio"; // Nescio Nomen (or N.N.) literally means "I don't know the name" and is
													// sometimes used when the name of a person is unknown
	std::vector<Portrait> portraits_;

	std::optional<AdvisorData> advisor_data;
	std::optional<CountryLeaderData> country_leader_data_;
	std::optional<CommanderData> commander_data_;
	std::optional<AdmiralData> admiral_data_;
};

} // namespace HoI4



#endif // HOI4_CHARACTERS_CHARACTER_H