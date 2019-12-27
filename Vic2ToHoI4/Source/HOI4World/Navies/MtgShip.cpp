#include "MtgShip.h"



float HoI4::MtgShip::getStrength() const
{
	if (type == "carrier")
	{
		return 0.5;
	}
	if (type == "battleship")
	{
		return 1.0;
	}
	if (type == "battle_cruiser")
	{
		return 0.8;
	}
	if (type == "heavy_cruiser")
	{
		return 0.5;
	}

	return 0.0;
}