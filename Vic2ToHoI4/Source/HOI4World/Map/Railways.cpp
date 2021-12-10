#include "Railways.h"



using HoI4::Railway;



std::vector<Railway> HoI4::determineRailways()
{
	std::vector<Railway> railways;

	Railway railway(1, {1, 2, 3, 4, 5});

	railways.push_back(railway);

	return railways;
}