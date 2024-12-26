#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/Mappers/Buildings/LandmarksMappingFactory.h"
#include <sstream>



TEST(Mappers_Landmark_LandmarksMappingTests, LandmarkDefaultsToEmpty)
{
	std::stringstream input;
	const auto mapping = Mappers::LandmarksMappingFactory().importMapping(input);

	ASSERT_TRUE(mapping->building.empty());
}


TEST(Mappers_Landmark_LandmarksMappingTests, LandmarkCanBeSet)
{
	std::stringstream input;
	input << "= { building = landmark_test }";
	const auto mapping = Mappers::LandmarksMappingFactory().importMapping(input);

	ASSERT_EQ("landmark_test", mapping->building);
}


TEST(Mappers_Landmark_LandmarksMappingTests, LocationDefaultsToZero)
{
	std::stringstream input;
	const auto mapping = Mappers::LandmarksMappingFactory().importMapping(input);

	ASSERT_EQ(0, mapping->location);
}


TEST(Mappers_Landmark_LandmarksMappingTests, LocationCanBeSet)
{
	std::stringstream input;
	input << "= { location = 42 }";
	const auto mapping = Mappers::LandmarksMappingFactory().importMapping(input);

	ASSERT_EQ(42, mapping->location);
}