#include "../../Mocks/TechnologiesMock.h"
#include "../../Vic2ToHoI4/Source/HOI4World/ShipTypes/MtgShipVariant.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_ShipTypes_MtgMtgShipVariantTests, DefaultsSetCorrectly)
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


TEST(HoI4World_ShipTypes_MtgMtgShipVariantTests, NameCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname = \"ship_name\"\n";
	input << "}";
	const HoI4::MtgShipVariant theMtgShipVariant(input);

	ASSERT_EQ(std::string("ship_name"), theMtgShipVariant.getName());
}


TEST(HoI4World_ShipTypes_MtgMtgShipVariantTests, TypeCanBeInput)
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


TEST(HoI4World_ShipTypes_MtgMtgShipVariantTests, NameGroupCanBeInput)
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


TEST(HoI4World_ShipTypes_MtgMtgShipVariantTests, OwningCountryTagCanBeInput)
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


TEST(HoI4World_ShipTypes_MtgMtgShipVariantTests, ModulesCanBeInput)
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


TEST(HoI4World_ShipTypes_MtgMtgShipVariantTests, CanBeSetObsolete)
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


TEST(HoI4World_ShipTypes_MtgMtgShipVariantTests, OnlySetObsoleteByYes)
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


TEST(HoI4World_ShipTypes_MtgMtgShipVariantTests, NoRequiredTechsMeansVariantIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "}";
	const HoI4::MtgShipVariant theMtgShipVariant(input);

	const mockTechnologies countryTechs;

	ASSERT_TRUE(theMtgShipVariant.isValidVariant(countryTechs));
}


TEST(HoI4World_ShipTypes_MtgMtgShipVariantTests, MissingRequiredTechMeansVariantIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::MtgShipVariant theMtgShipVariant(input);

	const mockTechnologies countryTechs;

	ASSERT_FALSE(theMtgShipVariant.isValidVariant(countryTechs));
}


TEST(HoI4World_ShipTypes_MtgMtgShipVariantTests, HavingRequiredTechsMeansVariantIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::MtgShipVariant theMtgShipVariant(input);

	const mockTechnologies mockTechs;
	EXPECT_CALL(mockTechs, hasTechnology("required_tech1")).WillOnce(testing::Return(true));

	ASSERT_TRUE(theMtgShipVariant.isValidVariant(mockTechs));
}


TEST(HoI4World_ShipTypes_MtgMtgShipVariantTests, HavingOnlySomeRequiredTechsMeansVariantIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t\trequired_tech2\n";
	input << "\t}\n";
	input << "}";
	const HoI4::MtgShipVariant theMtgShipVariant(input);

	const mockTechnologies mockTechs;
	EXPECT_CALL(mockTechs, hasTechnology("required_tech1")).WillOnce(testing::Return(true));
	EXPECT_CALL(mockTechs, hasTechnology("required_tech2")).WillOnce(testing::Return(false));

	ASSERT_FALSE(theMtgShipVariant.isValidVariant(mockTechs));
}


TEST(HoI4World_ShipTypes_MtgMtgShipVariantTests, HavingBlockingTechsMeansVariantIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tblocking_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::MtgShipVariant theMtgShipVariant(input);

	const mockTechnologies mockTechs;
	EXPECT_CALL(mockTechs, hasTechnology("required_tech1")).WillOnce(testing::Return(true));

	ASSERT_FALSE(theMtgShipVariant.isValidVariant(mockTechs));
}


TEST(HoI4World_ShipTypes_MtgMtgShipVariantTests, HavingNoBlockingTechsMeansVariantIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tblocking_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::MtgShipVariant theMtgShipVariant(input);

	const mockTechnologies countryTechs;

	ASSERT_TRUE(theMtgShipVariant.isValidVariant(countryTechs));
}