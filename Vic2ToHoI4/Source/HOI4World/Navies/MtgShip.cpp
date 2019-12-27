#include "MtgShip.h"



float HoI4::MtgShip::getStrength() const
{
	if (type == "carrier")
	{
		return 0.5;
	}
	else if (type == "battleship")
	{
		return 1.0;
	}
	else if (type == "battle_cruiser")
	{
		return 0.8;
	}
	else if (type == "heavy_cruiser")
	{
		return 0.5;
	}
	else
	{
		return 0.0;
	}
}