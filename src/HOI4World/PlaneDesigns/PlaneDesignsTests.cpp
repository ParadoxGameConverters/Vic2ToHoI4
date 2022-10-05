#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/PlaneDesigns/PlaneDesigns.h"
#include "src/HOI4World/TechnologiesBuilder.h"
#include <sstream>



TEST(HoI4World_PlaneDesigns_PlaneDesignsTests, DesignsDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::PossiblePlaneDesigns possible_designs(input);

	HoI4::PlaneDesigns the_designs(possible_designs, *HoI4::technologies::Builder().Build());

	std::stringstream output;
	output << the_designs;

	std::stringstream expected_output;
	expected_output << "### PLANE DESIGNS ###\n";
	expected_output << "if = {\n";
	expected_output << "\tlimit = { has_dlc = \"By Blood Alone\" }\n";
	expected_output << "}\n";
	ASSERT_EQ(expected_output.str(), output.str());
}


TEST(HoI4World_PlaneDesigns_PlaneDesignsTests, CanReceivePlaneDesign)
{
	std::stringstream input;
	input << "plane_design = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\tiw_small_airframe\n";
	input << "\t\tearly_bombs\n";
	input << "\t}\n";
	input << "\tblocking_techs = {\n";
	input << "\t\tbasic_small_airframe\n";
	input << "\t}\n";
	input << "\tname = \"GW Light Plane\"\n";
	input << "\ttype = small_plane_airframe_0\n";
	input << "\tmodules = {\n";
	input << "\t\tfixed_main_weapon_slot = light_mg_2x\n";
	input << "\t\tengine_type_slot = engine_1_1x\n";
	input << "\t\tspecial_type_slot_1 = empty\n";
	input << "\t}\n";
	input << "\tobsolete = no\n";
	input << "\ticon = \"gfx/interface/technologies/GFX_USA_light_plane_2_medium.dds\"\n";
	input << "}\n";
	HoI4::PossiblePlaneDesigns possible_designs(input);

	HoI4::PlaneDesigns the_designs(possible_designs,
		 *HoI4::technologies::Builder().addTechnology("iw_small_airframe").addTechnology("early_bombs").Build());

	std::stringstream output;
	output << the_designs;

	std::stringstream expected_output;
	expected_output << "### PLANE DESIGNS ###\n";
	expected_output << "if = {\n";
	expected_output << "\tlimit = { has_dlc = \"By Blood Alone\" }\n";
	expected_output << "\tcreate_equipment_variant = {\n";
	expected_output << "\t\tname = \"GW Light Plane\"\n";
	expected_output << "\t\ttype = small_plane_airframe_0\n";
	expected_output << "\t\tmodules = {\n";
	expected_output << "\t\t\tengine_type_slot = engine_1_1x\n";
	expected_output << "\t\t\tfixed_main_weapon_slot = light_mg_2x\n";
	expected_output << "\t\t\tspecial_type_slot_1 = empty\n";
	expected_output << "\t\t}\n";
	expected_output << "\t\ticon = \"gfx/interface/technologies/GFX_USA_light_plane_2_medium.dds\"\n";
	expected_output << "\t}\n";
	expected_output << "}\n";
	ASSERT_EQ(expected_output.str(), output.str());
}


TEST(HoI4World_PlaneDesigns_PlaneDesignsTests, HeldPlaneDesignIsIdentified)
{
	std::stringstream input;
	input << "plane_design = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\tiw_small_airframe\n";
	input << "\t\tearly_bombs\n";
	input << "\t}\n";
	input << "\tblocking_techs = {\n";
	input << "\t\tbasic_small_airframe\n";
	input << "\t}\n";
	input << "\tname = \"GW Light Plane\"\n";
	input << "\ttype = small_plane_airframe_0\n";
	input << "\tmodules = {\n";
	input << "\t\tfixed_main_weapon_slot = light_mg_2x\n";
	input << "\t\tengine_type_slot = engine_1_1x\n";
	input << "\t\tspecial_type_slot_1 = empty\n";
	input << "\t}\n";
	input << "\tobsolete = no\n";
	input << "\ticon = \"gfx/interface/technologies/GFX_USA_light_plane_2_medium.dds\"\n";
	input << "}\n";
	const HoI4::PossiblePlaneDesigns possible_designs(input);

	const HoI4::PlaneDesigns the_designs(possible_designs,
		 *HoI4::technologies::Builder().addTechnology("iw_small_airframe").addTechnology("early_bombs").Build());

	ASSERT_TRUE(the_designs.HasPlaneDesign("GW Light Plane"));
}


