#ifndef VIC2_ARMY_H_
#define VIC2_ARMY_H_



#include "Parser.h"
#include "Unit.h"
#include <optional>
#include <string>
#include <vector>



namespace Vic2
{

class Army: commonItems::parser // also Navy
{
  public:
	class Factory;

	[[nodiscard]] const auto& getName() const { return name; }
	[[nodiscard]] const auto& getLocation() const { return location; }
	[[nodiscard]] const auto& getUnits() const { return units; }
	[[nodiscard]] const auto& getTransportedArmies() const { return transportedArmies; }

  private:
	std::string name;
	std::optional<int> location;
	std::vector<Unit> units;
	std::vector<Army> transportedArmies;
};

} // namespace Vic2



#endif // VIC2_ARMY_H_
