#include "src/Maps/MapData.h"
#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"


TEST(Maps_MapData, ExceptionThrownForMissingProvincesBmp)
{
	const Maps::ProvinceDefinitions provinceDefinitions({}, {}, {}, {});
	ASSERT_THROW(const Maps::MapData mapData(provinceDefinitions, ""), std::runtime_error);
}


TEST(Maps_MapData, ExceptionThrownForMissingAdjacenciesCsv)
{
	const Maps::ProvinceDefinitions provinceDefinitions({}, {}, {}, {});
	ASSERT_THROW(const Maps::MapData mapData(provinceDefinitions, "maptests/nocsv"), std::runtime_error);
}


TEST(Maps_MapData, NoNeighborsForNonexistentProvince)
{
	const Maps::ProvinceDefinitions provinceDefinitions({}, {}, {}, {});
	const Maps::MapData mapData(provinceDefinitions, "maptests");

	EXPECT_THAT(mapData.getNeighbors(42), testing::UnorderedElementsAre());
}


TEST(Maps_MapData, NeighborDefinedFromBelow)
{
	const Maps::ProvinceDefinitions provinceDefinitions({},
		 {},
		 {},
		 {
			  {0x88'00'15, 1}, // the dark red one on top
			  {0x22'B1'4C, 3}, // the green one in the middle
		 });
	const Maps::MapData mapData(provinceDefinitions, "maptests");

	EXPECT_THAT(mapData.getNeighbors(1), testing::UnorderedElementsAre(3));
}


TEST(Maps_MapData, NeighborDefinedFromRight)
{
	const Maps::ProvinceDefinitions provinceDefinitions({},
		 {},
		 {},
		 {
			  {0xED'1C'24, 2}, // the red red one on the left
			  {0x22'B1'4C, 3}, // the green one in the middle
		 });
	const Maps::MapData mapData(provinceDefinitions, "maptests");

	EXPECT_THAT(mapData.getNeighbors(2), testing::UnorderedElementsAre(3));
}


TEST(Maps_MapData, NeighborDefinedFromLeft)
{
	const Maps::ProvinceDefinitions provinceDefinitions({},
		 {},
		 {},
		 {
			  {0x22'B1'4C, 3}, // the green one in the middle
			  {0xFF'7F'27, 4}, // the orange one on the right
		 });
	const Maps::MapData mapData(provinceDefinitions, "maptests");

	EXPECT_THAT(mapData.getNeighbors(4), testing::UnorderedElementsAre(3));
}


TEST(Maps_MapData, NeighborDefinedFromAbove)
{
	const Maps::ProvinceDefinitions provinceDefinitions({},
		 {},
		 {},
		 {
			  {0x22'B1'4C, 3}, // the green one in the middle
			  {0xFF'F2'00, 5}, // the yellow red one below
		 });
	const Maps::MapData mapData(provinceDefinitions, "maptests");

	EXPECT_THAT(mapData.getNeighbors(5), testing::UnorderedElementsAre(3));
}


TEST(Maps_MapData, NeighborDefinedFromNonImpassableAdjacency)
{
	const Maps::ProvinceDefinitions provinceDefinitions({}, {}, {}, {});
	const Maps::MapData mapData(provinceDefinitions, "maptests");

	EXPECT_THAT(mapData.getNeighbors(101), testing::UnorderedElementsAre(102));
	EXPECT_THAT(mapData.getNeighbors(254), testing::UnorderedElementsAre(271));
}


TEST(Maps_MapData, NeighborRemovedFromImpassableAdjacency)
{
	const Maps::ProvinceDefinitions provinceDefinitions({},
		 {},
		 {},
		 {
			  {0x3F'48'CC, 6}, // the indigo one on the far right
			  {0xA3'49'A4, 7}, // the purple one on the far right
		 });
	const Maps::MapData mapData(provinceDefinitions, "maptests");

	EXPECT_THAT(mapData.getNeighbors(6), testing::UnorderedElementsAre());
}


TEST(Maps_MapData, NoSpecifiedBorderForNonexistentProvince)
{
	const Maps::ProvinceDefinitions provinceDefinitions({}, {}, {}, {});
	const Maps::MapData mapData(provinceDefinitions, "maptests");

	EXPECT_EQ(mapData.getSpecifiedBorderCenter(42, 1), std::nullopt);
}


