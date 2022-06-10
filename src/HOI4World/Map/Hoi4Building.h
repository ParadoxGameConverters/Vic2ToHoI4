#ifndef HOI4_BUILDING_H
#define HOI4_BUILDING_H



#include "src/HOI4World/Map/BuildingPosition.h"
#include <optional>
#include <string>



namespace HoI4
{

class Building
{
  public:
	explicit Building(int _stateID,
		 const std::string& _type,
		 const BuildingPosition& _position,
		 std::optional<int> _connectingSeaProvince);

	friend std::ostream& operator<<(std::ostream& out, const Building& building);

  private:
	int stateID = 0;
	std::string type;
	BuildingPosition position;
	int connectingSeaProvince = 0;
};

} // namespace HoI4



#endif // HOI4_BUILDING_H
