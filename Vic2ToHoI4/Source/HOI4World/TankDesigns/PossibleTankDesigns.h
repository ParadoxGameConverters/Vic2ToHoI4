#ifndef POSSIBLE_TANK_DESIGNS_H
#define POSSIBLE_TANK_DESIGNS_H



#include "Parser.h"
#include "TankDesign.h"
#include <vector>



namespace HoI4
{

class PossibleTankDesigns: commonItems::parser
{
  public:
	explicit PossibleTankDesigns(std::istream& theStream);

	[[nodiscard]] auto getPossibleTankDesigns() const { return tankDesigns; }

  private:
	std::vector<TankDesign> tankDesigns;
};

} // namespace HoI4



#endif // POSSIBLE_TANK_DESIGNS_H