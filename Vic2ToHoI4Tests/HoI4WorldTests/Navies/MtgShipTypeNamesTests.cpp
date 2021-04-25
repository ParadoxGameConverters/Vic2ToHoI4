#include "HOI4World/Navies/MtgShipTypeNames.h"
#include "gtest/gtest.h"



TEST(HoI4World_Navies_MtgShipTypeNamesTests, OrderSetByType)
{
	const HoI4::MtgShipTypeNames MtgShipTypeNames("a", "", std::set<std::string>{}, "", {});
	const HoI4::MtgShipTypeNames MtgShipTypeNames2("b", "", std::set<std::string>{}, "", {});

	ASSERT_LT(MtgShipTypeNames, MtgShipTypeNames2);
}