#include "V2World/Map/Vic2ProvinceDefinitionImporter.h"
#include "V2World/Provinces/ProvinceBuilder.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"


TEST(Vic2World_Map_Vic2ProvinceDefinitionImporterTests, ExceptionThrownForMissingDefinitions)
{
	EXPECT_THROW(Vic2::importProvinceDefinitions("badfolder", {}), std::runtime_error);
}


TEST(Vic2World_Map_Vic2ProvinceDefinitionImporterTests, NoProvinceFromUndefinedColor)
{
	const auto definitions = Vic2::importProvinceDefinitions("ProvinceDefinition", {});

	const auto province = definitions.getProvinceFromColor(commonItems::Color(std::array{255, 255, 255}));
	EXPECT_FALSE(province);
}


TEST(Vic2World_Map_Vic2ProvinceDefinitionImporterTests, ProvinceFromDefinedColor)
{
	const auto definitions = Vic2::importProvinceDefinitions("ProvinceDefinition", {});

	const auto province = definitions.getProvinceFromColor(commonItems::Color(std::array<int, 3>{136, 0, 21}));
	ASSERT_TRUE(province);
	EXPECT_EQ(*province, 1);
}


TEST(Vic2World_Map_Vic2ProvinceDefinitionImporterTests, LandProvincesCanBeDetermined)
{
	const auto definitions = Vic2::importProvinceDefinitions("ProvinceDefinition",
		 {{1, Vic2::Province::Builder{}.setNumber(1).setIsLand().build()}});

	EXPECT_TRUE(definitions.isLandProvince(1));
	EXPECT_FALSE(definitions.isSeaProvince(1));
}


TEST(Vic2World_Map_Vic2ProvinceDefinitionImporterTests, SeaProvincesCanBeDetermined)
{
	const auto definitions =
		 Vic2::importProvinceDefinitions("ProvinceDefinition", {{1, Vic2::Province::Builder{}.setNumber(1).build()}});

	EXPECT_FALSE(definitions.isLandProvince(1));
	EXPECT_TRUE(definitions.isSeaProvince(1));
}