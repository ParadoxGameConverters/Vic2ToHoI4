#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/PlaneDesigns/PlaneDesign.h"
#include "src/HOI4World/TechnologiesBuilder.h"
#include <sstream>



TEST(HoI4World_PlaneDesigns_PlaneDesignTests, NameIsRequiredForDesign)
{
	std::stringstream input;
	input << " = {\n";
	input << "\ttype = \"plane_type\"\n";
	input << "}";
	EXPECT_THROW(HoI4::PlaneDesign the_plane_design(input), std::runtime_error);
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, TypeIsRequiredForDesign)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname = \"plane_name\"\n";
	input << "}";
	EXPECT_THROW(HoI4::PlaneDesign the_plane_design(input), std::runtime_error);
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, NameAndTypeCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname = \"plane_name\"\n";
	input << "\ttype = \"plane_type\"\n";
	input << "}";
	HoI4::PlaneDesign the_plane_design(input);

	std::stringstream output;
	output << the_plane_design;

	std::stringstream expected_output;
	expected_output << "\tcreate_equipment_variant = {\n";
	expected_output << "\t\tname = \"plane_name\"\n";
	expected_output << "\t\ttype = plane_type\n";
	expected_output << "\t}\n";
	EXPECT_EQ(expected_output.str(), output.str());
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, ModulesCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname = \"plane_name\"\n";
	input << "\ttype = \"plane_type\"\n";
	input << "\tmodules = {\n";
	input << "\t\tmoduleSpot1 = module1\n";
	input << "\t\tmoduleSpot2 = module2\n";
	input << "\t}";
	input << "}";
	HoI4::PlaneDesign the_plane_design(input);

	std::stringstream output;
	output << the_plane_design;

	std::stringstream expected_output;
	expected_output << "\tcreate_equipment_variant = {\n";
	expected_output << "\t\tname = \"plane_name\"\n";
	expected_output << "\t\ttype = plane_type\n";
	expected_output << "\t\tmodules = {\n";
	expected_output << "\t\t\tmoduleSpot1 = module1\n";
	expected_output << "\t\t\tmoduleSpot2 = module2\n";
	expected_output << "\t\t}\n";
	expected_output << "\t}\n";
	EXPECT_EQ(expected_output.str(), output.str());
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, IconCanBeInput)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname = \"plane_name\"\n";
	input << "\ttype = \"plane_type\"\n";
	input << "\ticon = \"gfx/interface/technologies/if_fighter.dds\"\n";
	input << "}";
	const HoI4::PlaneDesign the_plane_design(input);

	std::stringstream output;
	output << the_plane_design;

	std::stringstream expected_output;
	expected_output << "\tcreate_equipment_variant = {\n";
	expected_output << "\t\tname = \"plane_name\"\n";
	expected_output << "\t\ttype = plane_type\n";
	expected_output << "\t\ticon = \"gfx/interface/technologies/if_fighter.dds\"\n";
	expected_output << "\t}\n";
	EXPECT_EQ(expected_output.str(), output.str());
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, CanBeSetObsolete)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname = \"plane_name\"\n";
	input << "\ttype = \"plane_type\"\n";
	input << "\tobsolete = yes\n";
	input << "}";
	HoI4::PlaneDesign the_plane_design(input);

	std::stringstream output;
	output << the_plane_design;

	std::stringstream expected_output;
	expected_output << "\tcreate_equipment_variant = {\n";
	expected_output << "\t\tname = \"plane_name\"\n";
	expected_output << "\t\ttype = plane_type\n";
	expected_output << "\t\tobsolete = yes\n";
	expected_output << "\t}\n";
	EXPECT_EQ(expected_output.str(), output.str());
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, OnlySetObsoleteByYes)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname = \"plane_name\"\n";
	input << "\ttype = \"plane_type\"\n";
	input << "\tobsolete = no\n";
	input << "}";
	HoI4::PlaneDesign the_plane_design(input);

	std::stringstream output;
	output << the_plane_design;

	std::stringstream expected_output;
	expected_output << "\tcreate_equipment_variant = {\n";
	expected_output << "\t\tname = \"plane_name\"\n";
	expected_output << "\t\ttype = plane_type\n";
	expected_output << "\t}\n";
	EXPECT_EQ(expected_output.str(), output.str());
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, NoRequiredTechsMeansDesignIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname = \"plane_name\"\n";
	input << "\ttype = \"plane_type\"\n";
	input << "}";
	const HoI4::PlaneDesign the_plane_design(input);

	EXPECT_TRUE(the_plane_design.IsValidDesign(*HoI4::technologies::Builder().Build()));
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, MissingRequiredTechMeansDesignIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname = \"plane_name\"\n";
	input << "\ttype = \"plane_type\"\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::PlaneDesign the_plane_design(input);

	EXPECT_FALSE(the_plane_design.IsValidDesign(*HoI4::technologies::Builder().Build()));
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, HavingRequiredTechsMeansDesignIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname = \"plane_name\"\n";
	input << "\ttype = \"plane_type\"\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::PlaneDesign the_plane_design(input);

	EXPECT_TRUE(the_plane_design.IsValidDesign(*HoI4::technologies::Builder().addTechnology("required_tech1").Build()));
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, HavingOnlySomeRequiredTechsMeansDesignIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname = \"plane_name\"\n";
	input << "\ttype = \"plane_type\"\n";
	input << "\trequired_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t\trequired_tech2\n";
	input << "\t}\n";
	input << "}";
	const HoI4::PlaneDesign the_plane_design(input);

	EXPECT_FALSE(the_plane_design.IsValidDesign(*HoI4::technologies::Builder().addTechnology("required_tech1").Build()));
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, HavingBlockingTechsMeansDesignIsInvalid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname = \"plane_name\"\n";
	input << "\ttype = \"plane_type\"\n";
	input << "\tblocking_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::PlaneDesign the_plane_design(input);

	EXPECT_FALSE(the_plane_design.IsValidDesign(*HoI4::technologies::Builder().addTechnology("required_tech1").Build()));
}


TEST(HoI4World_PlaneDesigns_PlaneDesignTests, HavingNoBlockingTechsMeansDesignIsValid)
{
	std::stringstream input;
	input << " = {\n";
	input << "\tname = \"plane_name\"\n";
	input << "\ttype = \"plane_type\"\n";
	input << "\tblocking_techs = {\n";
	input << "\t\trequired_tech1\n";
	input << "\t}\n";
	input << "}";
	const HoI4::PlaneDesign the_plane_design(input);

	EXPECT_TRUE(the_plane_design.IsValidDesign(*HoI4::technologies::Builder().Build()));
}