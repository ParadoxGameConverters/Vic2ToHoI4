#include "HOI4World/ShipTypes/PossibleShipVariants.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_ShipTypes_possibleShipVariantsTests, mtgVariantsDefautlToEmpty)
{
	std::stringstream input;
	const HoI4::PossibleShipVariants theShipVariants(input);

	ASSERT_TRUE(theShipVariants.getPossibleMtgVariants().empty());
}


TEST(HoI4World_ShipTypes_possibleShipVariantsTests, mtgVariantsCanBeLoaded)
{
	std::stringstream input;
	input << "mtg_ship_type = {\n";
	input << "\tname = \"Early submarine\"\n";
	input << "\ttype = ship_hull_submarine_1\n";
	input << "\tname_group = SS_HISTORICAL\n";
	input << "\tparent_version = 0\n";
	input << "\tmodules = {\n";
	input << "\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	input << "\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	input << "\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	input << "\t}\n";
	input << "\tobsolete = yes\n";
	input << "}\n";
	input << "mtg_ship_type = {\n";
	input << "\tname = \"Early submarine2\"\n";
	input << "\ttype = ship_hull_submarine_1\n";
	input << "\tname_group = SS_HISTORICAL\n";
	input << "\tparent_version = 0\n";
	input << "\tmodules = {\n";
	input << "\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	input << "\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	input << "\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	input << "\t}\n";
	input << "\tobsolete = yes\n";
	input << "}\n";
	const HoI4::PossibleShipVariants theShipVariants(input);

	ASSERT_EQ(theShipVariants.getPossibleMtgVariants().size(), 2);
}


TEST(HoI4World_ShipTypes_possibleShipVariantsTests, legacyVariantsDefautlToEmpty)
{
	std::stringstream input;
	const HoI4::PossibleShipVariants theShipVariants(input);

	ASSERT_TRUE(theShipVariants.getPossibleLegacyVariants().empty());
}


TEST(HoI4World_ShipTypes_possibleShipVariantsTests, legacyVariantsCanBeLoaded)
{
	std::stringstream input;
	input << "legacy_ship_type = {\n";
	input << "}\n";
	input << "legacy_ship_type = {\n";
	input << "}\n";
	const HoI4::PossibleShipVariants theShipVariants(input);

	ASSERT_EQ(theShipVariants.getPossibleLegacyVariants().size(), 2);
}