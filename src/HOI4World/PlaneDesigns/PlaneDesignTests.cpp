#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/PlaneDesigns/PlaneDesign.h"
#include "src/HOI4World/TechnologiesBuilder.h"
#include <sstream>



TEST(HoI4World_PlaneDesigns_PlaneDesignTests, DefaultsSetCorrectly)
{
	std::stringstream input;
	input << "";
	HoI4::PlaneDesign thePlaneDesign(input);

	std::stringstream output;
	output << thePlaneDesign;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t}\n";
	EXPECT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, NameCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname = \"tank_name\"\n";
	input << "}";
	const HoI4::PlaneDesign thePlaneDesign(input);

	EXPECT_EQ(std::string("tank_name"), thePlaneDesign.getName());
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, TypeCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\ttype = \"tank_type\"\n";
	input << "}";
	HoI4::PlaneDesign thePlaneDesign(input);

	std::stringstream output;
	output << thePlaneDesign;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = tank_type\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t}\n";
	EXPECT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, ModulesCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tmodules = {\n";
	input << "\t\tmoduleSpot1 = module1\n";
	input << "\t\tmoduleSpot2 = module2\n";
	input << "\t}";
	input << "}";
	HoI4::PlaneDesign thePlaneDesign(input);

	std::stringstream output;
	output << thePlaneDesign;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t\tmodules = {\n";
	expectedOutput << "\t\t\tmoduleSpot1 = module1\n";
	expectedOutput << "\t\t\tmoduleSpot2 = module2\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	EXPECT_EQ(expectedOutput.str(), output.str());
}


// TEST(HoI4World_PlaneDesigns_PlaneDesignTests, UpgradesCanBeInput)
//{
//	std::stringstream input;
//	input << " = {\n";
//	input << "\tupgrades = {\n";
//	input << "\t\tupgradeSpot1 = 1\n";
//	input << "\t\tupgradeSpot2 = 2\n";
//	input << "\t}";
//	input << "}";
//	HoI4::PlaneDesign thePlaneDesign(input);
//
//	std::stringstream output;
//	output << thePlaneDesign;
//
//	std::stringstream expectedOutput;
//	expectedOutput << "\tcreate_equipment_variant = {\n";
//	expectedOutput << "\t\tname = \"\"\n";
//	expectedOutput << "\t\ttype = \n";
//	expectedOutput << "\t\tparent_version = 0\n";
//	expectedOutput << "\t\tupgrades = {\n";
//	expectedOutput << "\t\t\tupgradeSpot1 = 1\n";
//	expectedOutput << "\t\t\tupgradeSpot2 = 2\n";
//	expectedOutput << "\t\t}\n";
//	expectedOutput << "\t}\n";
//	EXPECT_EQ(expectedOutput.str(), output.str());
// }


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, IconCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\ticon = \"gfx/interface/technologies/gwtank.dds\"\n";
	input << "}";
	const HoI4::PlaneDesign thePlaneDesign(input);

	std::stringstream output;
	output << thePlaneDesign;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t\ticon = \"gfx/interface/technologies/gwtank.dds\"\n";
	expectedOutput << "\t}\n";
	EXPECT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, CanBeSetObsolete)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tobsolete = yes\n";
	input << "}";
	HoI4::PlaneDesign thePlaneDesign(input);

	std::stringstream output;
	output << thePlaneDesign;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t\tobsolete = yes\n";
	expectedOutput << "\t}\n";
	EXPECT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, OnlySetObsoleteByYes)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tobsolete = no\n";
	input << "}";
	HoI4::PlaneDesign thePlaneDesign(input);

	std::stringstream output;
	output << thePlaneDesign;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t}\n";
	EXPECT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, NoRequiredTechsMeansDesignIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "}";
	const HoI4::PlaneDesign thePlaneDesign(input);

	EXPECT_TRUE(thePlaneDesign.isValidDesign(*HoI4::technologies::Builder().Build()));
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, MissingRequiredTechMeansDesignIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::PlaneDesign thePlaneDesign(input);

	EXPECT_FALSE(thePlaneDesign.isValidDesign(*HoI4::technologies::Builder().Build()));
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, HavingRequiredTechsMeansDesignIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::PlaneDesign thePlaneDesign(input);

	EXPECT_TRUE(thePlaneDesign.isValidDesign(*HoI4::technologies::Builder().addTechnology("required_tech1").Build()));
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, HavingOnlySomeRequiredTechsMeansDesignIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t\trequired_tech2\n";
	input << "\t}\n";
	input << "}";
	const HoI4::PlaneDesign thePlaneDesign(input);

	EXPECT_FALSE(thePlaneDesign.isValidDesign(*HoI4::technologies::Builder().addTechnology("required_tech1").Build()));
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, HavingBlockingTechsMeansDesignIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tblocking_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::PlaneDesign thePlaneDesign(input);

	EXPECT_FALSE(thePlaneDesign.isValidDesign(*HoI4::technologies::Builder().addTechnology("required_tech1").Build()));
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, HavingNoBlockingTechsMeansDesignIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tblocking_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::PlaneDesign thePlaneDesign(input);

	EXPECT_TRUE(thePlaneDesign.isValidDesign(*HoI4::technologies::Builder().Build()));
}