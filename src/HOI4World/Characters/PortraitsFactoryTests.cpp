#include "HOI4World/Characters/PortraitsFactory.h"
#include "gtest/gtest.h"
#include <gmock/gmock-matchers.h>
#include <sstream>



TEST(HoI4World_Characters_PortraitsFactory, ValuesAreDefault)
{
	std::stringstream input;

	const auto portraits = HoI4::PortraitsFactory().importPortraits(input);

	EXPECT_TRUE(portraits.empty());
}


TEST(HoI4World_Characters_PortraitsFactory, ValuesAreImported)
{
	std::stringstream input;
	input << "\t\t\tarmy={\n";
	input << "\t\t\t\tlarge=\"gfx/leaders/TAG/Portrait_TAG_test_army_portrait.dds\"\n";
	input << "\t\t\t\tsmall=\"gfx/interface/ideas/idea_TAG_test_army_portrait.dds\"\n";
	input << "\t\t\t}\n";
	input << "\t\t\tnavy={\n";
	input << "\t\t\t\tlarge=\"gfx/leaders/TAG/Portrait_TAG_test_navy_portrait.dds\"\n";
	input << "\t\t\t\tsmall=\"gfx/interface/ideas/idea_TAG_test_navy_portrait.dds\"\n";
	input << "\t\t\t}\n";
	input << "\t\t\tcivilian={\n";
	input << "\t\t\t\tlarge=\"gfx/leaders/TAG/Portrait_TAG_test_civilian_portrait.dds\"\n";
	input << "\t\t\t\tsmall=\"gfx/interface/ideas/idea_TAG_test_civilian_portrait.dds\"\n";
	input << "\t\t\t}\n";

	const auto portraits = HoI4::PortraitsFactory().importPortraits(input);

	EXPECT_THAT(portraits,
		 testing::ElementsAre(HoI4::Portrait("army", "large", "gfx/leaders/TAG/Portrait_TAG_test_army_portrait.dds"),
			  HoI4::Portrait("army", "small", "gfx/interface/ideas/idea_TAG_test_army_portrait.dds"),
			  HoI4::Portrait("navy", "large", "gfx/leaders/TAG/Portrait_TAG_test_navy_portrait.dds"),
			  HoI4::Portrait("navy", "small", "gfx/interface/ideas/idea_TAG_test_navy_portrait.dds"),
			  HoI4::Portrait("civilian", "large", "gfx/leaders/TAG/Portrait_TAG_test_civilian_portrait.dds"),
			  HoI4::Portrait("civilian", "small", "gfx/interface/ideas/idea_TAG_test_civilian_portrait.dds")));
}