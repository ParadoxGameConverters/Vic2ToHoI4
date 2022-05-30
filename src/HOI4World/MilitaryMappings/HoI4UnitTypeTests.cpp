#include "HOI4World/MilitaryMappings/HoI4UnitType.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_MilitaryMappings_HoI4UnitTypeTests, defaultUnitMapCategoryIsBlank)
{
	std::stringstream input;
	const HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(std::string(), theMap.getCategory());
}


TEST(HoI4World_MilitaryMappings_HoI4UnitTypeTests, defaultUnitMapTypeIsBlank)
{
	std::stringstream input;
	const HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(std::string(), theMap.getType());
}


TEST(HoI4World_MilitaryMappings_HoI4UnitTypeTests, defaultUnitMapEquipmentIsBlank)
{
	std::stringstream input;
	const HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(std::string(), theMap.getEquipment());
}


TEST(HoI4World_MilitaryMappings_HoI4UnitTypeTests, defaultUnitMapSizeIsZero)
{
	std::stringstream input;
	const HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(0, theMap.getSize());
}


TEST(HoI4World_MilitaryMappings_HoI4UnitTypeTests, UnitMapCategoryCanBeSet)
{
	std::stringstream input(
		 "= {\n"
		 "\t\t\t\tcategory = land\n"
		 "\t\t\t}");
	const HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(std::string("land"), theMap.getCategory());
}


TEST(HoI4World_MilitaryMappings_HoI4UnitTypeTests, UnitMapTypeCanBeSet)
{
	std::stringstream input(
		 "= {\n"
		 "\t\t\t\ttype = infantry\n"
		 "\t\t\t}");
	const HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(std::string("infantry"), theMap.getType());
}


TEST(HoI4World_MilitaryMappings_HoI4UnitTypeTests, UnitMapEquipmentCanBeSet)
{
	std::stringstream input(
		 "= {\n"
		 "\t\t\t\tequipment = infantry_equipment_0\n"
		 "\t\t\t}");
	const HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(std::string("infantry_equipment_0"), theMap.getEquipment());
}


TEST(HoI4World_MilitaryMappings_HoI4UnitTypeTests, UnitMapVersionCanBeSet)
{
	std::stringstream input(
		 "= {\n"
		 "\t\t\t\tversion = \"Early Submarine\"\n"
		 "\t\t\t}");
	const HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(std::string("Early Submarine"), theMap.getVersion());
}


TEST(HoI4World_MilitaryMappings_HoI4UnitTypeTests, UnitMapSizeCanBeSet)
{
	std::stringstream input(
		 "= {\n"
		 "\t\t\t\tsize = 3\n"
		 "\t\t\t}");
	const HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(3, theMap.getSize());
}