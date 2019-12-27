#include "MtgNavy.h"



float HoI4::MtgNavy::getStrength() const
{
	auto strength = 0.0f;

	for (const auto& ship: ships)
	{
		strength += ship.getStrength();
	}

	return strength;
}