TEST(Maps_MapData, NoBorderForNonBorderingProvinces)
{
	const Maps::ProvinceDefinitions provinceDefinitions({},
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
	const Maps::MapData mapData(provinceDefinitions, "maptests");

	EXPECT_EQ(mapData.getSpecifiedBorderCenter(1, 5), std::nullopt);
}


TEST(Maps_MapData, SpecifiedBorderForBorderingProvinces)
{
	const Maps::ProvinceDefinitions provinceDefinitions({},
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
	const Maps::MapData mapData(provinceDefinitions, "maptests");

	const auto borderPoint = mapData.getSpecifiedBorderCenter(1, 3);
	ASSERT_TRUE(borderPoint);

	const Maps::Point expectedPoint{13, 591}; // y-axis is from the bottom
	EXPECT_EQ(*borderPoint, expectedPoint);
}


TEST(Maps_MapData, SpecifiedBorderForImpassableBorderProvinces)
{
	const Maps::ProvinceDefinitions provinceDefinitions({},
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
	const Maps::MapData mapData(provinceDefinitions, "maptests");

	const auto borderPoint = mapData.getSpecifiedBorderCenter(6, 7);
	ASSERT_TRUE(borderPoint);

	const Maps::Point expectedPoint{44, 586}; // y-axis is from the bottom
	EXPECT_EQ(*borderPoint, expectedPoint);
}


TEST(Maps_MapData, NoBorderForNonexistentProvince)
{
	const Maps::ProvinceDefinitions provinceDefinitions({}, {}, {}, {});
	const Maps::MapData mapData(provinceDefinitions, "maptests");

	EXPECT_EQ(mapData.getAnyBorderCenter(42), std::nullopt);
}


TEST(Maps_MapData, NoBorderForProvinceWithNoBorders)
{
	const Maps::ProvinceDefinitions provinceDefinitions({},
		 {},
		 {},
		 {
			  {0x00'A2'E8, 8}, // the blue province to the very far right
		 });
	const Maps::MapData mapData(provinceDefinitions, "maptests");

	EXPECT_EQ(mapData.getAnyBorderCenter(8), std::nullopt);
}


TEST(Maps_MapData, AnyBorderForBorderingProvinces)
{
	const Maps::ProvinceDefinitions provinceDefinitions({},
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
	const Maps::MapData mapData(provinceDefinitions, "maptests");

	const auto borderPoint = mapData.getAnyBorderCenter(3);
	ASSERT_TRUE(borderPoint);

	const Maps::Point expectedPoint{13, 590}; // y-axis is from the bottom
	EXPECT_EQ(*borderPoint, expectedPoint);
}


TEST(Maps_MapData, NoProvinceNumberForUndefinedPoint)
{
	const Maps::ProvinceDefinitions provinceDefinitions({}, {}, {}, {});
	const Maps::MapData mapData(provinceDefinitions, "maptests");

	EXPECT_EQ(mapData.getProvinceNumber({0, 0}), std::nullopt);
}


TEST(Maps_MapData, ProvinceNumberForDefinedPoint)
{
	const Maps::ProvinceDefinitions provinceDefinitions({},
		 {},
		 {},
		 {
			  {0x88'00'15, 1}, // the dark red one on top
		 });
	const Maps::MapData mapData(provinceDefinitions, "maptests");

	const auto provinceNumber = mapData.getProvinceNumber({13, 595});
	ASSERT_TRUE(provinceNumber);
	EXPECT_EQ(*provinceNumber, 1);
}


TEST(Maps_MapData, NoProvincePointsForUndefinedProvince)
{
	const Maps::ProvinceDefinitions provinceDefinitions({}, {}, {}, {});
	const Maps::MapData mapData(provinceDefinitions, "maptests");

	EXPECT_EQ(mapData.getProvincePoints(42), std::nullopt);
}


TEST(Maps_MapData, ProvincePointsForDefinedProvince)
{
	const Maps::ProvinceDefinitions provinceDefinitions({},
		 {},
		 {},
		 {
			  {0x88'00'15, 1}, // the dark red one on top
		 });
	const Maps::MapData mapData(provinceDefinitions, "maptests");

	const auto provincePoints = mapData.getProvincePoints(1);
	ASSERT_TRUE(provincePoints);

	Maps::Point expectedPoint{13, 595};
	EXPECT_EQ(provincePoints->getCentermostPoint(), expectedPoint);
}