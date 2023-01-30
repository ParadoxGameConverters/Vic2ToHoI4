#include "external/common_items/ModLoader/ModFilesystem.h"
#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/Map/Vic2ProvinceDefinitionImporter.h"
#include "src/V2World/Provinces/ProvinceBuilder.h"


TEST(Vic2World_Map_Vic2ProvinceDefinitionImporterTests, ExceptionThrownForMissingDefinitions)
{
	const commonItems::ModFilesystem mod_filesystem("badfolder", {});
	EXPECT_THROW(Vic2::ImportProvinceDefinitions(mod_filesystem, {}), std::runtime_error);
}


TEST(Vic2World_Map_Vic2ProvinceDefinitionImporterTests, NoProvinceFromUndefinedColor)
{
	const commonItems::ModFilesystem mod_filesystem("ProvinceDefinition", {});
	const auto definitions = Vic2::ImportProvinceDefinitions(mod_filesystem, {});

	const auto province = definitions.getProvinceFromColor(commonItems::Color(std::array{255, 255, 255}));
	EXPECT_FALSE(province);
}


TEST(Vic2World_Map_Vic2ProvinceDefinitionImporterTests, ProvinceFromDefinedColor)
{
	const commonItems::ModFilesystem mod_filesystem("ProvinceDefinition", {});
	const auto definitions = Vic2::ImportProvinceDefinitions(mod_filesystem, {});

	const auto province = definitions.getProvinceFromColor(commonItems::Color(std::array<int, 3>{136, 0, 21}));
	ASSERT_TRUE(province);
	EXPECT_EQ(*province, 1);
}


TEST(Vic2World_Map_Vic2ProvinceDefinitionImporterTests, LandProvincesCanBeDetermined)
{
	const commonItems::ModFilesystem mod_filesystem("ProvinceDefinition", {});
	const auto definitions = Vic2::ImportProvinceDefinitions(mod_filesystem,
		 {{1, Vic2::Province::Builder{}.setNumber(1).setIsLand().build()}});

	EXPECT_TRUE(definitions.isLandProvince(1));
	EXPECT_FALSE(definitions.isSeaProvince(1));
}


TEST(Vic2World_Map_Vic2ProvinceDefinitionImporterTests, SeaProvincesCanBeDetermined)
{
	const commonItems::ModFilesystem mod_filesystem("ProvinceDefinition", {});
	const auto definitions =
		 Vic2::ImportProvinceDefinitions(mod_filesystem, {{1, Vic2::Province::Builder{}.setNumber(1).build()}});

	EXPECT_FALSE(definitions.isLandProvince(1));
	EXPECT_TRUE(definitions.isSeaProvince(1));
}