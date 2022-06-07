#include "src/HOI4World/Decisions/DecisionsInCategory.h"
#include "src/HOI4World/Events/EventsBuilder.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Decisions_DecisionsInCategoryTests, NameDefaultsToBlank)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	const HoI4::DecisionsInCategory theDecisionsInCategory("", input);

	ASSERT_EQ(theDecisionsInCategory.getName(), "");
}


TEST(HoI4World_Decisions_DecisionsInCategoryTests, NameCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	const HoI4::DecisionsInCategory theDecisionsInCategory("decisionsCategoryName", input);

	ASSERT_EQ(theDecisionsInCategory.getName(), "decisionsCategoryName");
}


TEST(HoI4World_Decisions_DecisionsInCategoryTests, DecisionsDefaultsToEmpty)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	const HoI4::DecisionsInCategory theDecisionsInCategory("", input);

	ASSERT_EQ(theDecisionsInCategory.getDecisions().size(), 0);
}


TEST(HoI4World_Decisions_DecisionsInCategoryTests, DecisionsCanBeImported)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tdecision={}\n";
	input << "}";
	const HoI4::DecisionsInCategory theDecisionsInCategory("", input);

	ASSERT_EQ(theDecisionsInCategory.getDecisions().size(), 1);
}


TEST(HoI4World_Decisions_DecisionsInCategoryTests, DecisionCanBeReplaced)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tdecision={}\n";
	input << "}";
	HoI4::DecisionsInCategory theDecisionsInCategory("decisionsCategoryName", input);

	std::stringstream decisionInput;
	decisionInput << "= { cost = 50 }";
	HoI4::decision newDecision("decision", decisionInput);
	theDecisionsInCategory.replaceDecision(newDecision);

	std::stringstream output;
	output << theDecisionsInCategory;

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


TEST(HoI4World_Decisions_DecisionsInCategoryTests, DecisionsCanBeReplaced)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tdecision={}\n";
	input << "}";
	HoI4::DecisionsInCategory theDecisionsInCategory("decisionsCategoryName", input);

	std::stringstream decisionInput;
	decisionInput << "= { cost = 50 }";
	HoI4::decision newDecision("decision", decisionInput);
	std::vector<HoI4::decision> newDecisions;
	newDecisions.push_back(newDecision);

	theDecisionsInCategory.replaceDecisions(newDecisions);

	std::stringstream output;
	output << theDecisionsInCategory;

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


TEST(HoI4World_Decisions_DecisionsInCategoryTests, ReplacingNonexistentDecisionDoesNotAddIt)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	HoI4::DecisionsInCategory theDecisionsInCategory("decisionsCategoryName", input);

	std::stringstream decisionInput;
	decisionInput << "= { cost = 50 }";
	HoI4::decision newDecision("decision", decisionInput);
	theDecisionsInCategory.replaceDecision(newDecision);

	std::stringstream output;
	output << theDecisionsInCategory;

	std::stringstream expectedOutput;
	expectedOutput << "decisionsCategoryName = {\n";
	expectedOutput << "\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	ASSERT_EQ(output.str(), expectedOutput.str());
}


TEST(HoI4World_Decisions_DecisionsInCategoryTests, DecisionCanBeAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	HoI4::DecisionsInCategory theDecisionsInCategory("decisionsCategoryName", input);

	std::stringstream decisionInput;
	decisionInput << "= { cost = 50 }";
	HoI4::decision newDecision("decision", decisionInput);
	theDecisionsInCategory.addDecision(newDecision);

	std::stringstream output;
	output << theDecisionsInCategory;

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


TEST(HoI4World_Decisions_DecisionsInCategoryTests, EqualCategoriesAreEqual)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	HoI4::DecisionsInCategory theDecisionsInCategory("decisionsCategoryName", input);
	HoI4::DecisionsInCategory theDecisionsInCategory2("decisionsCategoryName", input);

	ASSERT_TRUE(theDecisionsInCategory == theDecisionsInCategory2);
}