TEST(HoI4World_PlaneDesigns_PlaneDesignsTests, MissingPlaneDesignIsNotIdentified)
{
	std::stringstream input;
	input << "plane_design = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\tiw_small_airframe\n";
	input << "\t\tearly_bombs\n";
	input << "\t}\n";
	input << "\tblocking_techs = {\n";
	input << "\t\tbasic_small_airframe\n";
	input << "\t}\n";
	input << "\tname = \"GW Light Plane\"\n";
	input << "\ttype = small_plane_airframe_0\n";
	input << "\tmodules = {\n";
	input << "\t\tfixed_main_weapon_slot = light_mg_2x\n";
	input << "\t\tengine_type_slot = engine_1_1x\n";
	input << "\t\tspecial_type_slot_1 = empty\n";
	input << "\t}\n";
	input << "\tobsolete = no\n";
	input << "\ticon = \"gfx/interface/technologies/GFX_USA_light_plane_2_medium.dds\"\n";
	input << "}\n";
	const HoI4::PossiblePlaneDesigns possible_designs(input);

	const HoI4::PlaneDesigns the_designs(possible_designs, *HoI4::technologies::Builder().Build());

	ASSERT_FALSE(the_designs.HasPlaneDesign("GW Medium Plane"));
}


TEST(HoI4World_PlaneDesigns_PlaneDesignsTests, PlaneDesignsNeedRequiredTechs)
{
	std::stringstream input;
	input << "plane_design = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\tiw_small_airframe\n";
	input << "\t\tearly_bombs\n";
	input << "\t}\n";
	input << "\tblocking_techs = {\n";
	input << "\t\tbasic_small_airframe\n";
	input << "\t}\n";
	input << "\tname = \"GW Light Plane\"\n";
	input << "\ttype = small_plane_airframe_0\n";
	input << "\tmodules = {\n";
	input << "\t\tfixed_main_weapon_slot = light_mg_2x\n";
	input << "\t\tengine_type_slot = engine_1_1x\n";
	input << "\t\tspecial_type_slot_1 = empty\n";
	input << "\t}\n";
	input << "\tobsolete = no\n";
	input << "\ticon = \"gfx/interface/technologies/GFX_USA_light_plane_2_medium.dds\"\n";
	input << "}\n";
	input << "\n";
	input << "plane_design = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\tbasic_small_airframe\n";
	input << "\t\tearly_bombs\n";
	input << "\t}\n";
	input << "\tblocking_techs = {\n";
	input << "\t\tbasic_medium_airframe\n";
	input << "\t}\n";
	input << "\tname = \"Basic Light Plane\"\n";
	input << "\ttype = cv_small_plane_airframe_0\n";
	input << "\tmodules = {\n";
	input << "\t\tfixed_main_weapon_slot = light_mg_2x\n";
	input << "\t\tengine_type_slot = engine_1_1x\n";
	input << "\t\tspecial_type_slot_1 = empty\n";
	input << "\t}\n";
	input << "\tobsolete = no\n";
	input << "}\n";
	HoI4::PossiblePlaneDesigns possible_designs(input);

	HoI4::PlaneDesigns the_designs(possible_designs,
		 *HoI4::technologies::Builder().addTechnology("iw_small_airframe").addTechnology("early_bombs").Build());

	std::stringstream output;
	output << the_designs;

	std::stringstream expected_output;
	expected_output << "### PLANE DESIGNS ###\n";
	expected_output << "if = {\n";
	expected_output << "\tlimit = { has_dlc = \"By Blood Alone\" }\n";
	expected_output << "\tcreate_equipment_variant = {\n";
	expected_output << "\t\tname = \"GW Light Plane\"\n";
	expected_output << "\t\ttype = small_plane_airframe_0\n";
	expected_output << "\t\tmodules = {\n";
	expected_output << "\t\t\tengine_type_slot = engine_1_1x\n";
	expected_output << "\t\t\tfixed_main_weapon_slot = light_mg_2x\n";
	expected_output << "\t\t\tspecial_type_slot_1 = empty\n";
	expected_output << "\t\t}\n";
	expected_output << "\t\ticon = \"gfx/interface/technologies/GFX_USA_light_plane_2_medium.dds\"\n";
	expected_output << "\t}\n";
	expected_output << "}\n";
	ASSERT_EQ(expected_output.str(), output.str());
}


