#include "src/HOI4World/Decisions/IdeologicalDecisions.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Decisions_IdeologicalDecisionsTests, defaultsToEmptyList)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	const HoI4::IdeologicalDecisions ideologicalDecisions(input);

	ASSERT_TRUE(ideologicalDecisions.getCategories().empty());
}


TEST(HoI4World_Decisions_IdeologicalDecisionsTests, categoriesCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tcategoryOne = {}\n";
	input << "\tcategoryTwo = {}\n";
	input << "}";
	const HoI4::IdeologicalDecisions ideologicalDecisions(input);

	ASSERT_EQ(ideologicalDecisions.getCategories().size(), 2);
}


TEST(HoI4World_Decisions_IdeologicalDecisionsTests, handlesNoRequiredIdeologies)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	HoI4::IdeologicalDecisions ideologicalDecisions(input);

	const std::set<std::string> majorIdeologies;
	ASSERT_TRUE(ideologicalDecisions.requiredIdeologiesExist(majorIdeologies));
}


TEST(HoI4World_Decisions_IdeologicalDecisionsTests, falseIfRequiredIdeologyMissing)
{
	std::stringstream input;
	input << "= {\n";
	input << "\trequired_ideologies = {\n";
	input << "\t\tabsolutism\n";
	input << "\t}";
	input << "}";
	HoI4::IdeologicalDecisions ideologicalDecisions(input);

	const std::set<std::string> majorIdeologies;
	ASSERT_FALSE(ideologicalDecisions.requiredIdeologiesExist(majorIdeologies));
}


TEST(HoI4World_Decisions_IdeologicalDecisionsTests, trueIfRequiredIdeologyPresent)
{
	std::stringstream input;
	input << "= {\n";
	input << "\trequired_ideologies = {\n";
	input << "\t\tabsolutism\n";
	input << "\t}";
	input << "}";
	HoI4::IdeologicalDecisions ideologicalDecisions(input);

	std::set<std::string> majorIdeologies;
	majorIdeologies.insert("absolutism");
	ASSERT_TRUE(ideologicalDecisions.requiredIdeologiesExist(majorIdeologies));
}


TEST(HoI4World_Decisions_IdeologicalDecisionsTests, falseIfAnyRequiredIdeologyMissing)
{
	std::stringstream input;
	input << "= {\n";
	input << "\trequired_ideologies = {\n";
	input << "\t\tabsolutism\n";
	input << "\t\tdemocracy\n";
	input << "\t}";
	input << "}";
	HoI4::IdeologicalDecisions ideologicalDecisions(input);

	std::set<std::string> majorIdeologies;
	majorIdeologies.insert("absolutism");
	ASSERT_FALSE(ideologicalDecisions.requiredIdeologiesExist(majorIdeologies));
}


TEST(HoI4World_Decisions_IdeologicalDecisionsTests, trueIfAllRequiredIdeologiesPresent)
{
	std::stringstream input;
	input << "= {\n";
	input << "\trequired_ideologies = {\n";
	input << "\t\tabsolutism\n";
	input << "\t\tdemocracy\n";
	input << "\t}";
	input << "}";
	HoI4::IdeologicalDecisions ideologicalDecisions(input);

	std::set<std::string> majorIdeologies;
	majorIdeologies.insert("absolutism");
	majorIdeologies.insert("democracy");
	ASSERT_TRUE(ideologicalDecisions.requiredIdeologiesExist(majorIdeologies));
}