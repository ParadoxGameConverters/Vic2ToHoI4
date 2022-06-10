#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/TankDesigns/PossibleTankDesigns.h"
#include <sstream>



TEST(HoI4World_TankDesigns_possibleTankDesignsTests, tankDesignsDefaultToEmpty)
{
	std::stringstream input;
	const HoI4::PossibleTankDesigns theTankDesigns(input);

	ASSERT_TRUE(theTankDesigns.getPossibleTankDesigns().empty());
}


TEST(HoI4World_TankDesigns_possibleTankDesignsTests, tankDesignsCanBeLoaded)
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
	input << "\t\tgwtank_chassis\n";
	input << "\t\tgw_artillery\n";
	input << "\t}\n";
	input << "\tblocking_techs = {\n";
	input << "\t\tbasic_medium_tank_chassis\n";
	input << "\t}\n";
	input << "\tname = \"GW Medium Tank\"\n";
	input << "\ttype = medium_tank_chassis_0\n";
	input << "\tparent_version = 0\n";
	input << "\tmodules = {\n";
	input << "\t\tmain_armament_slot = tank_small_cannon\n";
	input << "\t\tturret_type_slot = tank_medium_one_man_tank_turret\n";
	input << "\t\tsuspension_type_slot = tank_bogie_suspension\n";
	input << "\t\tarmor_type_slot = tank_riveted_armor\n";
	input << "\t\tengine_type_slot = tank_gasoline_engine\n";
	input << "\t}\n";
	input << "\tobsolete = no\n";
	input << "\ticon = \"gfx/interface/technologies/SOV_basic_heavy_tank.dds\"\n";
	input << "}\n";
	const HoI4::PossibleTankDesigns theTankDesigns(input);

	ASSERT_EQ(theTankDesigns.getPossibleTankDesigns().size(), 2);
}