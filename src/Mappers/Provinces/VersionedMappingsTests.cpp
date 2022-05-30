#include "Mappers/Provinces/VersionedMappings.h"
#include "Mappers/Provinces/VersionedMappingsFactory.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Mappers_Provinces_VersionedMappingsTests, Vic2ProvinceMappingsDefaultToEmpty)
{
	std::stringstream input;

	const auto versionedMappings = Mappers::VersionedMappings::Factory().importVersionedMappings(input);

	ASSERT_TRUE(versionedMappings->getVic2ToHoI4Mapping().empty());
}


TEST(Mappers_Provinces_VersionedMappingsTests, HoI4ProvinceMappingsDefaultToEmpty)
{
	std::stringstream input;

	const auto versionedMappings = Mappers::VersionedMappings::Factory().importVersionedMappings(input);

	ASSERT_TRUE(versionedMappings->getHoI4ToVic2Mapping().empty());
}


TEST(Mappers_Provinces_VersionedMappingsTests, EmptyMappingsAddNothing)
{
	std::stringstream input;
	input << "link = {}";

	const auto versionedMappings = Mappers::VersionedMappings::Factory().importVersionedMappings(input);

	ASSERT_TRUE(versionedMappings->getVic2ToHoI4Mapping().empty());
	ASSERT_TRUE(versionedMappings->getHoI4ToVic2Mapping().empty());
}


TEST(Mappers_Provinces_VersionedMappingsTests, ProvinceMappingsCanBeAdded)
{
	std::stringstream input;
	input << "link = { vic2 = 1 hoi4 = 1 hoi4 = 10 }\n";
	input << "link = { vic2 = 2 vic2 = 20 hoi4 = 2 }\n";
	input << "link = { vic2 = 3 }\n";
	input << "link = { hoi4 = 3 }\n";

	const auto versionedMappings = Mappers::VersionedMappings::Factory().importVersionedMappings(input);

	ASSERT_THAT(versionedMappings->getVic2ToHoI4Mapping(),
		 testing::UnorderedElementsAre(testing::Pair(1, std::vector{1, 10}),
			  testing::Pair(2, std::vector{2}),
			  testing::Pair(20, std::vector{2}),
			  testing::Pair(3, std::vector<int>{})));
	ASSERT_THAT(versionedMappings->getHoI4ToVic2Mapping(),
		 testing::UnorderedElementsAre(testing::Pair(1, std::vector{1}),
			  testing::Pair(10, std::vector{1}),
			  testing::Pair(2, std::vector{2, 20}),
			  testing::Pair(3, std::vector<int>{})));
}