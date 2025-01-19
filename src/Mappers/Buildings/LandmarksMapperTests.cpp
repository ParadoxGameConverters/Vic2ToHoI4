#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/Mappers/Buildings/LandmarksMapper.h"
#include "src/Mappers/Buildings/LandmarksMapping.h"



TEST(Mappers_Landmark_LandmarksMapperTests, MappingsCanBeImported)
{
	const auto mapper = Mappers::LandmarksMapper();

	EXPECT_THAT(mapper.getMappings(),
		 testing::UnorderedElementsAre(testing::Pair("landmark_test", Mappers::LandmarksMapping{42, true}),
			  testing::Pair("landmark_unbuilt", Mappers::LandmarksMapping{42, false})));
}