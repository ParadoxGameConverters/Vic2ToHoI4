#include "MtgShip.h"



float HoI4::MtgShip::getStrength() const
{
	if (type == "carrier")
	{
		return 0.5f;
	}
	if (type == "battleship")
	{
		return 1.0f;
	}
	if (type == "battle_cruiser")
	{
		return 0.8f;
	}
	if (type == "heavy_cruiser")
	{
		return 0.5f;
	}

	return 0.0f;
}