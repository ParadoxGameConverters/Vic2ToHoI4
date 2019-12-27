#include "MtgNavy.h"



float HoI4::MtgNavy::getStrength() const
{
	float strength = 0.0f;

	for (auto ship: ships)
	{
		strength += ship.getStrength();
	}

	return strength;
}