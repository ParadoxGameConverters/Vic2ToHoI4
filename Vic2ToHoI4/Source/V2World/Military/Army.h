#ifndef VIC2_ARMY_H_
#define VIC2_ARMY_H_



#include "Parser.h"
#include "Unit.h"
#include "UnitFactory.h"
#include <string>
#include <vector>



namespace Vic2
{

class Army: commonItems::parser // also Navy
{
  public:
	explicit Army(const std::string& type, std::istream& theStream, Unit::Factory& unitFactory);

	std::string getName() const { return name; }
	int getLocation() const { return location; }
	[[nodiscard]] const auto& getUnits() const { return units; }
	std::vector<Army> getTransportedArmies() const { return transportedArmies; }

  private:
	std::string name = "";
	int location = -1;
	std::vector<Unit> units;
	std::vector<Army> transportedArmies;
};

} // namespace Vic2



#endif // VIC2_ARMY_H_
