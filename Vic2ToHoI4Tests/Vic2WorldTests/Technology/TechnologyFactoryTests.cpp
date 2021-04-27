#include "V2World/Technology/TechnologyFactory.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"
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