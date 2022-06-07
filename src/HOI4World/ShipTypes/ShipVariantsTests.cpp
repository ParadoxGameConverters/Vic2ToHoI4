#include "src/HOI4World/ShipTypes/MtgShipVariant.h"
#include "src/HOI4World/ShipTypes/ShipVariants.h"
#include "src/HOI4World/TechnologiesBuilder.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_ShipTypes_shipVariantsTests, VariantsDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::PossibleShipVariants possibleVariants(input);

	HoI4::ShipVariants theVariants(possibleVariants, *HoI4::technologies::Builder().Build(), std::string(""));

	std::stringstream output;
	output << theVariants;

	std::stringstream expectedOutput;
	expectedOutput << "### VARIANTS ###\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	expectedOutput << "}\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_shipVariantsTests, CanReceiveMtgVariant)
{
	std::stringstream input;
	input << "mtg_ship_type = {\n";
	input << "\tname = \"Early submarine\"\n";
	input << "\ttype = ship_hull_submarine_1\n";
	input << "\tname_group = SS_HISTORICAL\n";
	input << "\t\tmodules = {\n";
	input << "\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	input << "\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	input << "\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	input << "\t}\n";
	input << "\tobsolete = yes\n";
	input << "}\n";
	HoI4::PossibleShipVariants possibleVariants(input);

	HoI4::ShipVariants theVariants(possibleVariants, *HoI4::technologies::Builder().Build(), "TAG");

	std::stringstream output;
	output << theVariants;

	std::stringstream expectedOutput;
	expectedOutput << "### VARIANTS ###\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	expectedOutput << "}\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"Early submarine\"\n";
	expectedOutput << "\t\ttype = ship_hull_submarine_1\n";
	expectedOutput << "\t\tname_group = TAG_SS_HISTORICAL\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t\tmodules = {\n";
	expectedOutput << "\t\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	expectedOutput << "\t\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	expectedOutput << "\t\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\tobsolete = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_shipVariantsTests, HeldMtgVariantIsIdentified)
{
	std::stringstream input;
	input << "mtg_ship_type = {\n";
	input << "\tname = \"Early submarine\"\n";
	input << "\ttype = ship_hull_submarine_1\n";
	input << "\tname_group = SS_HISTORICAL\n";
	input << "\t\tmodules = {\n";
	input << "\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	input << "\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	input << "\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	input << "\t}\n";
	input << "\tobsolete = yes\n";
	input << "}\n";
	HoI4::PossibleShipVariants possibleVariants(input);

	const HoI4::ShipVariants theVariants(possibleVariants, *HoI4::technologies::Builder().Build(), "TAG");

	ASSERT_TRUE(theVariants.hasMtgVariant("Early submarine"));
}


TEST(HoI4World_ShipTypes_shipVariantsTests, MissingMtgVariantIsNotIdentified)
{
	std::stringstream input;
	input << "mtg_ship_type = {\n";
	input << "\tname = \"Early submarine\"\n";
	input << "\ttype = ship_hull_submarine_1\n";
	input << "\tname_group = SS_HISTORICAL\n";
	input << "\t\tmodules = {\n";
	input << "\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	input << "\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	input << "\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	input << "\t}\n";
	input << "\tobsolete = yes\n";
	input << "}\n";
	HoI4::PossibleShipVariants possibleVariants(input);

	const HoI4::ShipVariants theVariants(possibleVariants, *HoI4::technologies::Builder().Build(), "TAG");

	ASSERT_FALSE(theVariants.hasMtgVariant("1936 submarine"));
}


