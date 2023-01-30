#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/Mappers/CountryName/CountryNameMapperFactory.h"
#include <sstream>



TEST(Mappers_CountryName_CountryNameMapperTests, NonMatchReturnsNullopt)
{
	const auto mapper = Mappers::CountryNameMapper::Factory().importCountryNameMapper();

	ASSERT_EQ(std::nullopt, mapper->getVic2Government("non_match", "TAG"));
}


TEST(Mappers_CountryName_CountryNameMapperTests, MatchingGovernmentIsReturned)
{
	const auto mapper = Mappers::CountryNameMapper::Factory().importCountryNameMapper();

	ASSERT_EQ("matching_vic2_gov", mapper->getVic2Government("match", "TAG"));
}


TEST(Mappers_CountryName_CountryNameMapperTests, IfRequiredTagNotPresentReturnsNullopt)
{
	const auto mapper = Mappers::CountryNameMapper::Factory().importCountryNameMapper();

	ASSERT_EQ(std::nullopt, mapper->getVic2Government("tag_required", "NON"));
}


TEST(Mappers_CountryName_CountryNameMapperTests, IfRequiredTagPresentReturnsGovernment)
{
	const auto mapper = Mappers::CountryNameMapper::Factory().importCountryNameMapper();

	ASSERT_EQ("matching_specific_vic2_gov", mapper->getVic2Government("tag_required", "TAG"));
}