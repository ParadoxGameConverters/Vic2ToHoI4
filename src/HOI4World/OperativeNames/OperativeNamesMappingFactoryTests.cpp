#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/OperativeNames/OperativeNamesMappingFactory.h"
#include <sstream>



class HoI4World_OperativeNames_OperativeNamesMappingFactoryTests: public testing::Test
{
  protected:
	HoI4World_OperativeNames_OperativeNamesMappingFactoryTests() = default;
	HoI4::OperativeNamesMappingFactory operativeNamesMappingFactory;
};


TEST_F(HoI4World_OperativeNames_OperativeNamesMappingFactoryTests, MappingsDefaultToNone)
{
	std::stringstream input;
	const auto mappings = operativeNamesMappingFactory.getMappings(input);

	ASSERT_TRUE(mappings.empty());
}


TEST_F(HoI4World_OperativeNames_OperativeNamesMappingFactoryTests, MappingsCanBeAdded)
{
	std::stringstream input;
	input << "{ codenames = CHI_OPERATIVE_CODENAME_HISTORICAL culture = beifaren }";
	const auto mappings = operativeNamesMappingFactory.getMappings(input);

	ASSERT_EQ(1, mappings.size());
	ASSERT_TRUE(mappings.contains("beifaren"));
	ASSERT_EQ("CHI_OPERATIVE_CODENAME_HISTORICAL", mappings.at("beifaren"));
}


TEST_F(HoI4World_OperativeNames_OperativeNamesMappingFactoryTests, MultipleMappingsCanBeAdded)
{
	std::stringstream input;
	input << "{ codenames = CHI_OPERATIVE_CODENAME_HISTORICAL culture = beifaren culture = nanfaren }";
	const auto mappings = operativeNamesMappingFactory.getMappings(input);

	ASSERT_EQ(2, mappings.size());
	ASSERT_TRUE(mappings.contains("beifaren"));
	ASSERT_EQ("CHI_OPERATIVE_CODENAME_HISTORICAL", mappings.at("beifaren"));
	ASSERT_TRUE(mappings.contains("nanfaren"));
	ASSERT_EQ("CHI_OPERATIVE_CODENAME_HISTORICAL", mappings.at("nanfaren"));
}


TEST_F(HoI4World_OperativeNames_OperativeNamesMappingFactoryTests, NoCultureNoMapping)
{
	std::stringstream input;
	input << "{ codenames = CHI_OPERATIVE_CODENAME_HISTORICAL }";
	const auto mappings = operativeNamesMappingFactory.getMappings(input);

	ASSERT_TRUE(mappings.empty());
}


TEST_F(HoI4World_OperativeNames_OperativeNamesMappingFactoryTests, NoCodenamesNoMapping)
{
	std::stringstream input;
	input << "{ culture = beifaren }";
	const auto mappings = operativeNamesMappingFactory.getMappings(input);

	ASSERT_TRUE(mappings.empty());
}