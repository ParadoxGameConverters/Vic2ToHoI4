#include "src/HOI4World/TankDesigns/TankDesigns.h"
#include "src/HOI4World/TechnologiesBuilder.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_TankDesigns_TankDesignsTests, DesignsDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::PossibleTankDesigns possibleDesigns(input);

	HoI4::TankDesigns theDesigns(possibleDesigns, *HoI4::technologies::Builder().Build());

	std::stringstream output;
	output << theDesigns;

	std::stringstream expectedOutput;
	expectedOutput << "### TANK DESIGNS ###\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { has_dlc = \"No Step Back\" }\n";
	expectedOutput << "}\n";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_TankDesigns_TankDesignsTests, CanReceiveTankDesign)
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
	input << "\tname = \"GW Light Tank\"\n";
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
	HoI4::PossibleTankDesigns possibleDesigns(input);

	HoI4::TankDesigns theDesigns(possibleDesigns,
		 *HoI4::technologies::Builder().addTechnology("gwtank_chassis").addTechnology("gw_artillery").Build());

	std::stringstream output;
	output << theDesigns;

	std::stringstream expectedOutput;
	expectedOutput << "### TANK DESIGNS ###\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { has_dlc = \"No Step Back\" }\n";
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"GW Light Tank\"\n";
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


TEST(HoI4World_TankDesigns_TankDesignsTests, HeldTankDesignIsIdentified)
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
	input << "\tname = \"GW Light Tank\"\n";
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
	HoI4::PossibleTankDesigns possibleDesigns(input);

	const HoI4::TankDesigns theDesigns(possibleDesigns,
		 *HoI4::technologies::Builder().addTechnology("gwtank_chassis").addTechnology("gw_artillery").Build());

	ASSERT_TRUE(theDesigns.hasTankDesign("GW Light Tank"));
}


TEST(HoI4World_TankDesigns_TankDesignsTests, MissingTankDesignIsNotIdentified)
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
	input << "\tname = \"GW Light Tank\"\n";
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
	HoI4::PossibleTankDesigns possibleDesigns(input);

	const HoI4::TankDesigns theDesigns(possibleDesigns, *HoI4::technologies::Builder().Build());

	ASSERT_FALSE(theDesigns.hasTankDesign("GW Medium Tank"));
}


TEST(HoI4World_TankDesigns_TankDesignsTests, TankDesignsNeedRequiredTechs)
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
	input << "\tname = \"GW Light Tank\"\n";
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
	input << "tank_design = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\tbasic_light_tank_chassis\n";
	input << "\t\tgw_artillery\n";
	input << "\t}\n";
	input << "\tblocking_techs = {\n";
	input << "\t\timproved_light_tank_chassis\n";
	input << "\t}\n";
	input << "\tname = \"Basic Light Tank\"\n";
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
	HoI4::PossibleTankDesigns possibleDesigns(input);

	HoI4::TankDesigns theDesigns(possibleDesigns,
		 *HoI4::technologies::Builder().addTechnology("gwtank_chassis").addTechnology("gw_artillery").Build());

	std::stringstream output;
	output << theDesigns;

	std::stringstream expectedOutput;
	expectedOutput << "### TANK DESIGNS ###\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { has_dlc = \"No Step Back\" }\n";
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"GW Light Tank\"\n";
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


TEST(HoI4World_TankDesigns_TankDesignsTests, TankDesignsCanBeBlocked)
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
	input << "\tname = \"GW Light Tank\"\n";
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
	input << "tank_design = {\n";
	input << "\trequired_techs = {\n";
	input << "\t\tbasic_light_tank_chassis\n";
	input << "\t\tgw_artillery\n";
	input << "\t}\n";
	input << "\tblocking_techs = {\n";
	input << "\t\timproved_light_tank_chassis\n";
	input << "\t}\n";
	input << "\tname = \"Basic Light Tank\"\n";
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
	HoI4::PossibleTankDesigns possibleDesigns(input);

	HoI4::TankDesigns theDesigns(possibleDesigns,
		 *HoI4::technologies::Builder()
				.addTechnology("gwtank_chassis")
				.addTechnology("gw_artillery")
				.addTechnology("improved_light_tank_chassis")
				.Build());

	std::stringstream output;
	output << theDesigns;

	std::stringstream expectedOutput;
	expectedOutput << "### TANK DESIGNS ###\n";
	expectedOutput << "if = {\n";
	expectedOutput << "\tlimit = { has_dlc = \"No Step Back\" }\n";
	expectedOutput << "\tcreate_equipment_variant = {\n";
	expectedOutput << "\t\tname = \"GW Light Tank\"\n";
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