TEST(HoI4World_Decisions_DecisionsInCategoryTests, UnequalCategoriesAreUnequal)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	HoI4::DecisionsInCategory theDecisionsInCategory("decisionsCategoryName", input);
	HoI4::DecisionsInCategory theDecisionsInCategory2("decisionsCategoryName2", input);

	ASSERT_FALSE(theDecisionsInCategory == theDecisionsInCategory2);
}


TEST(HoI4World_Decisions_DecisionsInCategoryTests, OpenUpPoliticalDiscourseCanBeUpdatedWithIdeologies)
{
	std::stringstream input;
	input << "= {\n";
	input << "\topen_up_political_discourse_fascism={}\n";
	input << "}";
	HoI4::DecisionsInCategory theDecisionsInCategory("decisionsCategoryName", input);

	std::set<std::string> ideologies;
	ideologies.insert("fascism");
	ideologies.insert("democracy");
	ideologies.insert("communism");
	theDecisionsInCategory.updatePoliticalDecisions(ideologies, *HoI4::Events::Builder().Build());

	std::stringstream output;
	output << theDecisionsInCategory;

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


TEST(HoI4World_Decisions_DecisionsInCategoryTests, DiscreditGovernmentCanBeUpdatedWithIdeologies)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tdiscredit_government_communism={}\n";
	input << "}";
	HoI4::DecisionsInCategory theDecisionsInCategory("decisionsCategoryName", input);

	std::set<std::string> ideologies;
	ideologies.insert("fascism");
	ideologies.insert("democracy");
	ideologies.insert("communism");
	theDecisionsInCategory.updatePoliticalDecisions(ideologies, *HoI4::Events::Builder().Build());

	std::stringstream output;
	output << theDecisionsInCategory;

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


TEST(HoI4World_Decisions_DecisionsInCategoryTests, InstituePressCensorshipCanBeUpdatedWithIdeologies)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tinstitute_press_censorship_absolutism={}\n";
	input << "}";
	HoI4::DecisionsInCategory theDecisionsInCategory("decisionsCategoryName", input);

	std::set<std::string> ideologies;
	ideologies.insert("absolutism");
	ideologies.insert("democracy");
	ideologies.insert("communism");
	theDecisionsInCategory.updatePoliticalDecisions(ideologies, *HoI4::Events::Builder().Build());

	std::stringstream output;
	output << theDecisionsInCategory;

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


TEST(HoI4World_Decisions_DecisionsInCategoryTests, IgniteTheIdeologyCivilWarCanBeUpdatedWithIdeologies)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tignite_the_radical_civil_war={}\n";
	input << "}";
	HoI4::DecisionsInCategory theDecisionsInCategory("decisionsCategoryName", input);

	std::set<std::string> ideologies;
	ideologies.insert("absolutism");
	ideologies.insert("democracy");
	ideologies.insert("radical");
	theDecisionsInCategory.updatePoliticalDecisions(ideologies, *HoI4::Events::Builder().Build());

	std::stringstream output;
	output << theDecisionsInCategory;

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


TEST(HoI4World_Decisions_DecisionsInCategoryTests, HoldTheIdeologyNationalReferendumCanBeUpdatedWithEvents)
{
	std::stringstream input;
	input << "= {\n";
	input << "\thold_the_democratic_national_referendum={}\n";
	input << "}";
	HoI4::DecisionsInCategory theDecisionsInCategory("decisionsCategoryName", input);

	std::set<std::string> ideologies;
	theDecisionsInCategory.updatePoliticalDecisions(ideologies,
		 *HoI4::Events::Builder().addEventNumber("fiftyPercentdemocratic", 122).Build());

	std::stringstream output;
	output << theDecisionsInCategory;

	std::stringstream expectedOutput;
	expectedOutput << "decisionsCategoryName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\thold_the_democratic_national_referendum = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tcomplete_effect = {\n";
	expectedOutput << "\t\t\tcountry_event = { id = conv.political.122 }\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "}\n";
	expectedOutput << "\n";
	ASSERT_EQ(output.str(), expectedOutput.str());
}