TEST(HoI4World_ShipTypes_shipVariantsTests, MtgVariantsNeedRequiredTechs)
{
	std::stringstream input;
	input << "mtg_ship_type = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\ttech1\n";
	input << "\t}\n";
	input << "\tname = \"Early submarine\"\n";
	input << "\ttype = ship_hull_submarine_1\n";
	input << "\tname_group = SS_HISTORICAL\n";
	input << "\t\tmodules = {\n";
	input << "\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	input << "\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	input << "\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	input << "\t}\n";
	input << "\tobsolete = yes\n";
	input << "}\n";
	input << "mtg_ship_type = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\ttech2\n";
	input << "\t}\n";
	input << "\tname = \"Early submarine2\"\n";
	input << "\ttype = ship_hull_submarine_1\n";
	input << "\tname_group = SS_HISTORICAL\n";
	input << "\t\tmodules = {\n";
	input << "\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	input << "\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	input << "\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	input << "\t}\n";
	input << "\tobsolete = yes\n";
	input << "}\n";
	HoI4::PossibleShipVariants possibleVariants(input);

	HoI4::ShipVariants theVariants(possibleVariants,
		 *HoI4::technologies::Builder().addTechnology("tech2").Build(),
		 "TAG");

	std::stringstream output;
	output << theVariants;

	std::stringstream expectedOutput;
	expectedOutput << "### VARIANTS ###\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	expectedOutput << "}\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"Early submarine2\"\n";
	expectedOutput << "\t\ttype = ship_hull_submarine_1\n";
	expectedOutput << "\t\tname_group = TAG_SS_HISTORICAL\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t\tmodules = {\n";
	expectedOutput << "\t\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	expectedOutput << "\t\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	expectedOutput << "\t\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\tobsolete = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_shipVariantsTests, MtgVariantsCanBeBlocked)
{
	std::stringstream input;
	input << "mtg_ship_type = {\n";
	input << "\tblocking_techs = {\n";
	input << "\t\ttech1\n";
	input << "\t}\n";
	input << "\tname = \"Early submarine\"\n";
	input << "\ttype = ship_hull_submarine_1\n";
	input << "\tname_group = SS_HISTORICAL\n";
	input << "\t\tmodules = {\n";
	input << "\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	input << "\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	input << "\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	input << "\t}\n";
	input << "\tobsolete = yes\n";
	input << "}\n";
	input << "mtg_ship_type = {\n";
	input << "\tblocking_techs = {\n";
	input << "\t\ttech2\n";
	input << "\t}\n";
	input << "\tname = \"Early submarine2\"\n";
	input << "\ttype = ship_hull_submarine_1\n";
	input << "\tname_group = SS_HISTORICAL\n";
	input << "\t\tmodules = {\n";
	input << "\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	input << "\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	input << "\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	input << "\t}\n";
	input << "\tobsolete = yes\n";
	input << "}\n";
	HoI4::PossibleShipVariants possibleVariants(input);

	HoI4::ShipVariants theVariants(possibleVariants,
		 *HoI4::technologies::Builder().addTechnology("tech2").Build(),
		 "TAG");

	std::stringstream output;
	output << theVariants;

	std::stringstream expectedOutput;
	expectedOutput << "### VARIANTS ###\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	expectedOutput << "}\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"Early submarine\"\n";
	expectedOutput << "\t\ttype = ship_hull_submarine_1\n";
	expectedOutput << "\t\tname_group = TAG_SS_HISTORICAL\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t\tmodules = {\n";
	expectedOutput << "\t\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	expectedOutput << "\t\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	expectedOutput << "\t\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\tobsolete = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_shipVariantsTests, CanReceiveLegacyVariant)
{
	std::stringstream input;
	input << "legacy_ship_type = {\n";
	input << "\tname = \"Early submarine\"\n";
	input << "\ttype = ship_hull_submarine_1\n";
	input << "\tupgrades = {\n";
	input << "\t\tship_reliability_upgrade = 1\n";
	input << "\t\tsub_engine_upgrade = 1\n";
	input << "\t\tsub_stealth_upgrade = 1\n";
	input << "\t\tsub_torpedo_upgrade = 1\n";
	input << "\t}\n";
	input << "\tobsolete = yes\n";
	input << "}\n";
	HoI4::PossibleShipVariants possibleVariants(input);

	HoI4::ShipVariants theVariants(possibleVariants, *HoI4::technologies::Builder().Build(), "TAG");

	std::stringstream output;
	output << theVariants;

	std::stringstream expectedOutput;
	expectedOutput << "### VARIANTS ###\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"Early submarine\"\n";
	expectedOutput << "\t\ttype = ship_hull_submarine_1\n";
	expectedOutput << "\t\tupgrades = {\n";
	expectedOutput << "\t\t\tship_reliability_upgrade = 1\n";
	expectedOutput << "\t\t\tsub_engine_upgrade = 1\n";
	expectedOutput << "\t\t\tsub_stealth_upgrade = 1\n";
	expectedOutput << "\t\t\tsub_torpedo_upgrade = 1\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\tobsolete = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "}\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_shipVariantsTests, HeldLegacyVariantIsIdentified)
{
	std::stringstream input;
	input << "legacy_ship_type = {\n";
	input << "\tname = \"Early submarine\"\n";
	input << "\ttype = ship_hull_submarine_1\n";
	input << "\tupgrades = {\n";
	input << "\t\tship_reliability_upgrade = 1\n";
	input << "\t\tsub_engine_upgrade = 1\n";
	input << "\t\tsub_stealth_upgrade = 1\n";
	input << "\t\tsub_torpedo_upgrade = 1\n";
	input << "\t}\n";
	input << "\tobsolete = yes\n";
	input << "}\n";
	HoI4::PossibleShipVariants possibleVariants(input);

	const HoI4::ShipVariants theVariants(possibleVariants, *HoI4::technologies::Builder().Build(), "TAG");

	ASSERT_TRUE(theVariants.hasLegacyVariant("Early submarine"));
}


TEST(HoI4World_ShipTypes_shipVariantsTests, MissingVariantIsNotIdentified)
{
	std::stringstream input;
	input << "legacy_ship_type = {\n";
	input << "\tname = \"Early submarine\"\n";
	input << "\ttype = ship_hull_submarine_1\n";
	input << "\tupgrades = {\n";
	input << "\t\tship_reliability_upgrade = 1\n";
	input << "\t\tsub_engine_upgrade = 1\n";
	input << "\t\tsub_stealth_upgrade = 1\n";
	input << "\t\tsub_torpedo_upgrade = 1\n";
	input << "\t}\n";
	input << "\tobsolete = yes\n";
	input << "}\n";
	HoI4::PossibleShipVariants possibleVariants(input);

	const HoI4::ShipVariants theVariants(possibleVariants, *HoI4::technologies::Builder().Build(), "TAG");

	ASSERT_FALSE(theVariants.hasLegacyVariant("1936 submarine"));
}


