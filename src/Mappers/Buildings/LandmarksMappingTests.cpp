#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/Mappers/Buildings/LandmarksMappingFactory.h"
#include <sstream>



TEST(Mappers_Landmark_LandmarksMappingTests, ImportedItemsAreDefaulted)
{
	std::stringstream input;
	const auto mapping = Mappers::LandmarksMappingFactory().importMapping(input);

	EXPECT_TRUE(mapping.locations.empty());
	EXPECT_FALSE(mapping.built);
}


TEST(Mappers_Landmark_LandmarksMappingTests, LocationsCanBeSet)
{
	std::stringstream input;
	input << "= { location = 42 location = 43 }";
	const auto mapping = Mappers::LandmarksMappingFactory().importMapping(input);

	EXPECT_THAT(mapping.locations, testing::UnorderedElementsAre(42, 43));
}


TEST(Mappers_Landmark_LandmarksMappingTests, BuiltCanBeSet)
{
	std::stringstream input;
	input << "= { built = yes }";
	const auto mapping = Mappers::LandmarksMappingFactory().importMapping(input);

	EXPECT_TRUE(mapping.built);
}