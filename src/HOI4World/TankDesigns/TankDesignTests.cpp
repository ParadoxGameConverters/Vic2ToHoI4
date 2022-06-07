#include "src/HOI4World/TankDesigns/TankDesign.h"
#include "src/HOI4World/TechnologiesBuilder.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_TankDesigns_TankDesignTests, DefaultsSetCorrectly)
{
	std::stringstream input;
	input << "";
	HoI4::TankDesign theTankDesign(input);

	std::stringstream output;
	output << theTankDesign;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_TankDesigns_TankDesignTests, NameCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname = \"tank_name\"\n";
	input << "}";
	const HoI4::TankDesign theTankDesign(input);

	ASSERT_EQ(std::string("tank_name"), theTankDesign.getName());
}


TEST(HoI4World_TankDesigns_TankDesignTests, TypeCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\ttype = \"tank_type\"\n";
	input << "}";
	HoI4::TankDesign theTankDesign(input);

	std::stringstream output;
	output << theTankDesign;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = tank_type\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_TankDesigns_TankDesignTests, ModulesCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tmodules = {\n";
	input << "\t\tmoduleSpot1 = module1\n";
	input << "\t\tmoduleSpot2 = module2\n";
	input << "\t}";
	input << "}";
	HoI4::TankDesign theTankDesign(input);

	std::stringstream output;
	output << theTankDesign;

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
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_TankDesigns_TankDesignTests, UpgradesCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tupgrades = {\n";
	input << "\t\tupgradeSpot1 = 1\n";
	input << "\t\tupgradeSpot2 = 2\n";
	input << "\t}";
	input << "}";
	HoI4::TankDesign theTankDesign(input);

	std::stringstream output;
	output << theTankDesign;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t\tupgrades = {\n";
	expectedOutput << "\t\t\tupgradeSpot1 = 1\n";
	expectedOutput << "\t\t\tupgradeSpot2 = 2\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_TankDesigns_TankDesignTests, IconCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\ticon = \"gfx/interface/technologies/gwtank.dds\"\n";
	input << "}";
	const HoI4::TankDesign theTankDesign(input);

	std::stringstream output;
	output << theTankDesign;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t\ticon = \"gfx/interface/technologies/gwtank.dds\"\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_TankDesigns_TankDesignTests, CanBeSetObsolete)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tobsolete = yes\n";
	input << "}";
	HoI4::TankDesign theTankDesign(input);

	std::stringstream output;
	output << theTankDesign;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t\tobsolete = yes\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_TankDesigns_TankDesignTests, OnlySetObsoleteByYes)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tobsolete = no\n";
	input << "}";
	HoI4::TankDesign theTankDesign(input);

	std::stringstream output;
	output << theTankDesign;

	std::stringstream expectedOutput;
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"\"\n";
	expectedOutput << "\t\ttype = \n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_TankDesigns_TankDesignTests, NoRequiredTechsMeansDesignIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "}";
	const HoI4::TankDesign theTankDesign(input);

	ASSERT_TRUE(theTankDesign.isValidDesign(*HoI4::technologies::Builder().Build()));
}


TEST(HoI4World_TankDesigns_TankDesignTests, MissingRequiredTechMeansDesignIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::TankDesign theTankDesign(input);

	ASSERT_FALSE(theTankDesign.isValidDesign(*HoI4::technologies::Builder().Build()));
}


TEST(HoI4World_TankDesigns_TankDesignTests, HavingRequiredTechsMeansDesignIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::TankDesign theTankDesign(input);

	ASSERT_TRUE(theTankDesign.isValidDesign(*HoI4::technologies::Builder().addTechnology("required_tech1").Build()));
}


TEST(HoI4World_TankDesigns_TankDesignTests, HavingOnlySomeRequiredTechsMeansDesignIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t\trequired_tech2\n";
	input << "\t}\n";
	input << "}";
	const HoI4::TankDesign theTankDesign(input);

	ASSERT_FALSE(theTankDesign.isValidDesign(*HoI4::technologies::Builder().addTechnology("required_tech1").Build()));
}


TEST(HoI4World_TankDesigns_TankDesignTests, HavingBlockingTechsMeansDesignIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tblocking_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::TankDesign theTankDesign(input);

	ASSERT_FALSE(theTankDesign.isValidDesign(*HoI4::technologies::Builder().addTechnology("required_tech1").Build()));
}


TEST(HoI4World_TankDesigns_TankDesignTests, HavingNoBlockingTechsMeansDesignIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tblocking_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::TankDesign theTankDesign(input);

	ASSERT_TRUE(theTankDesign.isValidDesign(*HoI4::technologies::Builder().Build()));
}