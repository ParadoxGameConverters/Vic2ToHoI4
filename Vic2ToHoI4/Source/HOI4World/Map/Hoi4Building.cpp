#include "Hoi4Building.h"



HoI4::Building::Building(const int _stateID,
	 const std::string& _type,
	 const BuildingPosition& _position,
	 std::optional<int> _connectingSeaProvince):
	 stateID(_stateID),
	 type(_type), position(_position)
{
	if (_connectingSeaProvince)
	{
		connectingSeaProvince = *_connectingSeaProvince;
	}
}