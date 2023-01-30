#include "external/common_items/external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/Technology/TechnologyFactory.h"
#include <sstream>



TEST(Vic2World_Technologys_TechnologyFactoryTests, TechsDefaultToEmpty)
{
	std::stringstream input;
	const auto techs = Vic2::TechnologyFactory().importTechnologies(input);

	ASSERT_TRUE(techs.empty());
}


TEST(Vic2World_Technologys_TechnologyFactoryTests, TechsAreImported)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ttech_one = { blah blah blah }\n";
	input << "\ttech_two = { blah blah blah }\n";
	input << "}";
	const auto techs = Vic2::TechnologyFactory().importTechnologies(input);

	ASSERT_THAT(techs, testing::ElementsAre("tech_one", "tech_two"));
}