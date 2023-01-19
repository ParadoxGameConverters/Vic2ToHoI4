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
	explicit PossiblePlaneDesigns(std::istream& the_stream);

	[[nodiscard]] auto GetPossiblePlaneDesigns() const { return plane_designs_; }

  private:
	std::vector<PlaneDesign> plane_designs_;
};

} // namespace HoI4



#endif // POSSIBLE_PLANE_DESIGNS_H