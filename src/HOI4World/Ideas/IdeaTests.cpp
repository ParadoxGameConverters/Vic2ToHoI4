#include "HOI4World/Ideas/Idea.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Ideas_IdeaTests, NameIsAsSet)
{
	std::stringstream input;
	const HoI4::Idea theIdea("theName", input);

	ASSERT_EQ("theName", theIdea.getName());
}


TEST(HoI4World_Ideas_IdeaTests, AllItemsDefaultToEmpty)
{
	std::stringstream input;
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, AltNameCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tname = alt_name";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\tname = alt_name\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, LedgerCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tledger = test_ledger";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\tledger = test_ledger\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, CostCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tcost = 42";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\tcost = 42\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, RemovalCostCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tremoval_cost = 42";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\tremoval_cost = 42\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, LevelCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tlevel = 42";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\tlevel = 42\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, AllowedCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tallowed = yes";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\tallowed = yes\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, AllowedCivilWarCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tallowed_civil_war = yes";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\tallowed_civil_war = yes\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, AllowedCivilWarCanBeChanged)
{
	std::stringstream input;
	HoI4::Idea theIdea("theIdea", input);
	theIdea.setAllowedCivilWar("= yes");

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\tallowed_civil_war = yes\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, CancelCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tcancel = yes";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\tcancel = yes\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, CancelCanBeUpdated)
{
	std::stringstream input;
	HoI4::Idea theIdea("theIdea", input);

	std::string newString = "= {\n";
	newString += "\t\t\t\tat_war = yes\n";
	newString += "\t\t\t}";
	theIdea.updateCancel(newString);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\tcancel = {\n";
	expectedOutput << "\t\t\t\tat_war = yes\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, AvailableCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tavailable = yes";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\tavailable = yes\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, AvailableCanBeChanged)
{
	std::stringstream input;
	HoI4::Idea theIdea("theIdea", input);
	theIdea.setAvailable("= yes");

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\tavailable = yes\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, AiWillDoCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tai_will_do = yes";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\tai_will_do = yes\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, PictureCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tpicture = yes";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\tpicture = yes\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, RuleCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\trule = yes";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\trule = yes\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, ModifierCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tmodifier = yes";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\tmodifier = yes\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, ResearchBonusCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tresearch_bonus = yes";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\tresearch_bonus = yes\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, EquipmentBonusCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tequipment_bonus = yes";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\tequipment_bonus = yes\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, TraitsCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ttraits = yes";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\ttraits = yes\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, OnAddCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ton_add = yes";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\ton_add = yes\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, AllowedToRemoveCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tallowed_to_remove = yes";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\tallowed_to_remove = yes\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, IsDefaultCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tdefault = yes";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\tdefault = yes\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, IsDefaultOnlySetWithYes)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tdefault = no";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, CancelIfInvalidCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tcancel_if_invalid = yes";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\tcancel_if_invalid = yes\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}


TEST(HoI4World_Ideas_IdeaTests, CancelIfInvalidCanBeSetToNo)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tcancel_if_invalid = no";
	input << "}";
	const HoI4::Idea theIdea("theIdea", input);

	std::stringstream actualOutput;
	actualOutput << theIdea;

	std::stringstream expectedOutput;
	expectedOutput << "\t\ttheIdea = {\n";
	expectedOutput << "\t\t\tcancel_if_invalid = no\n";
	expectedOutput << "\t\t}\n";

	ASSERT_EQ(expectedOutput.str(), actualOutput.str());
}