TEST(HoI4World_PlaneDesigns_PlaneDesignsTests, PlaneDesignsCanBeBlocked)
{
	std::stringstream input;
	input << "plane_design = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\tiw_small_airframe\n";
	input << "\t\tearly_bombs\n";
	input << "\t}\n";
	input << "\tblocking_techs = {\n";
	input << "\t\tbasic_small_airframe\n";
	input << "\t}\n";
	input << "\tname = \"GW Light Plane\"\n";
	input << "\ttype = small_plane_airframe_0\n";
	input << "\tmodules = {\n";
	input << "\t\tfixed_main_weapon_slot = light_mg_2x\n";
	input << "\t\tengine_type_slot = engine_1_1x\n";
	input << "\t\tspecial_type_slot_1 = empty\n";
	input << "\t}\n";
	input << "\tobsolete = no\n";
	input << "\ticon = \"gfx/interface/technologies/GFX_USA_light_plane_2_medium.dds\"\n";
	input << "}\n";
	input << "\n";
	input << "plane_design = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\tbasic_small_airframe\n";
	input << "\t\tearly_bombs\n";
	input << "\t}\n";
	input << "\tblocking_techs = {\n";
	input << "\t\tbasic_medium_airframe\n";
	input << "\t}\n";
	input << "\tname = \"Basic Light Plane\"\n";
	input << "\ttype = cv_small_plane_airframe_0\n";
	input << "\tmodules = {\n";
	input << "\t\tfixed_main_weapon_slot = light_mg_2x\n";
	input << "\t\tengine_type_slot = engine_1_1x\n";
	input << "\t\tspecial_type_slot_1 = empty\n";
	input << "\t}\n";
	input << "\tobsolete = no\n";
	input << "}\n";
	HoI4::PossiblePlaneDesigns possible_designs(input);

	HoI4::PlaneDesigns the_designs(possible_designs,
		 *HoI4::technologies::Builder()
				.addTechnology("iw_small_airframe")
				.addTechnology("early_bombs")
				.addTechnology("basic_medium_airframe")
				.Build());

	std::stringstream output;
	output << the_designs;

	std::stringstream expected_output;
	expected_output << "### PLANE DESIGNS ###\n";
	expected_output << "if = {\n";
	expected_output << "\tlimit = { has_dlc = \"By Blood Alone\" }\n";
	expected_output << "\tcreate_equipment_variant = {\n";
	expected_output << "\t\tname = \"GW Light Plane\"\n";
	expected_output << "\t\ttype = small_plane_airframe_0\n";
	expected_output << "\t\tmodules = {\n";
	expected_output << "\t\t\tengine_type_slot = engine_1_1x\n";
	expected_output << "\t\t\tfixed_main_weapon_slot = light_mg_2x\n";
	expected_output << "\t\t\tspecial_type_slot_1 = empty\n";
	expected_output << "\t\t}\n";
	expected_output << "\t\ticon = \"gfx/interface/technologies/GFX_USA_light_plane_2_medium.dds\"\n";
	expected_output << "\t}\n";
	expected_output << "}\n";
	ASSERT_EQ(expected_output.str(), output.str());
}