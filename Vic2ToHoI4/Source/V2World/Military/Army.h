#ifndef VIC2_ARMY_H_
#define VIC2_ARMY_H_



#include "Unit.h"
#include <optional>
#include <string>
#include <vector>



namespace Vic2
{

class Army // also Navy
{
  public:
	class Factory;
	class Builder;

	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getOwner() const { return owner; }
	[[nodiscard]] const auto& getLocation() const { return location; }
	[[nodiscard]] const auto& getUnits() const { return units; }
	[[nodiscard]] const auto& getTransportedArmies() const { return transportedArmies; }

	void setLocation(std::optional<int> newLocation) { location = newLocation; }

	bool operator<=>(const Army&) const = default;

  private:
	std::string name;
	std::string owner;
	std::optional<int> location;
	std::vector<Unit> units;
	std::vector<Army> transportedArmies;
};

} // namespace Vic2



#endif // VIC2_ARMY_H_
