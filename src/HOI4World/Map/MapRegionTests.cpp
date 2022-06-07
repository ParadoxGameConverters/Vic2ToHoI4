#include "src/HOI4World/Map/MapRegion.h"
#include "gtest/gtest.h"



TEST(HoI4World_Map_Region, IdDefaultsToZero)
{
	std::stringstream input;
	const HoI4::MapRegion region(input);

	ASSERT_EQ(0, region.getID());
}


TEST(HoI4World_Map_Region, IdCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tid = 42\n";
	input << "}";
	const HoI4::MapRegion region(input);

	ASSERT_EQ(42, region.getID());
}


TEST(HoI4World_Map_Region, NameDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::MapRegion region(input);

	ASSERT_TRUE(region.takeName().empty());
}


TEST(HoI4World_Map_Region, NameCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tname = region_name\n";
	input << "}";
	HoI4::MapRegion region(input);

	ASSERT_EQ("region_name", region.takeName());
}


TEST(HoI4World_Map_Region, ProvincesDefaultToEmpty)
{
	std::stringstream input;
	HoI4::MapRegion region(input);

	ASSERT_TRUE(region.takeProvinces().empty());
}


TEST(HoI4World_Map_Region, ProvincesCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tprovinces = { 1 2 3 }\n";
	input << "}";
	HoI4::MapRegion region(input);

	const std::vector<int> expectedProvinces{1, 2, 3};
	ASSERT_EQ(expectedProvinces, region.takeProvinces());
}


TEST(HoI4World_Map_Region, NavalTerrainDefaultsToNullopt)
{
	std::stringstream input;
	HoI4::MapRegion region(input);

	ASSERT_EQ(std::nullopt, region.takeNavalTerrain());
}


TEST(HoI4World_Map_Region, NavalTerrainCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tnaval_terrain = ocean\n";
	input << "}";
	HoI4::MapRegion region(input);

	std::vector<int> expectedProvinces{1, 2, 3};
	ASSERT_EQ("ocean", region.takeNavalTerrain());
}


TEST(HoI4World_Map_Region, StaticModiersDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::MapRegion region(input);

	ASSERT_TRUE(region.takeStaticModifiers().empty());
}


TEST(HoI4World_Map_Region, StaticModifiersCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tstatic_modifiers = {\n";
	input << "\t\tmodifier_one = foo\n";
	input << "\t\tmodifier_two = bar\n";
	input << "\t}\n";
	input << "}";
	HoI4::MapRegion region(input);

	const std::map<std::string, std::string> expectedModifiers{{"modifier_one", "foo"}, {"modifier_two", "bar"}};
	ASSERT_EQ(expectedModifiers, region.takeStaticModifiers());
}


TEST(HoI4World_Map_Region, WeatherDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::MapRegion region(input);

	ASSERT_TRUE(region.takeWeather().empty());
}


TEST(HoI4World_Map_Region, WeatherCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tweather = { the_weather }\n";
	input << "}";
	HoI4::MapRegion region(input);

	ASSERT_EQ("= { the_weather }", region.takeWeather());
}