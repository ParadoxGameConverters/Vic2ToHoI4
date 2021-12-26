#include "HOI4World/Characters/PortraitFactory.h"
#include "gtest/gtest.h"



TEST(HoI4World_Characters_PortraitFactory, ValuesAreDefault)
{
	std::stringstream input;

	const auto portrait = HoI4::PortraitFactory().importPortrait("", input);

	EXPECT_TRUE(portrait.getType().empty());
	EXPECT_TRUE(portrait.getSize().empty());
	EXPECT_TRUE(portrait.getDefinition().empty());
}


TEST(HoI4World_Characters_PortraitFactory, ValuesCanBeImported)
{
	std::stringstream input;
	input << "\t\ttest_size=\"GFX_test_portrait_definition\"";

	const auto portrait = HoI4::PortraitFactory().importPortrait("portrait_type", input);

	EXPECT_EQ(portrait.getType(), "portrait_type");
	EXPECT_EQ(portrait.getSize(), "test_size");
	EXPECT_EQ(portrait.getDefinition(), "GFX_test_portrait_definition");
}