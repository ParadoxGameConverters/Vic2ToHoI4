#ifndef POSSIBLE_PLANE_DESIGNS_H
#define POSSIBLE_PLANE_DESIGNS_H



#include "external/common_items/Parser.h"
#include "src/HOI4World/PlaneDesigns/PlaneDesign.h"
#include <vector>



namespace HoI4
{

class PossiblePlaneDesigns: commonItems::parser
{
  public:
	explicit PossiblePlaneDesigns(std::istream& theStream);

	[[nodiscard]] auto getPossiblePlaneDesigns() const { return tankDesigns; }

  private:
	std::vector<PlaneDesign> tankDesigns;
};

} // namespace HoI4



#endif // POSSIBLE_PLANE_DESIGNS_H