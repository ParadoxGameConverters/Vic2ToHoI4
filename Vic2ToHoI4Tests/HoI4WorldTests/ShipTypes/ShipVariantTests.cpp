#include "../../Mocks/TechnologiesMock.h"
#include "../../Vic2ToHoI4/Source/HOI4World/ShipTypes/ShipVariant.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_ShipTypes_shipVariantTests, DefaultsSetCorrectly)
{
	std::stringstream input;
	input << "";
	HoI4::shipVariant theShipVariant(input);

	std::stringstream output;
	output << theShipVariant;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tname_group = _\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_shipVariantTests, NameCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname = \"ship_name\"\n";
	input << "}";
	const HoI4::shipVariant theShipVariant(input);

	ASSERT_EQ(std::string("ship_name"), theShipVariant.getName());
}


TEST(HoI4World_ShipTypes_shipVariantTests, TypeCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\ttype = \"ship_type\"\n";
	input << "}";
	HoI4::shipVariant theShipVariant(input);

	std::stringstream output;
	output << theShipVariant;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = ship_type\n";
	expectedOutput << "\t\tname_group = _\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_shipVariantTests, NameGroupCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname_group = NAME_GROUP\n";
	input << "}";
	HoI4::shipVariant theShipVariant(input);

	std::stringstream output;
	output << theShipVariant;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tname_group = _NAME_GROUP\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_shipVariantTests, OwningCountryTagCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname_group = NAME_GROUP\n";
	input << "}";
	HoI4::shipVariant theShipVariant(input);
	theShipVariant.setOwningCountryTag("TAG");

	std::stringstream output;
	output << theShipVariant;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tname_group = TAG_NAME_GROUP\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_shipVariantTests, ModulesCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tmodules = {\n";
	input << "\t\tmoduleSpot1 = module1\n";
	input << "\t\tmoduleSpot2 = module2\n";
	input << "\t}";
	input << "}";
	HoI4::shipVariant theShipVariant(input);

	std::stringstream output;
	output << theShipVariant;

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


TEST(HoI4World_ShipTypes_shipVariantTests, CanBeSetObsolete)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tobsolete = yes\n";
	input << "}";
	HoI4::shipVariant theShipVariant(input);

	std::stringstream output;
	output << theShipVariant;

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


TEST(HoI4World_ShipTypes_shipVariantTests, OnlySetObsoleteByYes)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tobsolete = no\n";
	input << "}";
	HoI4::shipVariant theShipVariant(input);

	std::stringstream output;
	output << theShipVariant;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tname_group = _\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_ShipTypes_shipVariantTests, NoRequiredTechsMeansVariantIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "}";
	const HoI4::shipVariant theShipVariant(input);

	const mockTechnologies countryTechs;

	ASSERT_TRUE(theShipVariant.isValidVariant(countryTechs));
}


TEST(HoI4World_ShipTypes_shipVariantTests, MissingRequiredTechMeansVariantIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::shipVariant theShipVariant(input);

	const mockTechnologies countryTechs;

	ASSERT_FALSE(theShipVariant.isValidVariant(countryTechs));
}


TEST(HoI4World_ShipTypes_shipVariantTests, HavingRequiredTechsMeansVariantIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::shipVariant theShipVariant(input);

	const mockTechnologies mockTechs;
	EXPECT_CALL(mockTechs, hasTechnology("required_tech1")).WillOnce(testing::Return(true));

	ASSERT_TRUE(theShipVariant.isValidVariant(mockTechs));
}


TEST(HoI4World_ShipTypes_shipVariantTests, HavingOnlySomeRequiredTechsMeansVariantIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t\trequired_tech2\n";
	input << "\t}\n";
	input << "}";
	const HoI4::shipVariant theShipVariant(input);

	const mockTechnologies mockTechs;
	EXPECT_CALL(mockTechs, hasTechnology("required_tech1")).WillOnce(testing::Return(true));
	EXPECT_CALL(mockTechs, hasTechnology("required_tech2")).WillOnce(testing::Return(false));

	ASSERT_FALSE(theShipVariant.isValidVariant(mockTechs));
}


TEST(HoI4World_ShipTypes_shipVariantTests, HavingBlockingTechsMeansVariantIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tblocking_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::shipVariant theShipVariant(input);

	const mockTechnologies mockTechs;
	EXPECT_CALL(mockTechs, hasTechnology("required_tech1")).WillOnce(testing::Return(true));

	ASSERT_FALSE(theShipVariant.isValidVariant(mockTechs));
}


TEST(HoI4World_ShipTypes_shipVariantTests, HavingNoBlockingTechsMeansVariantIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tblocking_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::shipVariant theShipVariant(input);

	const mockTechnologies countryTechs;

	ASSERT_TRUE(theShipVariant.isValidVariant(countryTechs));
}