#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Ideas/IdeaGroup.h"
#include <sstream>



TEST(HoI4World_Ideas_IdeaGroupTests, NameIsAsSet)
{
	std::stringstream input;
	const HoI4::IdeaGroup theIdeaGroup("theName", input);

	ASSERT_EQ("theName", theIdeaGroup.getName());
}


TEST(HoI4World_Ideas_IdeaGroupTests, DefaultsAreAllEmpty)
{
	std::stringstream input;
	const HoI4::IdeaGroup theIdeaGroup("theName", input);

	std::stringstream actualOutput;
	actualOutput << theIdeaGroup;

	std::stringstream expectedOutput;
	expectedOutput << "\ttheName = {\n";
	expectedOutput << "\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaGroupTests, LawCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tlaw = yes\n";
	input << "\t}";
	const HoI4::IdeaGroup theIdeaGroup("theName", input);

	std::stringstream actualOutput;
	actualOutput << theIdeaGroup;

	std::stringstream expectedOutput;
	expectedOutput << "\ttheName = {\n";
	expectedOutput << "\t\tlaw = yes\n";
	expectedOutput << "\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaGroupTests, LawOnlySetWithYes)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tlaw = no\n";
	input << "\t}";
	const HoI4::IdeaGroup theIdeaGroup("theName", input);

	std::stringstream actualOutput;
	actualOutput << theIdeaGroup;

	std::stringstream expectedOutput;
	expectedOutput << "\ttheName = {\n";
	expectedOutput << "\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaGroupTests, UseListViewCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tuse_list_view = yes\n";
	input << "\t}";
	const HoI4::IdeaGroup theIdeaGroup("theName", input);

	std::stringstream actualOutput;
	actualOutput << theIdeaGroup;

	std::stringstream expectedOutput;
	expectedOutput << "\ttheName = {\n";
	expectedOutput << "\t\tuse_list_view = yes\n";
	expectedOutput << "\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaGroupTests, UseListViewOnlySetWithYes)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tuse_list_view = no\n";
	input << "\t}";
	const HoI4::IdeaGroup theIdeaGroup("theName", input);

	std::stringstream actualOutput;
	actualOutput << theIdeaGroup;

	std::stringstream expectedOutput;
	expectedOutput << "\ttheName = {\n";
	expectedOutput << "\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaGroupTests, DesignerCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tdesigner = yes\n";
	input << "\t}";
	const HoI4::IdeaGroup theIdeaGroup("theName", input);

	std::stringstream actualOutput;
	actualOutput << theIdeaGroup;

	std::stringstream expectedOutput;
	expectedOutput << "\ttheName = {\n";
	expectedOutput << "\t\tdesigner = yes\n";
	expectedOutput << "\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaGroupTests, DesignerOnlySetWithYes)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tdesigner = no\n";
	input << "\t}";
	const HoI4::IdeaGroup theIdeaGroup("theName", input);

	std::stringstream actualOutput;
	actualOutput << theIdeaGroup;

	std::stringstream expectedOutput;
	expectedOutput << "\ttheName = {\n";
	expectedOutput << "\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaGroupTests, IdeasDefaultsToEmpty)
{
	std::stringstream input;
	const HoI4::IdeaGroup theIdeaGroup("theName", input);

	ASSERT_TRUE(theIdeaGroup.getIdeas().empty());
}


TEST(HoI4World_Ideas_IdeaGroupTests, IdeasCanBeAdded)
{
	std::stringstream groupInput;
	groupInput << "= {\n";
	groupInput << "\t\ttest_idea = {\n";
	groupInput << "\t\t}\n";
	groupInput << "\t}";
	const HoI4::IdeaGroup theIdeaGroup("theName", groupInput);

	ASSERT_EQ(1, theIdeaGroup.getIdeas().size());

	std::stringstream actualOutput;
	actualOutput << theIdeaGroup.getIdeas()[0];

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttest_idea = {\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaGroupTests, IdeasCanBeReplaced)
{
	std::stringstream groupInput;
	groupInput << "= {\n";
	groupInput << "\t\ttest_idea = {\n";
	groupInput << "\t\t}\n";
	groupInput << "\t}";
	HoI4::IdeaGroup theIdeaGroup("theName", groupInput);

	std::stringstream ideaInput;
	ideaInput << "= {\n";
	ideaInput << "\t\t\tlevel = 5\n";
	ideaInput << "\t\t}";
	HoI4::Idea testIdea("test_idea", ideaInput);

	theIdeaGroup.replaceIdea(testIdea);

	ASSERT_EQ(1, theIdeaGroup.getIdeas().size());

	std::stringstream actualOutput;
	actualOutput << theIdeaGroup.getIdeas()[0];

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttest_idea = {\n";
	expectedOutput << "\t\t\tlevel = 5\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaGroupTests, GetIdeaReturnNulloptForMissingIdea)
{
	std::stringstream input;
	const HoI4::IdeaGroup theIdeaGroup("theName", input);

	ASSERT_EQ(std::nullopt, theIdeaGroup.getIdea("missing_idea"));
}


TEST(HoI4World_Ideas_IdeaGroupTests, GetIdeaReturnsIdea)
{
	std::stringstream groupInput;
	groupInput << "= {\n";
	groupInput << "\t\ttest_idea = {\n";
	groupInput << "\t\t}\n";
	groupInput << "\t}";
	const HoI4::IdeaGroup theIdeaGroup("theName", groupInput);

	auto returnedIdea = *theIdeaGroup.getIdea("test_idea");

	std::stringstream actualOutput;
	actualOutput << returnedIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttest_idea = {\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}