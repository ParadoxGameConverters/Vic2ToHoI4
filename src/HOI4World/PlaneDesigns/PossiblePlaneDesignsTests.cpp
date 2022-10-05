#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/PlaneDesigns/PossiblePlaneDesigns.h"
#include <sstream>



TEST(HoI4World_PlaneDesigns_possiblePlaneDesignsTests, PlaneDesignsDefaultToEmpty)
{
	std::stringstream input;
	const HoI4::PossiblePlaneDesigns thePlaneDesigns(input);

	EXPECT_TRUE(thePlaneDesigns.GetPossiblePlaneDesigns().empty());
}


TEST(HoI4World_PlaneDesigns_possiblePlaneDesignsTests, PlaneDesignsCanBeLoaded)
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
	input << "\t\tiw_small_airframe\n";
	input << "\t\tearly_bombs\n";
	input << "\t}\n";
	input << "\tblocking_techs = {\n";
	input << "\t\tbasic_medium_airframe\n";
	input << "\t}\n";
	input << "\tname = \"GW Medium Plane\"\n";
	input << "\ttype = cv_small_plane_airframe_0\n";
	input << "\tparent_version = 0\n";
	input << "\tmodules = {\n";
	input << "\t\tfixed_main_weapon_slot = light_mg_2x\n";
	input << "\t\tengine_type_slot = engine_1_1x\n";
	input << "\t\tspecial_type_slot_1 = empty\n";
	input << "\t}\n";
	input << "\tobsolete = no\n";
	input << "\ticon = \"gfx/interface/technologies/GFX_USA_light_plane_2_medium.dds\"\n";
	input << "}\n";
	const HoI4::PossiblePlaneDesigns thePlaneDesigns(input);

	EXPECT_EQ(thePlaneDesigns.GetPossiblePlaneDesigns().size(), 2);
}