#include "external/common_items/ModLoader/ModFilesystem.h"
#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/Maps/MapData.h"


TEST(Maps_MapData, ExceptionThrownForMissingProvincesBmp)
{
	const commonItems::ModFilesystem mod_filesystem;
	const Maps::ProvinceDefinitions province_definitions({}, {}, {}, {});
	EXPECT_THROW(const Maps::MapData map_data(province_definitions, mod_filesystem), std::runtime_error);
}


TEST(Maps_MapData, ExceptionThrownForMissingAdjacenciesCsv)
{
	const commonItems::ModFilesystem mod_filesystem("maptests/nocsv", {});
	const Maps::ProvinceDefinitions province_definitions({}, {}, {}, {});
	EXPECT_THROW(const Maps::MapData map_data(province_definitions, mod_filesystem), std::runtime_error);
}


TEST(Maps_MapData, NoNeighborsForNonexistentProvince)
{
	const commonItems::ModFilesystem mod_filesystem("maptests", {});
	const Maps::ProvinceDefinitions province_definitions({}, {}, {}, {});
	const Maps::MapData map_data(province_definitions, mod_filesystem);

	EXPECT_THAT(map_data.GetNeighbors(42), testing::UnorderedElementsAre());
}


TEST(Maps_MapData, NeighborDefinedFromBelow)
{
	const commonItems::ModFilesystem mod_filesystem("maptests", {});
	const Maps::ProvinceDefinitions province_definitions({},
		 {},
		 {},
		 {
			  {0x88'00'15, 1}, // the dark red one on top
			  {0x22'B1'4C, 3}, // the green one in the middle
		 });
	const Maps::MapData map_data(province_definitions, mod_filesystem);

	EXPECT_THAT(map_data.GetNeighbors(1), testing::UnorderedElementsAre(3));
}


TEST(Maps_MapData, NeighborDefinedFromRight)
{
	const commonItems::ModFilesystem mod_filesystem("maptests", {});
	const Maps::ProvinceDefinitions province_definitions({},
		 {},
		 {},
		 {
			  {0xED'1C'24, 2}, // the red red one on the left
			  {0x22'B1'4C, 3}, // the green one in the middle
		 });
	const Maps::MapData map_data(province_definitions, mod_filesystem);

	EXPECT_THAT(map_data.GetNeighbors(2), testing::UnorderedElementsAre(3));
}


TEST(Maps_MapData, NeighborDefinedFromLeft)
{
	const commonItems::ModFilesystem mod_filesystem("maptests", {});
	const Maps::ProvinceDefinitions province_definitions({},
		 {},
		 {},
		 {
			  {0x22'B1'4C, 3}, // the green one in the middle
			  {0xFF'7F'27, 4}, // the orange one on the right
		 });
	const Maps::MapData map_data(province_definitions, mod_filesystem);

	EXPECT_THAT(map_data.GetNeighbors(4), testing::UnorderedElementsAre(3));
}


TEST(Maps_MapData, NeighborDefinedFromAbove)
{
	const commonItems::ModFilesystem mod_filesystem("maptests", {});
	const Maps::ProvinceDefinitions province_definitions({},
		 {},
		 {},
		 {
			  {0x22'B1'4C, 3}, // the green one in the middle
			  {0xFF'F2'00, 5}, // the yellow red one below
		 });
	const Maps::MapData map_data(province_definitions, mod_filesystem);

	EXPECT_THAT(map_data.GetNeighbors(5), testing::UnorderedElementsAre(3));
}


TEST(Maps_MapData, NeighborDefinedFromNonImpassableAdjacency)
{
	const commonItems::ModFilesystem mod_filesystem("maptests", {});
	const Maps::ProvinceDefinitions province_definitions({}, {}, {}, {});
	const Maps::MapData map_data(province_definitions, mod_filesystem);

	EXPECT_THAT(map_data.GetNeighbors(101), testing::UnorderedElementsAre(102));
	EXPECT_THAT(map_data.GetNeighbors(254), testing::UnorderedElementsAre(271));
}


