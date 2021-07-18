#ifndef UNIT_H
#define UNIT_H



#include <string>



namespace Vic2
{

class Unit
{
  public:
	class Factory;

	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getType() const { return type; }
	[[nodiscard]] const auto& getStrength() const { return strength; }
	[[nodiscard]] const auto& getOrganization() const { return organization; }
	[[nodiscard]] const auto& getExperience() const { return experience; }

	bool operator==(const Unit& rhs) const = default;

  private:
	std::string name;
	std::string type;
	double strength = 0.0;
	double organization = 0.0;
	double experience = 0.0;
};

} // namespace Vic2



#endif // UNIT_H