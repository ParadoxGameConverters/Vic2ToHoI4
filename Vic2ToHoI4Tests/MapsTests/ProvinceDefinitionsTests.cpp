#include "Maps/ProvinceDefinitions.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"



TEST(HoI4World_Map_GetIntFromColor, IntDefaultsToZero)
{
	EXPECT_EQ(Maps::getIntFromColor(commonItems::Color(std::array{0, 0, 0})), 0);
}


TEST(HoI4World_Map_GetIntFromColor, RedIsLeftShiftedBy16)
{
	EXPECT_EQ(Maps::getIntFromColor(commonItems::Color(std::array{0x42, 0, 0})), 0x42'00'00);
}


TEST(HoI4World_Map_GetIntFromColor, GreenIsLeftShiftedBy8)
{
	EXPECT_EQ(Maps::getIntFromColor(commonItems::Color(std::array{0, 0x42, 0})), 0x00'42'00);
}


TEST(HoI4World_Map_GetIntFromColor, BlueIsNotShifted)
{
	EXPECT_EQ(Maps::getIntFromColor(commonItems::Color(std::array{0, 0, 0x42})), 0x00'00'42);
}


TEST(Maps_ProvinceDefinitions, LandProvincesDefaultToEmpty)
{
	const Maps::ProvinceDefinitions provinceDefinitions({}, {}, {}, {});

	EXPECT_TRUE(provinceDefinitions.getLandProvinces().empty());
}


TEST(Maps_ProvinceDefinitions, LandProvincesAreReturned)
{
	const Maps::ProvinceDefinitions provinceDefinitions({1, 2, 3, 4, 5}, {}, {}, {});

	EXPECT_THAT(provinceDefinitions.getLandProvinces(), testing::UnorderedElementsAre(1, 2, 3, 4, 5));
}


TEST(Maps_ProvinceDefinitions, ProvincesCanBeShownAreNotLandProvinces)
{
	const Maps::ProvinceDefinitions provinceDefinitions({}, {}, {}, {});

	EXPECT_FALSE(provinceDefinitions.isLandProvince(1));
	EXPECT_FALSE(provinceDefinitions.isLandProvince(2));
}


TEST(Maps_ProvinceDefinitions, ProvincesCanBeShownAreLandProvinces)
{
	const Maps::ProvinceDefinitions provinceDefinitions({1, 2}, {}, {}, {});

	EXPECT_TRUE(provinceDefinitions.isLandProvince(1));
	EXPECT_TRUE(provinceDefinitions.isLandProvince(2));
}


TEST(Maps_ProvinceDefinitions, ProvincesCanBeShownAreNotSeaProvinces)
{
	const Maps::ProvinceDefinitions provinceDefinitions({}, {}, {}, {});

	EXPECT_FALSE(provinceDefinitions.isSeaProvince(1));
	EXPECT_FALSE(provinceDefinitions.isSeaProvince(2));
}


TEST(Maps_ProvinceDefinitions, ProvincesCanBeShownAreSeaProvinces)
{
	const Maps::ProvinceDefinitions provinceDefinitions({}, {1, 2}, {}, {});

	EXPECT_TRUE(provinceDefinitions.isSeaProvince(1));
	EXPECT_TRUE(provinceDefinitions.isSeaProvince(2));
}


TEST(Maps_ProvinceDefinitions, ColorWithNoProvinceReturnsNullopt)
{
	const Maps::ProvinceDefinitions provinceDefinitions({}, {}, {}, {});

	EXPECT_EQ(provinceDefinitions.getProvinceFromColor(commonItems::Color(std::array{0, 0, 0})), std::nullopt);
}


TEST(Maps_ProvinceDefinitions, ProvincesCanBeLookedUpByColor)
{
	const Maps::ProvinceDefinitions provinceDefinitions({}, {}, {}, {{{0x01'02'03, 1}, {0x10'20'30, 10}}});

	EXPECT_EQ(provinceDefinitions.getProvinceFromColor(commonItems::Color(std::array{1, 2, 3})), 1);
	EXPECT_EQ(provinceDefinitions.getProvinceFromColor(commonItems::Color(std::array{16, 32, 48})), 10);
}


TEST(Maps_ProvinceDefinitions, TerrainTypeDefaultsToEmpty)
{
	const Maps::ProvinceDefinitions provinceDefinitions({}, {}, {}, {});

	EXPECT_EQ(provinceDefinitions.getTerrainType(1), "");
}


TEST(Maps_ProvinceDefinitions, TerrainTypeCanBeLookedUp)
{
	const Maps::ProvinceDefinitions provinceDefinitions({}, {}, {{1, "test_terrain"}}, {});

	EXPECT_EQ(provinceDefinitions.getTerrainType(1), "test_terrain");
}