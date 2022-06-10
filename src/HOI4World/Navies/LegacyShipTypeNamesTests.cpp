#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Navies/LegacyShipTypeNames.h"



TEST(HoI4World_Navies_LegacyShipTypeNamesTests, OrderSetByType)
{
	const HoI4::LegacyShipTypeNames legacyShipTypeNames("a", "", {});
	const HoI4::LegacyShipTypeNames legacyShipTypeNames2("b", "", {});

	ASSERT_LT(legacyShipTypeNames, legacyShipTypeNames2);
}