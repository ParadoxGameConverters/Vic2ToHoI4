#include "OutArmy.h"



std::ostream& HoI4::operator<<(std::ostream& output, const Army& theArmy)
{
	for (auto& division: theArmy.divisions)
	{
		output << division;
	}

	return output;
}