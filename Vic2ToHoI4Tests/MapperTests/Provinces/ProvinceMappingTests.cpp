#include "Mappers/Provinces/ProvinceMapping.h"
#include "Mappers/Provinces/ProvinceMappingFactory.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Mappers_Provinces_ProvinceMappingTests, Vic2ProvincesDefaultsToZero)
{
	std::stringstream input;

	const auto mapping = Mappers::ProvinceMapping::Factory().importProvinceMapping(input);

	ASSERT_THAT(mapping->getVic2Provinces(), testing::ElementsAre(0));
}


TEST(Mappers_Provinces_ProvinceMappingTests, Vic2ProvincesCanBeAdded)
{
	std::stringstream input;
	input << "= { vic2 = 42 vic2 = 144 }";

	const auto mapping = Mappers::ProvinceMapping::Factory().importProvinceMapping(input);

	ASSERT_THAT(mapping->getVic2Provinces(), testing::ElementsAre(42, 144));
}


TEST(Mappers_Provinces_ProvinceMappingTests, HoI4ProvincesDefaultsToZero)
{
	std::stringstream input;

	const auto mapping = Mappers::ProvinceMapping::Factory().importProvinceMapping(input);

	ASSERT_THAT(mapping->getHoI4Provinces(), testing::ElementsAre(0));
}


TEST(Mappers_Provinces_ProvinceMappingTests, HoI4ProvincesCanBeAdded)
{
	std::stringstream input;
	input << "= { hoi4 = 42 hoi4 = 144 }";

	const auto mapping = Mappers::ProvinceMapping::Factory().importProvinceMapping(input);

	ASSERT_THAT(mapping->getHoI4Provinces(), testing::ElementsAre(42, 144));
}