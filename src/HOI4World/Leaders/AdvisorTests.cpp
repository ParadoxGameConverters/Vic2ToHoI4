#include "src/HOI4World/Leaders/Advisor.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Leaders_AdmiralTests, TraitsDefaultToEmpty)
{
	std::stringstream input;
	const HoI4::Advisor theAdvisor("", input);

	ASSERT_TRUE(theAdvisor.getTraits().empty());
}


TEST(HoI4World_Leaders_AdmiralTests, TraitsCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ttraits = { trait_one trait_two }\n";
	input << "}";
	const HoI4::Advisor theAdvisor("", input);

	ASSERT_EQ(theAdvisor.getTraits().size(), 2);
	ASSERT_EQ(theAdvisor.getTraits()[0], "trait_one");
	ASSERT_EQ(theAdvisor.getTraits()[1], "trait_two");
}


TEST(HoI4World_Leaders_AdmiralTests, PictureDefaultsToEmpty)
{
	std::stringstream input;
	const HoI4::Advisor theAdvisor("", input);

	ASSERT_TRUE(theAdvisor.getPicture().empty());
}


TEST(HoI4World_Leaders_AdmiralTests, PictureCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tpicture = picture_text\n";
	input << "}";
	const HoI4::Advisor theAdvisor("", input);

	ASSERT_EQ(theAdvisor.getPicture(), "picture_text");
}


TEST(HoI4World_Leaders_AdmiralTests, IdeologyDefaultsToEmpty)
{
	std::stringstream input;
	const HoI4::Advisor theAdvisor("", input);

	ASSERT_TRUE(theAdvisor.getIdeology().empty());
}


TEST(HoI4World_Leaders_AdmiralTests, IdeologyCanBeSet)
{
	std::stringstream input;
	const HoI4::Advisor theAdvisor("ideology", input);

	ASSERT_EQ(theAdvisor.getIdeology(), "ideology");
}


TEST(HoI4World_Leaders_AdmiralTests, AdvisorsOrderedByIdeology)
{
	std::stringstream input;
	const HoI4::Advisor earlyAdvisor("earlyIdeology", input);
	const HoI4::Advisor lateAdvisor("lateIdeology", input);

	ASSERT_LT(earlyAdvisor, lateAdvisor);
}