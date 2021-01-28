#include "Configuration.h"
#include "Mappers/Provinces/ProvinceMapper.h"
#include "Mappers/Provinces/ProvinceMapperFactory.h"
#include "V2World/Mods/ModBuilder.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Mappers_Provinces_ProvinceMapperTests, ProvinceMappingsCanBeImported)
{
	const auto province_mappings =
		 Mappers::ProvinceMapper::Factory(*Configuration::Builder().setHoI4Path("./empty_definition/").build())
			  .importProvinceMapper(*Configuration::Builder().build());

	ASSERT_THAT(province_mappings->getVic2ToHoI4ProvinceMapping(1), testing::ElementsAre(1, 10));
	ASSERT_THAT(province_mappings->getVic2ToHoI4ProvinceMapping(2), testing::ElementsAre(2));
	ASSERT_THAT(province_mappings->getVic2ToHoI4ProvinceMapping(20), testing::ElementsAre(2));
	ASSERT_THAT(province_mappings->getVic2ToHoI4ProvinceMapping(3), testing::ElementsAre());
	ASSERT_THAT(province_mappings->getVic2ToHoI4ProvinceMapping(4), testing::ElementsAre());
	ASSERT_THAT(province_mappings->getHoI4ToVic2ProvinceMapping(1), testing::ElementsAre(1));
	ASSERT_THAT(province_mappings->getHoI4ToVic2ProvinceMapping(10), testing::ElementsAre(1));
	ASSERT_THAT(province_mappings->getHoI4ToVic2ProvinceMapping(2), testing::ElementsAre(2, 20));
	ASSERT_THAT(province_mappings->getHoI4ToVic2ProvinceMapping(3), testing::ElementsAre());
	ASSERT_THAT(province_mappings->getHoI4ToVic2ProvinceMapping(4), testing::ElementsAre());
	ASSERT_TRUE(province_mappings->isVic2ProvinceMapped(1));
	ASSERT_TRUE(province_mappings->isVic2ProvinceMapped(2));
	ASSERT_TRUE(province_mappings->isVic2ProvinceMapped(20));
	ASSERT_TRUE(province_mappings->isVic2ProvinceMapped(3));
	ASSERT_FALSE(province_mappings->isVic2ProvinceMapped(4));
}


TEST(Mappers_Provinces_ProvinceMapperTests, ProvinceMappingsCanBeImportedFromMods)
{
	const auto province_mappings =
		 Mappers::ProvinceMapper::Factory(*Configuration::Builder().setHoI4Path("./empty_definition/").build())
			  .importProvinceMapper(*Configuration::Builder()
												  .addVic2Mod(*Vic2::Mod::Builder().setName("no_mappings_mod").build())
												  .addVic2Mod(*Vic2::Mod::Builder().setName("mod").build())
												  .build());

	ASSERT_THAT(province_mappings->getVic2ToHoI4ProvinceMapping(5), testing::ElementsAre(5, 50));
	ASSERT_THAT(province_mappings->getVic2ToHoI4ProvinceMapping(6), testing::ElementsAre(6));
	ASSERT_THAT(province_mappings->getVic2ToHoI4ProvinceMapping(60), testing::ElementsAre(6));
	ASSERT_THAT(province_mappings->getVic2ToHoI4ProvinceMapping(7), testing::ElementsAre());
	ASSERT_THAT(province_mappings->getVic2ToHoI4ProvinceMapping(8), testing::ElementsAre());
	ASSERT_THAT(province_mappings->getHoI4ToVic2ProvinceMapping(5), testing::ElementsAre(5));
	ASSERT_THAT(province_mappings->getHoI4ToVic2ProvinceMapping(50), testing::ElementsAre(5));
	ASSERT_THAT(province_mappings->getHoI4ToVic2ProvinceMapping(6), testing::ElementsAre(6, 60));
	ASSERT_THAT(province_mappings->getHoI4ToVic2ProvinceMapping(7), testing::ElementsAre());
	ASSERT_THAT(province_mappings->getHoI4ToVic2ProvinceMapping(8), testing::ElementsAre());
	ASSERT_TRUE(province_mappings->isVic2ProvinceMapped(5));
	ASSERT_TRUE(province_mappings->isVic2ProvinceMapped(6));
	ASSERT_TRUE(province_mappings->isVic2ProvinceMapped(60));
	ASSERT_TRUE(province_mappings->isVic2ProvinceMapped(7));
	ASSERT_FALSE(province_mappings->isVic2ProvinceMapped(8));
}


TEST(Mappers_Provinces_ProvinceMapperTests, MissingMapDefinitionThrowsException)
{
	ASSERT_THROW(const auto province_mappings =
						  Mappers::ProvinceMapper::Factory(*Configuration::Builder().setHoI4Path("./no_definition/").build())
								.importProvinceMapper(*Configuration::Builder().build()),
		 std::runtime_error);
}


TEST(Mappers_Provinces_ProvinceMapperTests, BadLineInMapDefinitionLogsWarning)
{
	std::stringstream log;
	auto stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const auto province_mappings =
		 Mappers::ProvinceMapper::Factory(*Configuration::Builder().setHoI4Path("./bad_line_definition/").build())
			  .importProvinceMapper(*Configuration::Builder().build());
	std::cout.rdbuf(stdOutBuf);

	ASSERT_EQ(
		 "    [INFO] Parsing province mappings\n"
		 " [WARNING] Bad line in /map/definition.csv: bad_line;0;0;0;land;false;unknown;0\n",
		 log.str());
}


TEST(Mappers_Provinces_ProvinceMapperTests, MissingHoI4ProvinceMappingLogsWarning)
{
	std::stringstream log;
	auto stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const auto province_mappings =
		 Mappers::ProvinceMapper::Factory(*Configuration::Builder().setHoI4Path("./missing_definition/").build())
			  .importProvinceMapper(*Configuration::Builder().build());
	const auto _ = province_mappings->getHoI4ToVic2ProvinceMapping(12);

	std::cout.rdbuf(stdOutBuf);

	ASSERT_EQ(
		 "    [INFO] Parsing province mappings\n"
		 " [WARNING] No mapping for HoI4 province 12\n"
		 " [WARNING] No mapping found for HoI4 province 12\n",
		 log.str());
}


TEST(Mappers_Provinces_ProvinceMapperTests, MissingVic2ProvinceMappingLogsWarning)
{
	const auto province_mappings =
		 Mappers::ProvinceMapper::Factory(*Configuration::Builder().setHoI4Path("./empty_definition/").build())
			  .importProvinceMapper(*Configuration::Builder().build());

	std::stringstream log;
	auto stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const auto _ = province_mappings->getVic2ToHoI4ProvinceMapping(12);

	std::cout.rdbuf(stdOutBuf);

	ASSERT_EQ(" [WARNING] No mapping found for Vic2 province 12\n", log.str());
}


TEST(Mappers_Provinces_ProvinceMapperTests, NoLoggingWhenAllProvincesMapped)
{
	std::stringstream log;
	auto stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const auto province_mappings =
		 Mappers::ProvinceMapper::Factory(*Configuration::Builder().setHoI4Path("./good_definition/").build())
			  .importProvinceMapper(*Configuration::Builder().build());
	std::cout.rdbuf(stdOutBuf);

	ASSERT_EQ("    [INFO] Parsing province mappings\n", log.str());
}