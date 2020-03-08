#include "../../Mocks/TechnologiesMock.h"
#include "../../Vic2ToHoI4/Source/HOI4World/ShipTypes/ShipUpgrades.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_ShipTypes_ShipUpgradesTests, UpgradesDefaultToEmpty)
{
	std::stringstream input;
	HoI4::ShipUpgrades theUpgrades(input);

	ASSERT_TRUE(theUpgrades.takeUpgrades().empty());
}


TEST(HoI4World_ShipTypes_ShipUpgradesTests, UpgradesCanBeAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tupgrade_1 = 1\n";
	input << "\t\tupgrade_2 = 2\n";
	input << "\t}\n";
	HoI4::ShipUpgrades theUpgrades(input);

	const std::map<std::string, int> expectedUpgrades{{"upgrade_1", 1}, {"upgrade_2", 2}};
	ASSERT_EQ(expectedUpgrades, theUpgrades.takeUpgrades());
}