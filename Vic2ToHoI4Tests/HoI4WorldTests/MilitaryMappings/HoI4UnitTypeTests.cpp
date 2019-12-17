/*Copyright (c) 2019 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HOI4World/MilitaryMappings/HoI4UnitType.h"
#include <sstream>



TEST(HoI4World_HoI4UnitTypeTests, defaultUnitMapCategoryIsBlank)
{
	std::stringstream input;
	HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(std::string(""), theMap.getCategory());
}


TEST(HoI4World_HoI4UnitTypeTests, defaultUnitMapTypeIsBlank)
{
	std::stringstream input;
	HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(std::string(""), theMap.getType());
}


TEST(HoI4World_HoI4UnitTypeTests, defaultUnitMapEquipmentIsBlank)
{
	std::stringstream input;
	HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(std::string(""), theMap.getEquipment());
}


TEST(HoI4World_HoI4UnitTypeTests, defaultUnitMapSizeIsZero)
{
	std::stringstream input;
	HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(0, theMap.getSize());
}


TEST(HoI4World_HoI4UnitTypeTests, blankUnitMapCategoryRemainsBlank)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t}"
	);
	HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(std::string(""), theMap.getCategory());
}


TEST(HoI4World_HoI4UnitTypeTests, blankUnitMapTypeRemainsBlank)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t}"
	);
	HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(std::string(""), theMap.getType());
}


TEST(HoI4World_HoI4UnitTypeTests, blankUnitMapEquipmentRemainsBlank)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t}"
	);
	HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(std::string(""), theMap.getEquipment());
}


TEST(HoI4World_HoI4UnitTypeTests, blankUnitMapVersionRemainsBlank)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t}"
	);
	HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(std::string(""), theMap.getVersion());
}


TEST(HoI4World_HoI4UnitTypeTests, blankUnitMapSizeRemainsZero)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t}"
	);
	HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(0, theMap.getSize());
}


TEST(HoI4World_HoI4UnitTypeTests, UnitMapCategoryCanBeSet)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t\tcategory = land\n"\
		"\t\t\t}"
	);
	HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(std::string("land"), theMap.getCategory());
}


TEST(HoI4World_HoI4UnitTypeTests, UnitMapTypeCanBeSet)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t\ttype = infantry\n"\
		"\t\t\t}"
	);
	HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(std::string("infantry"), theMap.getType());
}


TEST(HoI4World_HoI4UnitTypeTests, UnitMapEquipmentCanBeSet)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t\tequipment = infantry_equipment_0\n"\
		"\t\t\t}"
	);
	HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(std::string("infantry_equipment_0"), theMap.getEquipment());
}


TEST(HoI4World_HoI4UnitTypeTests, UnitMapVersionCanBeSet)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t\tversion = \"Early Submarine\"\n"\
		"\t\t\t}"
	);
	HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(std::string("Early Submarine"), theMap.getVersion());
}


TEST(HoI4World_HoI4UnitTypeTests, UnitMapSizeCanBeSet)
{
	std::stringstream input(
		"= {\n"\
		"\t\t\t\tsize = 3\n"\
		"\t\t\t}"
	);
	HoI4::HoI4UnitType theMap(input);
	ASSERT_EQ(3, theMap.getSize());
}