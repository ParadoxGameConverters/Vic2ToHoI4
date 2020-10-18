#include "HOI4World/Navies/LegacyShipTypeNames.h"
#include "gtest/gtest.h"



TEST(HoI4World_Navies_LegacyShipTypeNamesTests, OrderSetByType)
{
	const HoI4::LegacyShipTypeNames legacyShipTypeNames("a", "", std::vector<std::string>{});
	const HoI4::LegacyShipTypeNames legacyShipTypeNames2("b", "", std::vector<std::string>{});

	ASSERT_LT(legacyShipTypeNames, legacyShipTypeNames2);
}