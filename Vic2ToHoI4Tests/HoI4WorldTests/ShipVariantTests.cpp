/*Copyright (c) 2019 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../../Vic2ToHoI4/Source/HOI4World/ShipTypes/ShipVariant.h"
#include "../Mocks/TechnologiesMock.h"
#include <sstream>



TEST(HoI4World_shipVariantTests, noInputGivesDefaultOutput)
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


TEST(HoI4World_shipVariantTests, nameCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname = \"ship_name\"\n";
	input << "}";
	HoI4::shipVariant theShipVariant(input);

	std::stringstream output;
	output << theShipVariant;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"ship_name\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tname_group = _\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_shipVariantTests, typeCanBeInput)
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


TEST(HoI4World_shipVariantTests, nameGroupCanBeInput)
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


TEST(HoI4World_shipVariantTests, owningCountryTagCanBeInput)
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


TEST(HoI4World_shipVariantTests, modulesCanBeInput)
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


TEST(HoI4World_shipVariantTests, canBeSetObsolete)
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


TEST(HoI4World_shipVariantTests, onlySetObsoleteByYes)
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


TEST(HoI4World_shipVariantTests, noRequiredTechsMeansVariantIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "}";
	HoI4::shipVariant theShipVariant(input);

	mockTechnologies countrytechs;

	ASSERT_TRUE(theShipVariant.isValidVariant(countrytechs));
}


TEST(HoI4World_shipVariantTests, missingRequiredTechMeansVariantIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	HoI4::shipVariant theShipVariant(input);

	mockTechnologies countrytechs;

	ASSERT_FALSE(theShipVariant.isValidVariant(countrytechs));
}


TEST(HoI4World_shipVariantTests, havingRequiredTechsMeansVariantIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	HoI4::shipVariant theShipVariant(input);

	mockTechnologies mockTechs;
	EXPECT_CALL(mockTechs, hasTechnology("required_tech1")).WillOnce(testing::Return(true));

	ASSERT_TRUE(theShipVariant.isValidVariant(mockTechs));
}


TEST(HoI4World_shipVariantTests, havingOnlySomeRequiredTechsMeansVariantIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t\trequired_tech2\n";
	input << "\t}\n";
	input << "}";
	HoI4::shipVariant theShipVariant(input);

	mockTechnologies mockTechs;
	EXPECT_CALL(mockTechs, hasTechnology("required_tech1")).WillOnce(testing::Return(true));
	EXPECT_CALL(mockTechs, hasTechnology("required_tech2")).WillOnce(testing::Return(false));

	ASSERT_FALSE(theShipVariant.isValidVariant(mockTechs));
}


TEST(HoI4World_shipVariantTests, havingBlockingTechsMeansVariantIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tblocking_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	HoI4::shipVariant theShipVariant(input);

	mockTechnologies mockTechs;
	EXPECT_CALL(mockTechs, hasTechnology("required_tech1")).WillOnce(testing::Return(true));

	ASSERT_FALSE(theShipVariant.isValidVariant(mockTechs));
}


TEST(HoI4World_shipVariantTests, havingNoBlockingTechsMeansVariantIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tblocking_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	HoI4::shipVariant theShipVariant(input);

	mockTechnologies countryTechs;

	ASSERT_TRUE(theShipVariant.isValidVariant(countryTechs));
}