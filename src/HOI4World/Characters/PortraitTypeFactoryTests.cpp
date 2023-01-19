#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Characters/PortraitTypeFactory.h"



TEST(HoI4World_Characters_PortraitTypeFactory, ValuesAreDefault)
{
	std::stringstream input;

	const auto portraits = HoI4::PortraitTypeFactory().importPortraits("", input);

	EXPECT_TRUE(portraits.empty());
}


TEST(HoI4World_Characters_PortraitTypeFactory, ValuesCanBeImported)
{
	std::stringstream input;
	input << "\t\ttest_size=\"GFX_test_portrait_definition\"";
	input << "\t\ttest_size_two=\"GFX_test_portrait_definition_two\"";

	const auto portraits = HoI4::PortraitTypeFactory().importPortraits("portrait_type", input);

	EXPECT_THAT(portraits,
		 testing::ElementsAre(HoI4::Portrait("portrait_type", "test_size", "GFX_test_portrait_definition"),
			  HoI4::Portrait("portrait_type", "test_size_two", "GFX_test_portrait_definition_two")));
}