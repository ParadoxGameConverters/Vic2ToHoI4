#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Map/Railway.h"
#include <gmock/gmock-matchers.h>



using HoI4::Railway;



TEST(HoI4World_Map_Railway, LevelIsAsSet)
{
	const Railway railway(2, {1, 2});

	EXPECT_EQ(railway.GetLevel(), 2);
}


TEST(HoI4World_Map_Railway, ExceptionForTooFewProvinces)
{
	EXPECT_THROW(Railway railway(42, {}), std::runtime_error);
}


TEST(HoI4World_Map_Railway, ProvincesAreAsSet)
{
	const Railway railway(42, {1, 2, 3, 4, 5});
	EXPECT_THAT(railway.GetProvinces(), testing::ElementsAre(1, 2, 3, 4, 5));
}


TEST(HoI4World_Map_Railway, LengthIsEqualToNumberOfProvinces)
{
	const Railway railway(42, {1, 2, 3, 4, 5});
	EXPECT_EQ(railway.GetLength(), 5);
}