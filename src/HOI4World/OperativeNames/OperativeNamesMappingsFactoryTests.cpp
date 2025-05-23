#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/OperativeNames/OperativeNamesMappingsFactory.h"
#include <sstream>



TEST(HoI4World_OperativeNames_OperativeNamesMappingsFactoryTests, GenericOperativeNamesReturnedForNonCulture)
{
	const auto mappings = HoI4::OperativeNamesMappings::Factory().getMappings();

	ASSERT_EQ("GENERIC_ENG_OPERATIVE_CODENAME_HISTORICAL", mappings.getMatchingNamesSet("not_a_culture"));
}


TEST(HoI4World_OperativeNames_OperativeNamesMappingsFactoryTests, MatchingOperativeNamesReturnedForCulture)
{
	const auto mappings = HoI4::OperativeNamesMappings::Factory().getMappings();

	ASSERT_EQ("CHI_OPERATIVE_CODENAME_HISTORICAL", mappings.getMatchingNamesSet("beifaren"));
}