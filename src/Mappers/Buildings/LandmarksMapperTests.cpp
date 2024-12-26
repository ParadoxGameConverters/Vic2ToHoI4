#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/Mappers/Buildings/LandmarksMapperFactory.h"



TEST(Mappers_Landmark_LandmarksMapperTests, MappingsCanBeImported)
{
	const auto mapper = Mappers::LandmarksMapper::Factory().importLandmarksMapper();

	ASSERT_FALSE(mapper->getMappings().empty());
}