TEST(Maps_MapData, NeighborRemovedFromImpassableAdjacency)
{
	const commonItems::ModFilesystem mod_filesystem("maptests", {});
	const Maps::ProvinceDefinitions province_definitions({},
		 {},
		 {},
		 {
			  {0x3F'48'CC, 6}, // the indigo one on the far right
			  {0xA3'49'A4, 7}, // the purple one on the far right
		 });
	const Maps::MapData map_data(province_definitions, mod_filesystem);

	EXPECT_THAT(map_data.GetNeighbors(6), testing::UnorderedElementsAre());
}


TEST(Maps_MapData, NoSpecifiedBorderForNonexistentProvince)
{
	const commonItems::ModFilesystem mod_filesystem("maptests", {});
	const Maps::ProvinceDefinitions province_definitions({}, {}, {}, {});
	const Maps::MapData map_data(province_definitions, mod_filesystem);

	EXPECT_EQ(map_data.GetSpecifiedBorderCenter(42, 1), std::nullopt);
}


TEST(Maps_MapData, NoBorderForNonBorderingProvinces)
{
	const commonItems::ModFilesystem mod_filesystem("maptests", {});
	const Maps::ProvinceDefinitions province_definitions({},
		 {},
		 {},
		 {
			  {0x88'00'15, 1}, // the dark red one on top
			  {0xED'1C'24, 2}, // the red red one on the left
			  {0x22'B1'4C, 3}, // the green one in the middle
			  {0xFF'7F'27, 4}, // the orange one on the right
			  {0xFF'F2'00, 5}, // the yellow red one below
			  {0x3F'48'CC, 6}, // the indigo one on the far right
			  {0xA3'49'A4, 7}, // the purple one on the far right
		 });
	const Maps::MapData map_data(province_definitions, mod_filesystem);

	EXPECT_EQ(map_data.GetSpecifiedBorderCenter(1, 5), std::nullopt);
}


TEST(Maps_MapData, SpecifiedBorderForBorderingProvinces)
{
	const commonItems::ModFilesystem mod_filesystem("maptests", {});
	const Maps::ProvinceDefinitions province_definitions({},
		 {},
		 {},
		 {
			  {0x88'00'15, 1}, // the dark red one on top
			  {0xED'1C'24, 2}, // the red red one on the left
			  {0x22'B1'4C, 3}, // the green one in the middle
			  {0xFF'7F'27, 4}, // the orange one on the right
			  {0xFF'F2'00, 5}, // the yellow red one below
			  {0x3F'48'CC, 6}, // the indigo one on the far right
			  {0xA3'49'A4, 7}, // the purple one on the far right
		 });
	const Maps::MapData map_data(province_definitions, mod_filesystem);

	const auto border_point = map_data.GetSpecifiedBorderCenter(1, 3);
	ASSERT_TRUE(border_point);

	constexpr Maps::Point expected_point{13, 591}; // y-axis is from the bottom
	EXPECT_EQ(*border_point, expected_point);
}


TEST(Maps_MapData, SpecifiedBorderForImpassableBorderProvinces)
{
	const commonItems::ModFilesystem mod_filesystem("maptests", {});
	const Maps::ProvinceDefinitions province_definitions({},
		 {},
		 {},
		 {
			  {0x88'00'15, 1}, // the dark red one on top
			  {0xED'1C'24, 2}, // the red red one on the left
			  {0x22'B1'4C, 3}, // the green one in the middle
			  {0xFF'7F'27, 4}, // the orange one on the right
			  {0xFF'F2'00, 5}, // the yellow red one below
			  {0x3F'48'CC, 6}, // the indigo one on the far right
			  {0xA3'49'A4, 7}, // the purple one on the far right
		 });
	const Maps::MapData map_data(province_definitions, mod_filesystem);

	const auto border_point = map_data.GetSpecifiedBorderCenter(6, 7);
	ASSERT_TRUE(border_point);

	constexpr Maps::Point expected_point{44, 586}; // y-axis is from the bottom
	EXPECT_EQ(*border_point, expected_point);
}


