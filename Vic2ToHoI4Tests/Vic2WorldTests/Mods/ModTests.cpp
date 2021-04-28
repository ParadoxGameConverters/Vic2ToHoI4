#include "V2World/Mods/ModBuilder.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"



TEST(Vic2World_Mods_ModTests, ModsWithEqualNamesAreEqual)
{
	const auto modOne = Vic2::Mod::Builder().setName("test_name").build();
	const auto modTwo = Vic2::Mod::Builder().setName("test_name").build();

	ASSERT_EQ(*modOne, *modTwo);
}


TEST(Vic2World_Mods_ModTests, ModsWithUnequalNamesAreUnequal)
{
	const auto modOne = Vic2::Mod::Builder().setName("test_name").build();
	const auto modTwo = Vic2::Mod::Builder().setName("test_name2").build();

	ASSERT_NE(*modOne, *modTwo);
}