#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Decisions/Decision.h"
#include "src/OutHoi4/Decisions/OutDecision.h"
#include <sstream>



TEST(HoI4World_Decisions_DecisionTests, EverythingDefaultsToEmptyOrBlank)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	HoI4::decision theDecision("", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\t = {\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, NameCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	const HoI4::decision theDecision("decisionName", input);

	ASSERT_EQ(theDecision.getName(), "decisionName");
}


TEST(HoI4World_Decisions_DecisionTests, IconCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ticon = generic_civil_support\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\ticon = generic_civil_support\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, NameFieldCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tname = recruit_in_europe_state\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tname = recruit_in_europe_state\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, IsGoodCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tis_good = no\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tis_good = no\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, AllowedCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tallowed = {\n";
	input << "\t\t\talways = yes\n";
	input << "\t}\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tallowed = {\n";
	expectedOutput << "\t\t\talways = yes\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, AllowedCanBeChanged)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tallowed = {\n";
	input << "\t\talways = yes\n";
	input << "\t}\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);
	theDecision.setAllowed("= {\n\t\t\talways = no\n\t\t}");

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tallowed = {\n";
	expectedOutput << "\t\t\talways = no\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, HighlightStatesTargetsCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\thighlight_state_targets = {\n";
	input << "\t\t\tstate = 105\n";
	input << "\t\t}\n";
	input << "\t}";
	const HoI4::decision theDecision("decisionName", input);

	ASSERT_EQ("= {\n\t\t\tstate = 105\n\t\t}", theDecision.getHighlightStateTargets());
}


TEST(HoI4World_Decisions_DecisionTests, HighlightStateTargetsCanBeChanged)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);
	theDecision.setHighlightStateTargets("= {\n\t\t\tstate = 609\n\t\t}");

	ASSERT_EQ("= {\n\t\t\tstate = 609\n\t\t}", theDecision.getHighlightStateTargets());
}


TEST(HoI4World_Decisions_DecisionTests, AvailableCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tavailable = {\n";
	input << "\t\t\thas_unsupported_economic_law = yes\n";
	input << "\t\t\thas_war = no\n";
	input << "\t\t}\n";
	input << "\t}";
	const HoI4::decision theDecision("decisionName", input);

	ASSERT_EQ("= {\n\t\t\thas_unsupported_economic_law = yes\n\t\t\thas_war = no\n\t\t}", theDecision.getAvailable());
}


TEST(HoI4World_Decisions_DecisionTests, AvailableCanBeChanged)
{
	std::stringstream input;
	HoI4::decision theDecision("decisionName", input);

	std::string newAvailable = "= {\n";
	newAvailable += "\t\t\thas_unsupported_economic_law = yes\n";
	newAvailable += "\t\t\thas_war = no\n";
	newAvailable += "\t\t}";
	theDecision.setAvailable(newAvailable);

	ASSERT_EQ("= {\n\t\t\thas_unsupported_economic_law = yes\n\t\t\thas_war = no\n\t\t}", theDecision.getAvailable());
}


TEST(HoI4World_Decisions_DecisionTests, DaysMissionTimeoutCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tdays_mission_timeout = 90\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tdays_mission_timeout = 90\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, ActivationCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tactivation = {\n";
	input << "\t\thas_unsupported_economic_law = yes\n";
	input << "\t\thas_war = no\n";
	input << "\t}\n";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tactivation = {\n";
	expectedOutput << "\t\thas_unsupported_economic_law = yes\n";
	expectedOutput << "\t\thas_war = no\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, TargetsCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ttargets = { host }\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\ttargets = { host }\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, TargetArrayCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ttarget_array = exiles\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\ttarget_array = exiles\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, TargetRootTriggerCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\ttarget_root_trigger = {\n";
	input << "\t\t\tis_major = yes\n";
	input << "\t\t\thas_capitulated = no\n";
	input << "\t\t}\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\ttarget_root_trigger = {\n";
	expectedOutput << "\t\t\tis_major = yes\n";
	expectedOutput << "\t\t\thas_capitulated = no\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, StateTargetCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tstate_target = yes\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tstate_target = yes\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, TargetTriggerCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ttarget_trigger = {\n";
	input << "\t\tFROM = { \n";
	input << "\t\t\toriginal_tag = GER\n";
	input << "\t\t}\n";
	input << "\t}\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\ttarget_trigger = {\n";
	expectedOutput << "\t\tFROM = { \n";
	expectedOutput << "\t\t\toriginal_tag = GER\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, TargetTriggerCanBeChanged)
{
	std::stringstream input;
	HoI4::decision theDecision("decisionName", input);

	std::string newTargetTrigger = "= {\n";
	newTargetTrigger += "\t\t\tFROM = {\n";
	newTargetTrigger += "\t\t\t\tis_exiled_in = ROOT\n";
	newTargetTrigger += "\t\t\t\thas_legitimacy > 40\n";
	newTargetTrigger += "\t\t\t\tOR = {\n";
	newTargetTrigger += "\t\t\t\t\tabsolutist > 0.05\n";
	newTargetTrigger += "\t\t\t\t\tradical > 0.05\n";
	newTargetTrigger += "\t\t\t\t}\n";
	newTargetTrigger += "\t\t\t}\n";
	newTargetTrigger += "\t\t}";
	theDecision.setTargetTrigger(newTargetTrigger);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\ttarget_trigger = {\n";
	expectedOutput << "\t\t\tFROM = {\n";
	expectedOutput << "\t\t\t\tis_exiled_in = ROOT\n";
	expectedOutput << "\t\t\t\thas_legitimacy > 40\n";
	expectedOutput << "\t\t\t\tOR = {\n";
	expectedOutput << "\t\t\t\t\tabsolutist > 0.05\n";
	expectedOutput << "\t\t\t\t\tradical > 0.05\n";
	expectedOutput << "\t\t\t\t}\n";
	expectedOutput << "\t\t\t}\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, TargetNonExistingCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ttarget_non_existing = yes\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\ttarget_non_existing = yes\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, RemoveTriggerCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tremove_trigger = {\n";
	input << "\t\thas_government = fascism\n";
	input << "\t}\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tremove_trigger = {\n";
	expectedOutput << "\t\thas_government = fascism\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, CustomCostTriggerCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tcustom_cost_trigger = {\n";
	input << "\t\tcommand_power > 25\n";
	input << "\t}\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tcustom_cost_trigger = {\n";
	expectedOutput << "\t\tcommand_power > 25\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, CustomCostTextCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tcustom_cost_text = custom_cost_joint_training_exercise\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tcustom_cost_text = custom_cost_joint_training_exercise\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, VisibleCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tvisible = {\n";
	input << "\t\t\thas_war = no\n";
	input << "\t\t\thas_unsupported_economic_law = yes\n";
	input << "\t\t}\n";
	input << "}";
	const HoI4::decision theDecision("decisionName", input);

	ASSERT_EQ("= {\n\t\t\thas_war = no\n\t\t\thas_unsupported_economic_law = yes\n\t\t}", theDecision.getVisible());
}


TEST(HoI4World_Decisions_DecisionTests, VisibleCanBeChanged)
{
	std::stringstream input;
	HoI4::decision theDecision("decisionName", input);

	std::string newVisible = "= {\n";
	newVisible += "\t\t\thas_war = no\n";
	newVisible += "\t\t\thas_unsupported_economic_law = yes\n";
	newVisible += "\t\t}";
	theDecision.setVisible(newVisible);
	ASSERT_EQ("= {\n\t\t\thas_war = no\n\t\t\thas_unsupported_economic_law = yes\n\t\t}", theDecision.getVisible());
}


TEST(HoI4World_Decisions_DecisionTests, CancelTriggerCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tcancel_trigger = {\n";
	input << "\t\thidden_trigger = { \n";
	input << "\t\t\thas_civil_war = yes\n";
	input << "\t\t}\n";
	input << "\t}\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tcancel_trigger = {\n";
	expectedOutput << "\t\thidden_trigger = { \n";
	expectedOutput << "\t\t\thas_civil_war = yes\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, OnMapModeCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\ton_map_mode = map_only\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\ton_map_mode = map_only\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, CompleteEffectCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tcomplete_effect = {\n";
	input << "\t\tcountry_event = stability.21\n";
	input << "\t}\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tcomplete_effect = {\n";
	expectedOutput << "\t\tcountry_event = stability.21\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, CompleteEffectCanBeChanged)
{
	std::stringstream input;
	HoI4::decision theDecision("decisionName", input);

	std::string newCompleteEffect = "= {\n";
	newCompleteEffect += "\t\tcountry_event = stability.21\n";
	newCompleteEffect += "\t}";
	theDecision.setCompleteEffect(newCompleteEffect);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tcomplete_effect = {\n";
	expectedOutput << "\t\tcountry_event = stability.21\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, TargetedModifierCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\ttargeted_modifier = {\n";
	input << "\t\t\ttag = FROM\n";
	input << "\t\t\ttargeted_legitimacy_daily = -1\n";
	input << "\t\t\tdemocratic_drift = 0.05\n";
	input << "\t\t}\n";
	input << "\t}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\ttargeted_modifier = {\n";
	expectedOutput << "\t\t\ttag = FROM\n";
	expectedOutput << "\t\t\ttargeted_legitimacy_daily = -1\n";
	expectedOutput << "\t\t\tdemocratic_drift = 0.05\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, TargetedModifierCanBeChanged)
{
	std::stringstream input;
	HoI4::decision theDecision("decisionName", input);

	std::string newTargetedModifier = "= {\n";
	newTargetedModifier += "\t\t\ttag = FROM\n";
	newTargetedModifier += "\t\t\ttargeted_legitimacy_daily = -1\n";
	newTargetedModifier += "\t\t\tdemocratic_drift = 0.05\n";
	newTargetedModifier += "\t\t}";
	theDecision.setTargetedModifier(newTargetedModifier);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\ttargeted_modifier = {\n";
	expectedOutput << "\t\t\ttag = FROM\n";
	expectedOutput << "\t\t\ttargeted_legitimacy_daily = -1\n";
	expectedOutput << "\t\t\tdemocratic_drift = 0.05\n";
	expectedOutput << "\t\t}\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, RemoveEffectCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tremove_effect = {\n";
	input << "\t\t\tno_effect\n";
	input << "\t\t}\n";
	input << "\t}";
	const HoI4::decision theDecision("decisionName", input);

	ASSERT_EQ("= {\n\t\t\tno_effect\n\t\t}", theDecision.getRemoveEffect());
}


TEST(HoI4World_Decisions_DecisionTests, RemoveEffectCanBeChanged)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);
	theDecision.setRemoveEffect("= {\n\t\t\tno_effect\n\t\t}");

	ASSERT_EQ("= {\n\t\t\tno_effect\n\t\t}", theDecision.getRemoveEffect());
}


TEST(HoI4World_Decisions_DecisionTests, TimeoutEffectCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ttimeout_effect = {\n";
	input << "\t\tadd_stability = -0.1 #naughty\n";
	input << "\t}\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "= {\n";
	expectedOutput << "\t\tadd_stability = -0.1 #naughty\n";
	expectedOutput << "\t}";
	ASSERT_EQ(theDecision.getTimeoutEffect(), expectedOutput.str());
}


TEST(HoI4World_Decisions_DecisionTests, TimeoutEffectCanBeChanged)
{
	std::stringstream input;
	HoI4::decision theDecision("decisionName", input);

	std::string newTimeoutEffect = "= {\n";
	newTimeoutEffect += "\t\tadd_stability = -0.1 #naughty\n";
	newTimeoutEffect += "\t}";
	theDecision.setTimeoutEffect(newTimeoutEffect);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "= {\n";
	expectedOutput << "\t\tadd_stability = -0.1 #naughty\n";
	expectedOutput << "\t}";
	ASSERT_EQ(theDecision.getTimeoutEffect(), expectedOutput.str());
}


TEST(HoI4World_Decisions_DecisionTests, AiWillDoCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tai_will_do = {\n";
	input << "\t\tfactor = 1\n";
	input << "\t}\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tai_will_do = {\n";
	expectedOutput << "\t\tfactor = 1\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, AiWillDoCanBeChanged)
{
	std::stringstream input;
	HoI4::decision theDecision("decisionName", input);

	std::string newAiWillDo = "= {\n";
	newAiWillDo += "\t\tfactor = 1\n";
	newAiWillDo += "\t}";
	theDecision.setAiWillDo(newAiWillDo);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tai_will_do = {\n";
	expectedOutput << "\t\tfactor = 1\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, FireOnlyOnceCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tfire_only_once = yes\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tfire_only_once = yes\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, DaysRemoveCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tdays_remove = 365\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tdays_remove = 365\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, DaysReEnableCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tdays_re_enable = 30\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\t\tdays_re_enable = 30\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, CostCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tcost = var:war_propaganda_cost?75\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tcost = var:war_propaganda_cost?75\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, ModfierCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tmodifier = {\n";
	input << "\t\tfascism_drift = 0.02\n";
	input << "\t\tstability_weekly = -0.03\n";
	input << "\t\tpolitical_power_gain = -0.2\n";
	input << "\t}\n";
	input << "}";
	HoI4::decision theDecision("decisionName", input);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tmodifier = {\n";
	expectedOutput << "\t\tfascism_drift = 0.02\n";
	expectedOutput << "\t\tstability_weekly = -0.03\n";
	expectedOutput << "\t\tpolitical_power_gain = -0.2\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, ModfierCanBeChanged)
{
	std::stringstream input;
	HoI4::decision theDecision("decisionName", input);

	std::string newModifier = "= {\n";
	newModifier += "\t\tfascism_drift = 0.02\n";
	newModifier += "\t\tstability_weekly = -0.03\n";
	newModifier += "\t\tpolitical_power_gain = -0.2\n";
	newModifier += "\t}";
	theDecision.setModifier(newModifier);

	std::stringstream output;
	output << theDecision;

	std::stringstream expectedOutput;
	expectedOutput << "\n";
	expectedOutput << "\tdecisionName = {\n";
	expectedOutput << "\n";
	expectedOutput << "\t\tmodifier = {\n";
	expectedOutput << "\t\tfascism_drift = 0.02\n";
	expectedOutput << "\t\tstability_weekly = -0.03\n";
	expectedOutput << "\t\tpolitical_power_gain = -0.2\n";
	expectedOutput << "\t}\n";
	expectedOutput << "\t}";
	ASSERT_EQ(expectedOutput.str(), output.str());
}


TEST(HoI4World_Decisions_DecisionTests, EqualDecisionsAreEqual)
{
	std::stringstream input;
	const HoI4::decision theDecision("decisionName", input);
	const HoI4::decision secondDecision("decisionName", input);

	ASSERT_TRUE(theDecision == secondDecision);
}


TEST(HoI4World_Decisions_DecisionTests, UnequalDecisionsAreUnequal)
{
	std::stringstream input;
	const HoI4::decision theDecision("decisionName", input);
	const HoI4::decision secondDecision("decisionName2", input);

	ASSERT_FALSE(theDecision == secondDecision);
}