TEST(Maps_MapData, NoBorderForNonexistentProvince)
{
	const commonItems::ModFilesystem mod_filesystem("maptests", {});
	const Maps::ProvinceDefinitions province_definitions({}, {}, {}, {});
	const Maps::MapData map_data(province_definitions, mod_filesystem);

	EXPECT_EQ(map_data.GetAnyBorderCenter(42), std::nullopt);
}


TEST(Maps_MapData, NoBorderForProvinceWithNoBorders)
{
	const commonItems::ModFilesystem mod_filesystem("maptests", {});
	const Maps::ProvinceDefinitions province_definitions({},
		 {},
		 {},
		 {
			  {0x00'A2'E8, 8}, // the blue province to the very far right
		 });
	const Maps::MapData map_data(province_definitions, mod_filesystem);

	EXPECT_EQ(map_data.GetAnyBorderCenter(8), std::nullopt);
}


TEST(Maps_MapData, AnyBorderForBorderingProvinces)
{
	const commonItems::ModFilesystem mod_filesystem("maptests", {});
	const Maps::ProvinceDefinitions province_definitions({},
		 {},
		 {},
		 {
			  {0x88'00'15, 1}, // the dark red one on top
			  {0xED'1C'24, 2}, // the red red one on the left
			  {0x22'B1'4C, 3}, // the green one in the middle
			  {0xFF'7F'27, 4}, // the orange one on the right
			  {0xFF'F2'00, 5}, // the yellow red one below
			  {0x3F'48'CC, 6}, // the indigo one on the far right
			  {0xA3'49'A4, 7}, // the purple one on the far right
		 });
	const Maps::MapData map_data(province_definitions, mod_filesystem);

	const auto border_point = map_data.GetAnyBorderCenter(3);
	ASSERT_TRUE(border_point);

	constexpr Maps::Point expected_point{13, 590}; // y-axis is from the bottom
	EXPECT_EQ(*border_point, expected_point);
}


TEST(Maps_MapData, NoProvinceNumberForUndefinedPoint)
{
	const commonItems::ModFilesystem mod_filesystem("maptests", {});
	const Maps::ProvinceDefinitions province_definitions({}, {}, {}, {});
	const Maps::MapData map_data(province_definitions, mod_filesystem);

	EXPECT_EQ(map_data.GetProvinceNumber({0, 0}), std::nullopt);
}


TEST(Maps_MapData, ProvinceNumberForDefinedPoint)
{
	const commonItems::ModFilesystem mod_filesystem("maptests", {});
	const Maps::ProvinceDefinitions province_definitions({},
		 {},
		 {},
		 {
			  {0x88'00'15, 1}, // the dark red one on top
		 });
	const Maps::MapData map_data(province_definitions, mod_filesystem);

	const auto province_number = map_data.GetProvinceNumber({13, 595});
	ASSERT_TRUE(province_number);
	EXPECT_EQ(*province_number, 1);
}


TEST(Maps_MapData, NoProvincePointsForUndefinedProvince)
{
	const commonItems::ModFilesystem mod_filesystem("maptests", {});
	const Maps::ProvinceDefinitions province_definitions({}, {}, {}, {});
	const Maps::MapData map_data(province_definitions, mod_filesystem);

	EXPECT_EQ(map_data.GetProvincePoints(42), std::nullopt);
}


TEST(Maps_MapData, ProvincePointsForDefinedProvince)
{
	const commonItems::ModFilesystem mod_filesystem("maptests", {});
	const Maps::ProvinceDefinitions province_definitions({},
		 {},
		 {},
		 {
			  {0x88'00'15, 1}, // the dark red one on top
		 });
	const Maps::MapData map_data(province_definitions, mod_filesystem);

	const auto provincePoints = map_data.GetProvincePoints(1);
	ASSERT_TRUE(provincePoints);

	constexpr Maps::Point expected_point{13, 595};
	EXPECT_EQ(provincePoints->getCentermostPoint(), expected_point);
}