TEST(HoI4World_ShipTypes_shipVariantsTests, LegacyVariantsNeedRequiredTechs)
{
	std::stringstream input;
	input << "legacy_ship_type = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\ttech1\n";
	input << "\t}\n";
	input << "\tname = \"Early submarine\"\n";
	input << "\ttype = ship_hull_submarine_1\n";
	input << "\tupgrades = {\n";
	input << "\t\tship_reliability_upgrade = 1\n";
	input << "\t\tsub_engine_upgrade = 1\n";
	input << "\t\tsub_stealth_upgrade = 1\n";
	input << "\t\tsub_torpedo_upgrade = 1\n";
	input << "\t}\n";
	input << "\tobsolete = yes\n";
	input << "}\n";
	input << "legacy_ship_type = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\ttech2\n";
	input << "\t}\n";
	input << "\tname = \"Early submarine2\"\n";
	input << "\ttype = ship_hull_submarine_1\n";
	input << "\tupgrades = {\n";
	input << "\t\tship_reliability_upgrade = 2\n";
	input << "\t\tsub_engine_upgrade = 2\n";
	input << "\t\tsub_stealth_upgrade = 2\n";
	input << "\t\tsub_torpedo_upgrade = 2\n";
	input << "\t}\n";
	input << "\tobsolete = yes\n";
	input << "}\n";
	HoI4::PossibleShipVariants possibleVariants(input);


	HoI4::ShipVariants theVariants(possibleVariants,
		 *HoI4::technologies::Builder().addTechnology("tech2").Build(),
		 "TAG");

	std::stringstream output;
	output << theVariants;

	std::stringstream expectedOutput;
	expectedOutput << "### VARIANTS ###\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"Early submarine2\"\n";
	expectedOutput << "\t\ttype = ship_hull_submarine_1\n";
	expectedOutput << "\t\tupgrades = {\n";
	expectedOutput << "\t\t\tship_reliability_upgrade = 2\n";
	expectedOutput << "\t\t\tsub_engine_upgrade = 2\n";
	expectedOutput << "\t\t\tsub_stealth_upgrade = 2\n";
	expectedOutput << "\t\t\tsub_torpedo_upgrade = 2\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\tobsolete = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "}\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_shipVariantsTests, LegacyVariantsCanBeBlocked)
{
	std::stringstream input;
	input << "legacy_ship_type = {\n";
	input << "\tblocking_techs = {\n";
	input << "\t\ttech1\n";
	input << "\t}\n";
	input << "\tname = \"Early submarine\"\n";
	input << "\ttype = ship_hull_submarine_1\n";
	input << "\tupgrades = {\n";
	input << "\t\tship_reliability_upgrade = 1\n";
	input << "\t\tsub_engine_upgrade = 1\n";
	input << "\t\tsub_stealth_upgrade = 1\n";
	input << "\t\tsub_torpedo_upgrade = 1\n";
	input << "\t}\n";
	input << "\tobsolete = yes\n";
	input << "}\n";
	input << "legacy_ship_type = {\n";
	input << "\tblocking_techs = {\n";
	input << "\t\ttech2\n";
	input << "\t}\n";
	input << "\tname = \"Early submarine2\"\n";
	input << "\ttype = ship_hull_submarine_1\n";
	input << "\tupgrades = {\n";
	input << "\t\tship_reliability_upgrade = 2\n";
	input << "\t\tsub_engine_upgrade = 2\n";
	input << "\t\tsub_stealth_upgrade = 2\n";
	input << "\t\tsub_torpedo_upgrade = 12n";
	input << "\t}\n";
	input << "\tobsolete = yes\n";
	input << "}\n";
	HoI4::PossibleShipVariants possibleVariants(input);

	HoI4::ShipVariants theVariants(possibleVariants,
		 *HoI4::technologies::Builder().addTechnology("tech2").Build(),
		 "TAG");

	std::stringstream output;
	output << theVariants;

	std::stringstream expectedOutput;
	expectedOutput << "### VARIANTS ###\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { not = { has_dlc = \"Man the Guns\" } }\n";
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"Early submarine\"\n";
	expectedOutput << "\t\ttype = ship_hull_submarine_1\n";
	expectedOutput << "\t\tupgrades = {\n";
	expectedOutput << "\t\t\tship_reliability_upgrade = 1\n";
	expectedOutput << "\t\t\tsub_engine_upgrade = 1\n";
	expectedOutput << "\t\t\tsub_stealth_upgrade = 1\n";
	expectedOutput << "\t\t\tsub_torpedo_upgrade = 1\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\tobsolete = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";
	expectedOutput << "}\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}