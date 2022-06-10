#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/ShipTypes/LegacyShipVariant.h"
#include "src/HOI4World/TechnologiesBuilder.h"
#include <sstream>



TEST(HoI4World_ShipTypes_LegacyShipVariantTests, DefaultsAsExpected)
{
	std::stringstream input;
	const HoI4::LegacyShipVariant theLegacyShipVariant(input);

	std::stringstream output;
	output << theLegacyShipVariant;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tupgrades = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_LegacyShipVariantTests, NameCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tname = \"Test Class\"\n";
	input << "}";
	const HoI4::LegacyShipVariant theLegacyShipVariant(input);

	ASSERT_EQ("Test Class", theLegacyShipVariant.getName());
}


TEST(HoI4World_ShipTypes_LegacyShipVariantTests, TypeCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ttype = type_1\n";
	input << "}";
	const HoI4::LegacyShipVariant theLegacyShipVariant(input);

	std::stringstream output;
	output << theLegacyShipVariant;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = type_1\n";
	expectedOutput << "\t\tupgrades = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_LegacyShipVariantTests, UpgradesCanBeAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tupgrades = {\n";
	input << "\t\tupgrade_1 = 1\n";
	input << "\t\tupgrade_2 = 2\n";
	input << "\t}\n";
	input << "}";
	const HoI4::LegacyShipVariant theLegacyShipVariant(input);

	std::stringstream output;
	output << theLegacyShipVariant;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tupgrades = {\n";
	expectedOutput << "\t\t\tupgrade_1 = 1\n";
	expectedOutput << "\t\t\tupgrade_2 = 2\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_LegacyShipVariantTests, CanBeSetObsolete)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tobsolete = yes\n";
	input << "}";
	HoI4::LegacyShipVariant theLegacyShipVariant(input);

	std::stringstream output;
	output << theLegacyShipVariant;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tupgrades = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\tobsolete = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_LegacyShipVariantTests, OnlySetObsoleteByYes)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tobsolete = no\n";
	input << "}";
	HoI4::LegacyShipVariant theLegacyShipVariant(input);

	std::stringstream output;
	output << theLegacyShipVariant;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tupgrades = {\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\n";

	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_LegacyShipVariantTests, NoRequiredTechsMeansVariantIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "}";
	const HoI4::LegacyShipVariant theLegacyShipVariant(input);

	ASSERT_TRUE(theLegacyShipVariant.isValidVariant(*HoI4::technologies::Builder().Build()));
}


TEST(HoI4World_ShipTypes_LegacyShipVariantTests, MissingRequiredTechMeansVariantIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::LegacyShipVariant theLegacyShipVariant(input);

	ASSERT_FALSE(theLegacyShipVariant.isValidVariant(*HoI4::technologies::Builder().Build()));
}


TEST(HoI4World_ShipTypes_LegacyShipVariantTests, HavingRequiredTechsMeansVariantIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::LegacyShipVariant theLegacyShipVariant(input);

	ASSERT_TRUE(
		 theLegacyShipVariant.isValidVariant(*HoI4::technologies::Builder().addTechnology("required_tech1").Build()));
}


TEST(HoI4World_ShipTypes_LegacyShipVariantTests, HavingOnlySomeRequiredTechsMeansVariantIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t\trequired_tech2\n";
	input << "\t}\n";
	input << "}";
	const HoI4::LegacyShipVariant theLegacyShipVariant(input);

	ASSERT_FALSE(
		 theLegacyShipVariant.isValidVariant(*HoI4::technologies::Builder().addTechnology("required_tech1").Build()));
}


TEST(HoI4World_ShipTypes_LegacyShipVariantTests, HavingBlockingTechsMeansVariantIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tblocking_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::LegacyShipVariant theLegacyShipVariant(input);

	ASSERT_FALSE(
		 theLegacyShipVariant.isValidVariant(*HoI4::technologies::Builder().addTechnology("required_tech1").Build()));
}


TEST(HoI4World_ShipTypes_LegacyShipVariantTests, HavingNoBlockingTechsMeansVariantIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tblocking_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::LegacyShipVariant theLegacyShipVariant(input);

	ASSERT_TRUE(theLegacyShipVariant.isValidVariant(*HoI4::technologies::Builder().Build()));
}