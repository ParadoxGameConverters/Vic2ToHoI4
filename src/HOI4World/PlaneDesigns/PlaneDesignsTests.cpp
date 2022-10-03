#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/PlaneDesigns/PlaneDesigns.h"
#include "src/HOI4World/TechnologiesBuilder.h"
#include <sstream>



TEST(HoI4World_PlaneDesigns_PlaneDesignsTests, DesignsDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::PossiblePlaneDesigns possibleDesigns(input);

	HoI4::PlaneDesigns theDesigns(possibleDesigns, *HoI4::technologies::Builder().Build());

	std::stringstream output;
	output << theDesigns;

	std::stringstream expectedOutput;
	expectedOutput << "### PLANE DESIGNS ###\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { has_dlc = \"By Blood Alone\" }\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_PlaneDesigns_PlaneDesignsTests, CanReceivePlaneDesign)
{
	std::stringstream input;
	input << "plane_design = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\tgwtank_chassis\n";
	input << "\t\tgw_artillery\n";
	input << "\t}\n";
	input << "\tblocking_techs = {\n";
	input << "\t\tbasic_light_tank_chassis\n";
	input << "\t}\n";
	input << "\tname = \"GW Light Plane\"\n";
	input << "\ttype = light_tank_chassis_0\n";
	input << "\tparent_version = 0\n";
	input << "\tmodules = {\n";
	input << "\t\tmain_armament_slot = tank_small_cannon\n";
	input << "\t\tturret_type_slot = tank_light_one_man_tank_turret\n";
	input << "\t\tsuspension_type_slot = tank_bogie_suspension\n";
	input << "\t\tarmor_type_slot = tank_riveted_armor\n";
	input << "\t\tengine_type_slot = tank_gasoline_engine\n";
	input << "\t}\n";
	input << "\tobsolete = no\n";
	input << "\ticon = \"gfx/interface/technologies/gwtank.dds\"\n";
	input << "}\n";
	HoI4::PossiblePlaneDesigns possibleDesigns(input);

	HoI4::PlaneDesigns theDesigns(possibleDesigns,
		 *HoI4::technologies::Builder().addTechnology("gwtank_chassis").addTechnology("gw_artillery").Build());

	std::stringstream output;
	output << theDesigns;

	std::stringstream expectedOutput;
	expectedOutput << "### PLANE DESIGNS ###\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { has_dlc = \"By Blood Alone\" }\n";
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"GW Light Plane\"\n";
	expectedOutput << "\t\ttype = light_tank_chassis_0\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t\tmodules = {\n";
	expectedOutput << "\t\t\tarmor_type_slot = tank_riveted_armor\n";
	expectedOutput << "\t\t\tengine_type_slot = tank_gasoline_engine\n";
	expectedOutput << "\t\t\tmain_armament_slot = tank_small_cannon\n";
	expectedOutput << "\t\t\tsuspension_type_slot = tank_bogie_suspension\n";
	expectedOutput << "\t\t\tturret_type_slot = tank_light_one_man_tank_turret\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\ticon = \"gfx/interface/technologies/gwtank.dds\"\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_PlaneDesigns_PlaneDesignsTests, HeldPlaneDesignIsIdentified)
{
	std::stringstream input;
	input << "plane_design = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\tgwtank_chassis\n";
	input << "\t\tgw_artillery\n";
	input << "\t}\n";
	input << "\tblocking_techs = {\n";
	input << "\t\tbasic_light_tank_chassis\n";
	input << "\t}\n";
	input << "\tname = \"GW Light Plane\"\n";
	input << "\ttype = light_tank_chassis_0\n";
	input << "\tparent_version = 0\n";
	input << "\tmodules = {\n";
	input << "\t\tmain_armament_slot = tank_small_cannon\n";
	input << "\t\tturret_type_slot = tank_light_one_man_tank_turret\n";
	input << "\t\tsuspension_type_slot = tank_bogie_suspension\n";
	input << "\t\tarmor_type_slot = tank_riveted_armor\n";
	input << "\t\tengine_type_slot = tank_gasoline_engine\n";
	input << "\t}\n";
	input << "\tobsolete = no\n";
	input << "\ticon = \"gfx/interface/technologies/gwtank.dds\"\n";
	input << "}\n";
	const HoI4::PossiblePlaneDesigns possibleDesigns(input);

	const HoI4::PlaneDesigns theDesigns(possibleDesigns,
		 *HoI4::technologies::Builder().addTechnology("gwtank_chassis").addTechnology("gw_artillery").Build());

	ASSERT_TRUE(theDesigns.hasPlaneDesign("GW Light Plane"));
}


TEST(HoI4World_PlaneDesigns_PlaneDesignsTests, MissingPlaneDesignIsNotIdentified)
{
	std::stringstream input;
	input << "tank_design = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\tgwtank_chassis\n";
	input << "\t\tgw_artillery\n";
	input << "\t}\n";
	input << "\tblocking_techs = {\n";
	input << "\t\tbasic_light_tank_chassis\n";
	input << "\t}\n";
	input << "\tname = \"GW Light Plane\"\n";
	input << "\ttype = light_tank_chassis_0\n";
	input << "\tparent_version = 0\n";
	input << "\tmodules = {\n";
	input << "\t\tmain_armament_slot = tank_small_cannon\n";
	input << "\t\tturret_type_slot = tank_light_one_man_tank_turret\n";
	input << "\t\tsuspension_type_slot = tank_bogie_suspension\n";
	input << "\t\tarmor_type_slot = tank_riveted_armor\n";
	input << "\t\tengine_type_slot = tank_gasoline_engine\n";
	input << "\t}\n";
	input << "\tobsolete = no\n";
	input << "\ticon = \"gfx/interface/technologies/gwtank.dds\"\n";
	input << "}\n";
	const HoI4::PossiblePlaneDesigns possibleDesigns(input);

	const HoI4::PlaneDesigns theDesigns(possibleDesigns, *HoI4::technologies::Builder().Build());

	ASSERT_FALSE(theDesigns.hasPlaneDesign("GW Medium Plane"));
}


TEST(HoI4World_PlaneDesigns_PlaneDesignsTests, PlaneDesignsNeedRequiredTechs)
{
	std::stringstream input;
	input << "plane_design = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\tgwtank_chassis\n";
	input << "\t\tgw_artillery\n";
	input << "\t}\n";
	input << "\tblocking_techs = {\n";
	input << "\t\tbasic_light_tank_chassis\n";
	input << "\t}\n";
	input << "\tname = \"GW Light Plane\"\n";
	input << "\ttype = light_tank_chassis_0\n";
	input << "\tparent_version = 0\n";
	input << "\tmodules = {\n";
	input << "\t\tmain_armament_slot = tank_small_cannon\n";
	input << "\t\tturret_type_slot = tank_light_one_man_tank_turret\n";
	input << "\t\tsuspension_type_slot = tank_bogie_suspension\n";
	input << "\t\tarmor_type_slot = tank_riveted_armor\n";
	input << "\t\tengine_type_slot = tank_gasoline_engine\n";
	input << "\t}\n";
	input << "\tobsolete = no\n";
	input << "\ticon = \"gfx/interface/technologies/gwtank.dds\"\n";
	input << "}\n";
	input << "\n";
	input << "plane_design = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\tbasic_light_tank_chassis\n";
	input << "\t\tgw_artillery\n";
	input << "\t}\n";
	input << "\tblocking_techs = {\n";
	input << "\t\timproved_light_tank_chassis\n";
	input << "\t}\n";
	input << "\tname = \"Basic Light Plane\"\n";
	input << "\ttype = light_tank_chassis_1\n";
	input << "\tparent_version = 0\n";
	input << "\tmodules = {\n";
	input << "\t\tmain_armament_slot = tank_small_cannon\n";
	input << "\t\tturret_type_slot = tank_light_two_man_tank_turret\n";
	input << "\t\tsuspension_type_slot = tank_bogie_suspension\n";
	input << "\t\tarmor_type_slot = tank_riveted_armor\n";
	input << "\t\tengine_type_slot = tank_gasoline_engine\n";
	input << "\t}\n";
	input << "\tobsolete = no\n";
	input << "}\n";
	HoI4::PossiblePlaneDesigns possibleDesigns(input);

	HoI4::PlaneDesigns theDesigns(possibleDesigns,
		 *HoI4::technologies::Builder().addTechnology("gwtank_chassis").addTechnology("gw_artillery").Build());

	std::stringstream output;
	output << theDesigns;

	std::stringstream expectedOutput;
	expectedOutput << "### PLANE DESIGNS ###\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { has_dlc = \"By Blood Alone\" }\n";
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"GW Light Plane\"\n";
	expectedOutput << "\t\ttype = light_tank_chassis_0\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t\tmodules = {\n";
	expectedOutput << "\t\t\tarmor_type_slot = tank_riveted_armor\n";
	expectedOutput << "\t\t\tengine_type_slot = tank_gasoline_engine\n";
	expectedOutput << "\t\t\tmain_armament_slot = tank_small_cannon\n";
	expectedOutput << "\t\t\tsuspension_type_slot = tank_bogie_suspension\n";
	expectedOutput << "\t\t\tturret_type_slot = tank_light_one_man_tank_turret\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\ticon = \"gfx/interface/technologies/gwtank.dds\"\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_PlaneDesigns_PlaneDesignsTests, PlaneDesignsCanBeBlocked)
{
	std::stringstream input;
	input << "plane_design = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\tgwtank_chassis\n";
	input << "\t\tgw_artillery\n";
	input << "\t}\n";
	input << "\tblocking_techs = {\n";
	input << "\t\tbasic_light_tank_chassis\n";
	input << "\t}\n";
	input << "\tname = \"GW Light Plane\"\n";
	input << "\ttype = light_tank_chassis_0\n";
	input << "\tparent_version = 0\n";
	input << "\tmodules = {\n";
	input << "\t\tmain_armament_slot = tank_small_cannon\n";
	input << "\t\tturret_type_slot = tank_light_one_man_tank_turret\n";
	input << "\t\tsuspension_type_slot = tank_bogie_suspension\n";
	input << "\t\tarmor_type_slot = tank_riveted_armor\n";
	input << "\t\tengine_type_slot = tank_gasoline_engine\n";
	input << "\t}\n";
	input << "\tobsolete = no\n";
	input << "\ticon = \"gfx/interface/technologies/gwtank.dds\"\n";
	input << "}\n";
	input << "\n";
	input << "plane_design = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\tbasic_light_tank_chassis\n";
	input << "\t\tgw_artillery\n";
	input << "\t}\n";
	input << "\tblocking_techs = {\n";
	input << "\t\timproved_light_tank_chassis\n";
	input << "\t}\n";
	input << "\tname = \"Basic Light Plane\"\n";
	input << "\ttype = light_tank_chassis_1\n";
	input << "\tparent_version = 0\n";
	input << "\tmodules = {\n";
	input << "\t\tmain_armament_slot = tank_small_cannon\n";
	input << "\t\tturret_type_slot = tank_light_two_man_tank_turret\n";
	input << "\t\tsuspension_type_slot = tank_bogie_suspension\n";
	input << "\t\tarmor_type_slot = tank_riveted_armor\n";
	input << "\t\tengine_type_slot = tank_gasoline_engine\n";
	input << "\t}\n";
	input << "\tobsolete = no\n";
	input << "}\n";
	HoI4::PossiblePlaneDesigns possibleDesigns(input);

	HoI4::PlaneDesigns theDesigns(possibleDesigns,
		 *HoI4::technologies::Builder()
				.addTechnology("gwtank_chassis")
				.addTechnology("gw_artillery")
				.addTechnology("improved_light_tank_chassis")
				.Build());

	std::stringstream output;
	output << theDesigns;

	std::stringstream expectedOutput;
	expectedOutput << "### PLANE DESIGNS ###\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { has_dlc = \"By Blood Alone\" }\n";
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"GW Light Plane\"\n";
	expectedOutput << "\t\ttype = light_tank_chassis_0\n";
	expectedOutput << "\t\tparent_version = 0\n";
	expectedOutput << "\t\tmodules = {\n";
	expectedOutput << "\t\t\tarmor_type_slot = tank_riveted_armor\n";
	expectedOutput << "\t\t\tengine_type_slot = tank_gasoline_engine\n";
	expectedOutput << "\t\t\tmain_armament_slot = tank_small_cannon\n";
	expectedOutput << "\t\t\tsuspension_type_slot = tank_bogie_suspension\n";
	expectedOutput << "\t\t\tturret_type_slot = tank_light_one_man_tank_turret\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t\ticon = \"gfx/interface/technologies/gwtank.dds\"\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}