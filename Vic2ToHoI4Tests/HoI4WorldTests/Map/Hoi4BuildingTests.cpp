#include "HOI4World/Map/Hoi4Building.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Map_Building, ConnectingSeaProvinceDefaultsToZero)
{
	const HoI4::BuildingPosition position;
	const HoI4::Building building(1, "type", position, std::nullopt);

	std::stringstream output;
	output << building;

	std::stringstream expectedOutput;
	expectedOutput << "1;type;0.00;0.00;0.00;0.00;0\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Map_Building, ConnectingSeaProvinceCanBeSet)
{
	const HoI4::BuildingPosition position;
	const HoI4::Building building(1, "type", position, 2);

	std::stringstream output;
	output << building;

	std::stringstream expectedOutput;
	expectedOutput << "1;type;0.00;0.00;0.00;0.00;2\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}