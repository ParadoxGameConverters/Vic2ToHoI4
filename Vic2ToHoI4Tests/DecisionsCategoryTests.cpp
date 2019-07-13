/*Copyright (c) 2019 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HOI4World/Decisions/DecisionsCategory.h"
#include "mocks/EventsMock.h"
#include <sstream>



TEST(HoI4World_DecisionsCategoryTests, NameDefaultsToBlank)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	HoI4::decisionsCategory theDecisionsCategory("", input);

	ASSERT_EQ(theDecisionsCategory.getName(), "");
}


TEST(HoI4World_DecisionsCategoryTests, NameCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	HoI4::decisionsCategory theDecisionsCategory("decisionsCategoryName", input);

	ASSERT_EQ(theDecisionsCategory.getName(), "decisionsCategoryName");
}


TEST(HoI4World_DecisionsCategoryTests, DecisionsDefaultsToEmpty)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	HoI4::decisionsCategory theDecisionsCategory("", input);

	ASSERT_EQ(theDecisionsCategory.getDecisions().size(), 0);
}


TEST(HoI4World_DecisionsCategoryTests, DecisionsCanBeImported)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tdecision={}\n";
	input << "}";
	HoI4::decisionsCategory theDecisionsCategory("", input);

	ASSERT_EQ(theDecisionsCategory.getDecisions().size(), 1);
}


TEST(HoI4World_DecisionsCategoryTests, DecisionCategorycanBeOutput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tdecision={}\n";
	input << "}";
	HoI4::decisionsCategory theDecisionsCategory("decisionsCategoryName", input);

	std::stringstream output;
	output << theDecisionsCategory;

	std::stringstream expectedOutput;
	expectedOutput << "decisionsCategoryName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\tdecision = {\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	ASSERT_EQ(output.str(), expectedOutput.str());
}


TEST(HoI4World_DecisionsCategoryTests, DecisionCanBeReplaced)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tdecision={}\n";
	input << "}";
	HoI4::decisionsCategory theDecisionsCategory("decisionsCategoryName", input);

	std::stringstream decisionInput;
	decisionInput << "= { cost = 50 }";
	HoI4::decision newDecision("decision", decisionInput);
	theDecisionsCategory.replaceDecision(newDecision);

	std::stringstream output;
	output << theDecisionsCategory;

	std::stringstream expectedOutput;
	expectedOutput << "decisionsCategoryName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\tdecision = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tcost = 50\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	ASSERT_EQ(output.str(), expectedOutput.str());
}


TEST(HoI4World_DecisionsCategoryTests, ReplacingNonexistentDecisionDoesNotAddIt)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	HoI4::decisionsCategory theDecisionsCategory("decisionsCategoryName", input);

	std::stringstream decisionInput;
	decisionInput << "= { cost = 50 }";
	HoI4::decision newDecision("decision", decisionInput);
	theDecisionsCategory.replaceDecision(newDecision);

	std::stringstream output;
	output << theDecisionsCategory;

	std::stringstream expectedOutput;
	expectedOutput << "decisionsCategoryName = {\n";
	expectedOutput << "\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	ASSERT_EQ(output.str(), expectedOutput.str());
}


TEST(HoI4World_DecisionsCategoryTests, DecisionCanBeAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	HoI4::decisionsCategory theDecisionsCategory("decisionsCategoryName", input);

	std::stringstream decisionInput;
	decisionInput << "= { cost = 50 }";
	HoI4::decision newDecision("decision", decisionInput);
	theDecisionsCategory.addDecision(newDecision);

	std::stringstream output;
	output << theDecisionsCategory;

	std::stringstream expectedOutput;
	expectedOutput << "decisionsCategoryName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\tdecision = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tcost = 50\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	ASSERT_EQ(output.str(), expectedOutput.str());
}


TEST(HoI4World_DecisionsCategoryTests, EqualCategoriesAreEqual)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	HoI4::decisionsCategory theDecisionsCategory("decisionsCategoryName", input);
	HoI4::decisionsCategory theDecisionsCategory2("decisionsCategoryName", input);

	ASSERT_TRUE(theDecisionsCategory == theDecisionsCategory2);
}


TEST(HoI4World_DecisionsCategoryTests, UnequalCategoriesAreUnequal)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	HoI4::decisionsCategory theDecisionsCategory("decisionsCategoryName", input);
	HoI4::decisionsCategory theDecisionsCategory2("decisionsCategoryName2", input);

	ASSERT_FALSE(theDecisionsCategory == theDecisionsCategory2);
}


TEST(HoI4World_DecisionsCategoryTests, OpenUpPoliticalDiscourseCanBeUpdatedWithIdeologies)
{
	std::stringstream input;
	input << "= {\n";
	input << "\topen_up_political_discourse_fascism={}\n";
	input << "}";
	HoI4::decisionsCategory theDecisionsCategory("decisionsCategoryName", input);

	std::set<std::string> ideologies;
	ideologies.insert("fascism");
	ideologies.insert("democracy");
	ideologies.insert("communism");
	mockEvents theEvents;
	theDecisionsCategory.updatePoliticalDecisions(ideologies, theEvents);

	std::stringstream output;
	output << theDecisionsCategory;

	std::stringstream expectedOutput;
	expectedOutput << "decisionsCategoryName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\topen_up_political_discourse_fascism = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tavailable = {\n";
	expectedOutput << "\t\t\tcommunism < 0.9\n";
	expectedOutput << "\t\t\tdemocracy < 0.9\n";
	expectedOutput << "\t\t\tfascism < 0.9\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	ASSERT_EQ(output.str(), expectedOutput.str());
}


TEST(HoI4World_DecisionsCategoryTests, DiscreditGovernmentCanBeUpdatedWithIdeologies)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tdiscredit_government_communism={}\n";
	input << "}";
	HoI4::decisionsCategory theDecisionsCategory("decisionsCategoryName", input);

	std::set<std::string> ideologies;
	ideologies.insert("fascism");
	ideologies.insert("democracy");
	ideologies.insert("communism");
	mockEvents theEvents;
	theDecisionsCategory.updatePoliticalDecisions(ideologies, theEvents);

	std::stringstream output;
	output << theDecisionsCategory;

	std::stringstream expectedOutput;
	expectedOutput << "decisionsCategoryName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\tdiscredit_government_communism = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tavailable = {\n";
	expectedOutput << "\t\t\tcommunism < 0.8\n";
	expectedOutput << "\t\t\tdemocracy < 0.8\n";
	expectedOutput << "\t\t\tfascism < 0.8\n";
	expectedOutput << "\t\t\thas_idea_with_trait = communism_minister\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tcomplete_effect = {\n";
	expectedOutput << "\t\t\tadd_stability = -0.010\n";
	expectedOutput << "\t\t\tif = {\n";
	expectedOutput << "\t\t\t\tlimit = {\n";
	expectedOutput << "\t\t\t\t\thas_government = democracy\n";
	expectedOutput << "\t\t\t\t}\n";
	expectedOutput << "\t\t\t\tadd_popularity = {\n";
	expectedOutput << "\t\t\t\t\tideology = democracy\n";
	expectedOutput << "\t\t\t\t\tpopularity = -0.1\n";
	expectedOutput << "\t\t\t\t}\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\t\t\tif = {\n";
	expectedOutput << "\t\t\t\tlimit = {\n";
	expectedOutput << "\t\t\t\t\thas_government = fascism\n";
	expectedOutput << "\t\t\t\t}\n";
	expectedOutput << "\t\t\t\tadd_popularity = {\n";
	expectedOutput << "\t\t\t\t\tideology = fascism\n";
	expectedOutput << "\t\t\t\t\tpopularity = -0.1\n";
	expectedOutput << "\t\t\t\t}\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	ASSERT_EQ(output.str(), expectedOutput.str());
}


TEST(HoI4World_DecisionsCategoryTests, InstituePressCensorshipCanBeUpdatedWithIdeologies)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tinstitute_press_censorship_absolutism={}\n";
	input << "}";
	HoI4::decisionsCategory theDecisionsCategory("decisionsCategoryName", input);

	std::set<std::string> ideologies;
	ideologies.insert("absolutism");
	ideologies.insert("democracy");
	ideologies.insert("communism");
	mockEvents theEvents;
	theDecisionsCategory.updatePoliticalDecisions(ideologies, theEvents);

	std::stringstream output;
	output << theDecisionsCategory;

	std::stringstream expectedOutput;
	expectedOutput << "decisionsCategoryName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\tinstitute_press_censorship_absolutism = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tmodifier = {\n";
	expectedOutput << "\t\t\tabsolutism_drift = 0.03\n";
	expectedOutput << "\t\t\tcommunism_drift = -0.01\n";
	expectedOutput << "\t\t\tdemocracy_drift = -0.01\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	ASSERT_EQ(output.str(), expectedOutput.str());
}


TEST(HoI4World_DecisionsCategoryTests, IgniteTheIdeologyCivilWarCanBeUpdatedWithIdeologies)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tignite_the_radical_civil_war={}\n";
	input << "}";
	HoI4::decisionsCategory theDecisionsCategory("decisionsCategoryName", input);

	std::set<std::string> ideologies;
	ideologies.insert("absolutism");
	ideologies.insert("democracy");
	ideologies.insert("radical");
	mockEvents theEvents;
	theDecisionsCategory.updatePoliticalDecisions(ideologies, theEvents);

	std::stringstream output;
	output << theDecisionsCategory;

	std::stringstream expectedOutput;
	expectedOutput << "decisionsCategoryName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\tignite_the_radical_civil_war = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tcomplete_effect = {\n";
	expectedOutput << "\t\t\tif = {\n";
	expectedOutput << "\t\t\t\tlimit = {\n";
	expectedOutput << "\t\t\t\t\thas_government = absolutism\n";
	expectedOutput << "\t\t\t\t}\n";
	expectedOutput << "\t\t\t\tset_variable = {\n";
	expectedOutput << "\t\t\t\t\tvar = civil_war_size_var\n";
	expectedOutput << "\t\t\t\t\tvalue = party_popularity@absolutism\n";
	expectedOutput << "\t\t\t\t}\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\t\t\tif = {\n";
	expectedOutput << "\t\t\t\tlimit = {\n";
	expectedOutput << "\t\t\t\t\thas_government = democracy\n";
	expectedOutput << "\t\t\t\t}\n";
	expectedOutput << "\t\t\t\tset_variable = {\n";
	expectedOutput << "\t\t\t\t\tvar = civil_war_size_var\n";
	expectedOutput << "\t\t\t\t\tvalue = party_popularity@democracy\n";
	expectedOutput << "\t\t\t\t}\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\t\t\tsubtract_from_variable = {\n";
	expectedOutput << "\t\t\t\tvar = civil_war_size_var\n";
	expectedOutput << "\t\t\t\tvalue = army_support_var\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\t\t\tif = {\n";
	expectedOutput << "\t\t\t\tlimit = {\n";
	expectedOutput << "\t\t\t\t\tcheck_variable = {\n";
	expectedOutput << "\t\t\t\t\t\tvar = civil_war_size_var\n";
	expectedOutput << "\t\t\t\t\t\tvalue = 0.3\n";
	expectedOutput << "\t\t\t\t\t\tcompare = less_than\n";
	expectedOutput << "\t\t\t\t\t}\n";
	expectedOutput << "\t\t\t\t}\n";
	expectedOutput << "\t\t\t\tset_variable = {\n";
	expectedOutput << "\t\t\t\t\tvar = civil_war_size_var\n";
	expectedOutput << "\t\t\t\t\tvalue = 0.3\n";
	expectedOutput << "\t\t\t\t}\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\t\t\tstart_civil_war = {\n";
	expectedOutput << "\t\t\t\truling_party = radical\n";
	expectedOutput << "\t\t\t\tideology = ROOT\n";
	expectedOutput << "\t\t\t\tsize = civil_war_size_var\n";
	expectedOutput << "\t\t\t\tkeep_unit_leaders_trigger = {\n";
	expectedOutput << "\t\t\t\t\thas_trait = hidden_sympathies\n";
	expectedOutput << "\t\t\t\t}\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\t\t\tclr_country_flag = preparation_for_radical_civil_war\n";
	expectedOutput << "\t\t\tclr_country_flag = military_support_for_radical_civil_war\n";
	expectedOutput << "\t\t\tclr_country_flag = civil_support_for_radical_civil_war\n";
	expectedOutput << "\t\t\tset_country_flag = ideology_civil_war\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	ASSERT_EQ(output.str(), expectedOutput.str());
}


TEST(HoI4World_DecisionsCategoryTests, HoldTheIdeologyNationalReferendumCanBeUpdatedWithEvents)
{
	std::stringstream input;
	input << "= {\n";
	input << "\thold_the_democratic_national_referendum={}\n";
	input << "}";
	HoI4::decisionsCategory theDecisionsCategory("decisionsCategoryName", input);

	std::set<std::string> ideologies;
	mockEvents theEvents;
	EXPECT_CALL(theEvents, getEventNumber("fiftyPercentdemocratic")).WillOnce(testing::Return(122));
	theDecisionsCategory.updatePoliticalDecisions(ideologies, theEvents);

	std::stringstream output;
	output << theDecisionsCategory;

	std::stringstream expectedOutput;
	expectedOutput << "decisionsCategoryName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\thold_the_democratic_national_referendum = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tcomplete_effect = {\n";
	expectedOutput << "\t\t\tcountry_event = { id = political.122 }\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	ASSERT_EQ(output.str(), expectedOutput.str());
}