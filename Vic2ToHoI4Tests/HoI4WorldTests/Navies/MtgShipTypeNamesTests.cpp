#include "HOI4World/Navies/MtgShipTypeNames.h"
#include "gtest/gtest.h"



TEST(HoI4World_Navies_MtgShipTypeNamesTests, OrderSetByType)
{
	const HoI4::MtgShipTypeNames MtgShipTypeNames("a", "", {}, "", {});
	const HoI4::MtgShipTypeNames MtgShipTypeNames2("b", "", {}, "", {});

	ASSERT_LT(MtgShipTypeNames, MtgShipTypeNames2);
}