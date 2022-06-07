#include "src/HOI4World/ShipTypes/MtgShipVariant.h"
#include "src/HOI4World/TechnologiesBuilder.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_ShipTypes_MtgShipVariantTests, DefaultsSetCorrectly)
{
	std::stringstream input;
	input << "";
	HoI4::MtgShipVariant theMtgShipVariant(input);

	std::stringstream output;
	output << theMtgShipVariant;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tname_group = _\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_MtgShipVariantTests, NameCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname = \"ship_name\"\n";
	input << "}";
	const HoI4::MtgShipVariant theMtgShipVariant(input);

	ASSERT_EQ(std::string("ship_name"), theMtgShipVariant.getName());
}


TEST(HoI4World_ShipTypes_MtgShipVariantTests, TypeCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\ttype = \"ship_type\"\n";
	input << "}";
	HoI4::MtgShipVariant theMtgShipVariant(input);

	std::stringstream output;
	output << theMtgShipVariant;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = ship_type\n";
	expectedOutput << "\t\tname_group = _\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_MtgShipVariantTests, NameGroupCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname_group = NAME_GROUP\n";
	input << "}";
	HoI4::MtgShipVariant theMtgShipVariant(input);

	std::stringstream output;
	output << theMtgShipVariant;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tname_group = _NAME_GROUP\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_MtgShipVariantTests, OwningCountryTagCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname_group = NAME_GROUP\n";
	input << "}";
	HoI4::MtgShipVariant theMtgShipVariant(input);
	theMtgShipVariant.setOwningCountryTag("TAG");

	std::stringstream output;
	output << theMtgShipVariant;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tname_group = TAG_NAME_GROUP\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_MtgShipVariantTests, ModulesCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tmodules = {\n";
	input << "\t\tmoduleSpot1 = module1\n";
	input << "\t\tmoduleSpot2 = module2\n";
	input << "\t}";
	input << "}";
	HoI4::MtgShipVariant theMtgShipVariant(input);

	std::stringstream output;
	output << theMtgShipVariant;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tname_group = _\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t\tmodules = {\n";
	expectedOutput << "\t\t\tmoduleSpot1 = module1\n";
	expectedOutput << "\t\t\tmoduleSpot2 = module2\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_MtgShipVariantTests, CanBeSetObsolete)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tobsolete = yes\n";
	input << "}";
	HoI4::MtgShipVariant theMtgShipVariant(input);

	std::stringstream output;
	output << theMtgShipVariant;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tname_group = _\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t\tobsolete = yes\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_MtgShipVariantTests, OnlySetObsoleteByYes)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tobsolete = no\n";
	input << "}";
	HoI4::MtgShipVariant theMtgShipVariant(input);

	std::stringstream output;
	output << theMtgShipVariant;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tname_group = _\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_MtgShipVariantTests, NoRequiredTechsMeansVariantIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "}";
	const HoI4::MtgShipVariant theMtgShipVariant(input);

	ASSERT_TRUE(theMtgShipVariant.isValidVariant(*HoI4::technologies::Builder().Build()));
}


TEST(HoI4World_ShipTypes_MtgShipVariantTests, MissingRequiredTechMeansVariantIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::MtgShipVariant theMtgShipVariant(input);

	ASSERT_FALSE(theMtgShipVariant.isValidVariant(*HoI4::technologies::Builder().Build()));
}


TEST(HoI4World_ShipTypes_MtgShipVariantTests, HavingRequiredTechsMeansVariantIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::MtgShipVariant theMtgShipVariant(input);

	ASSERT_TRUE(
		 theMtgShipVariant.isValidVariant(*HoI4::technologies::Builder().addTechnology("required_tech1").Build()));
}


TEST(HoI4World_ShipTypes_MtgShipVariantTests, HavingOnlySomeRequiredTechsMeansVariantIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t\trequired_tech2\n";
	input << "\t}\n";
	input << "}";
	const HoI4::MtgShipVariant theMtgShipVariant(input);

	ASSERT_FALSE(
		 theMtgShipVariant.isValidVariant(*HoI4::technologies::Builder().addTechnology("required_tech1").Build()));
}


TEST(HoI4World_ShipTypes_MtgShipVariantTests, HavingBlockingTechsMeansVariantIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tblocking_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::MtgShipVariant theMtgShipVariant(input);

	ASSERT_FALSE(
		 theMtgShipVariant.isValidVariant(*HoI4::technologies::Builder().addTechnology("required_tech1").Build()));
}


TEST(HoI4World_ShipTypes_MtgShipVariantTests, HavingNoBlockingTechsMeansVariantIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tblocking_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::MtgShipVariant theMtgShipVariant(input);

	ASSERT_TRUE(theMtgShipVariant.isValidVariant(*HoI4::technologies::Builder().Build()));
}