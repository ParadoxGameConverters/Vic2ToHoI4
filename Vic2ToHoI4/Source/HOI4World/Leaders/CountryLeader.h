#ifndef COUNTRY_LEADER_H
#define COUNTRY_LEADER_H



#include <string>
#include <vector>



namespace HoI4
{

class CountryLeader
{
  public:
	class Factory;

	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getDescription() const { return description; }
	[[nodiscard]] const auto& getPicture() const { return picture; }
	[[nodiscard]] const auto& getIdeology() const { return ideology; }
	[[nodiscard]] const auto& getTraits() const { return traits; }

  private:
	std::string name = "Nomen Nescio"; // Nescio Nomen (or N.N.) literally means "I don't know the name" and is sometimes
												  // used when the name of a person is unknown
	std::string description = "POLITICS_NOMEN_NESCIO_DESC";
	std::string picture = "gfx/leaders/ENG/portrait_eng_fallen_government.dds";
	std::string ideology = "conservatism_neutral";
	std::vector<std::string> traits;
};

} // namespace HoI4



#endif // COUNTRY_LEADER_H