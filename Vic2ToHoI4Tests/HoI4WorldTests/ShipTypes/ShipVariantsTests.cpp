#include "../../Mocks/TechnologiesMock.h"
#include "../../Vic2ToHoI4/Source/HOI4World/ShipTypes/ShipVariant.h"
#include "../../Vic2ToHoI4/Source/HOI4World/ShipTypes/ShipVariants.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_ShipTypes_shipVariantsTests, VariantsDefaultsToEmpty)
{
	std::vector<HoI4::shipVariant> possibleVariants;
	mockTechnologies ownedTechs;

	HoI4::shipVariants theVariants(possibleVariants, ownedTechs, std::string(""));

	std::stringstream output;
	output << theVariants;

	std::stringstream expectedOutput;
	expectedOutput << "### VARIANTS ###\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { has_dlc = \"Man the Guns\" }\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_shipVariantsTests, CanReceiveVariant)
{
	std::stringstream input;
	input << " = {\n";
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
	HoI4::shipVariant theShipVariant(input);
	std::vector<HoI4::shipVariant> possibleVariants;
	possibleVariants.push_back(theShipVariant);

	mockTechnologies ownedTechs;

	HoI4::shipVariants theVariants(possibleVariants, ownedTechs, "TAG");

	std::stringstream output;
	output << theVariants;

	std::stringstream expectedOutput;
	expectedOutput << "### VARIANTS ###\n";
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


TEST(HoI4World_ShipTypes_shipVariantsTests, HeldVaraintIsIdentified)
{
	std::stringstream input;
	input << " = {\n";
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
	const HoI4::shipVariant theShipVariant(input);
	std::vector<HoI4::shipVariant> possibleVariants;
	possibleVariants.push_back(theShipVariant);

	const mockTechnologies ownedTechs;

	const HoI4::shipVariants theVariants(possibleVariants, ownedTechs, "TAG");

	ASSERT_TRUE(theVariants.hasVariant("Early submarine"));
}


TEST(HoI4World_ShipTypes_shipVariantsTests, MissingVaraintIsNotIdentified)
{
	std::stringstream input;
	input << " = {\n";
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
	const HoI4::shipVariant theShipVariant(input);
	std::vector<HoI4::shipVariant> possibleVariants;
	possibleVariants.push_back(theShipVariant);

	const mockTechnologies ownedTechs;

	const HoI4::shipVariants theVariants(possibleVariants, ownedTechs, "TAG");

	ASSERT_FALSE(theVariants.hasVariant("1936 submarine"));
}


TEST(HoI4World_ShipTypes_shipVariantsTests, VariantsNeedRequiredTechs)
{
	std::vector<HoI4::shipVariant> possibleVariants;

	std::stringstream input;
	input << " = {\n";
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
	HoI4::shipVariant theShipVariant(input);
	possibleVariants.push_back(theShipVariant);

	std::stringstream input2;
	input2 << " = {\n";
	input2 << "\trequired_techs = {\n";
	input2 << "\t\ttech2\n";
	input2 << "\t}\n";
	input2 << "\tname = \"Early submarine2\"\n";
	input2 << "\ttype = ship_hull_submarine_1\n";
	input2 << "\tname_group = SS_HISTORICAL\n";
	input2 << "\t\tmodules = {\n";
	input2 << "\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	input2 << "\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	input2 << "\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	input2 << "\t}\n";
	input2 << "\tobsolete = yes\n";
	input2 << "}\n";
	HoI4::shipVariant theShipVariant2(input2);
	possibleVariants.push_back(theShipVariant2);

	mockTechnologies ownedTechs;
	EXPECT_CALL(ownedTechs, hasTechnology("tech1")).WillOnce(testing::Return(false));
	EXPECT_CALL(ownedTechs, hasTechnology("tech2")).WillOnce(testing::Return(true));

	HoI4::shipVariants theVariants(possibleVariants, ownedTechs, "TAG");

	std::stringstream output;
	output << theVariants;

	std::stringstream expectedOutput;
	expectedOutput << "### VARIANTS ###\n";
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


TEST(HoI4World_ShipTypes_shipVariantsTests, VariantsCanBeBlocked)
{
	std::vector<HoI4::shipVariant> possibleVariants;

	std::stringstream input;
	input << " = {\n";
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
	HoI4::shipVariant theShipVariant(input);
	possibleVariants.push_back(theShipVariant);

	std::stringstream input2;
	input2 << " = {\n";
	input2 << "\tblocking_techs = {\n";
	input2 << "\t\ttech2\n";
	input2 << "\t}\n";
	input2 << "\tname = \"Early submarine2\"\n";
	input2 << "\ttype = ship_hull_submarine_1\n";
	input2 << "\tname_group = SS_HISTORICAL\n";
	input2 << "\t\tmodules = {\n";
	input2 << "\t\tfixed_ship_torpedo_slot = ship_torpedo_sub_2\n";
	input2 << "\t\tfixed_ship_engine_slot = sub_ship_engine_2\n";
	input2 << "\t\trear_1_custom_slot = ship_torpedo_sub_2\n";
	input2 << "\t}\n";
	input2 << "\tobsolete = yes\n";
	input2 << "}\n";
	HoI4::shipVariant theShipVariant2(input2);
	possibleVariants.push_back(theShipVariant2);

	mockTechnologies ownedTechs;
	EXPECT_CALL(ownedTechs, hasTechnology("tech1")).WillOnce(testing::Return(false));
	EXPECT_CALL(ownedTechs, hasTechnology("tech2")).WillOnce(testing::Return(true));

	HoI4::shipVariants theVariants(possibleVariants, ownedTechs, "TAG");

	std::stringstream output;
	output << theVariants;

	std::stringstream expectedOutput;
	expectedOutput << "### VARIANTS ###\n";
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