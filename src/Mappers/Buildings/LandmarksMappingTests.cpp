#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/Mappers/Buildings/LandmarksMappingFactory.h"
#include <sstream>



TEST(Mappers_Landmark_LandmarksMappingTests, ImportedItemsAreDefaulted)
{
	std::stringstream input;
	const auto mapping = Mappers::LandmarksMappingFactory().importMapping(input);

	EXPECT_EQ(0, mapping.location);
	EXPECT_FALSE(mapping.built);
}


TEST(Mappers_Landmark_LandmarksMappingTests, LocationCanBeSet)
{
	std::stringstream input;
	input << "= { location = 42 }";
	const auto mapping = Mappers::LandmarksMappingFactory().importMapping(input);

	EXPECT_EQ(42, mapping.location);
}


TEST(Mappers_Landmark_LandmarksMappingTests, BuiltCanBeSet)
{
	std::stringstream input;
	input << "= { built = yes }";
	const auto mapping = Mappers::LandmarksMappingFactory().importMapping(input);

	EXPECT_TRUE(mapping.built);
}