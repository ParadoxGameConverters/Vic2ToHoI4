#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Countries/Equipment.h"
#include "src/OutHoi4/Countries/OutEquipment.h"



TEST(HoI4World_Countries_EquipmentTests, EquipmentIsAsConstructed)
{
	const HoI4::Equipment the_equipment("TAG", "test_equipment_1", "test variant", "has_dlc = \"test dlc\"", 42);

	std::ostringstream output;
	output << the_equipment;


	EXPECT_EQ(output.str(),
		 "if = {\n"
		 "\tlimit = { has_dlc = \"test dlc\" }\n"
		 "\tadd_equipment_to_stockpile = { type = test_equipment_1 variant = \"test variant\" amount = 42 producer = TAG "
		 "}\n"
		 "}\n");
}


TEST(HoI4World_Countries_EquipmentTests, ItemsCanBeSkipped)
{
	const HoI4::Equipment the_equipment("TAG", "test_equipment_1", std::nullopt, std::nullopt, 42);

	std::ostringstream output;
	output << the_equipment;


	EXPECT_EQ(output.str(), "add_equipment_to_stockpile = { type = test_equipment_1 amount = 42 producer = TAG }\n");
}