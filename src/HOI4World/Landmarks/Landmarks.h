#ifndef HOI4_LANDMARKS_H
#define HOI4_LANDMARKS_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/Landmarks/Landmark.h"
#include <vector>



namespace HoI4
{

class Landmarks: commonItems::parser
{
  public:
	Landmarks(std::istream& theStream);

	[[nodiscard]] const auto& getBuildings() const { return buildings; }

  private:
	std::vector<Landmark> buildings;
};

} // namespace HoI4



#endif // HOI4_LANDMARKS_H