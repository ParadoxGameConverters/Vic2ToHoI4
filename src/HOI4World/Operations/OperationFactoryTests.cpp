#include "src/HOI4World/Operations/OperationFactory.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(HoI4World_Operations_OperationFactoryTests, NameCanBeSet)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ("operation_name", operation->getName());
}


TEST(HoI4World_Operations_OperationFactoryTests, IconDefaultsToEmpty)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_TRUE(operation->getIcon().empty());
}


TEST(HoI4World_Operations_OperationFactoryTests, IconCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ticon = test_icon\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ("test_icon", operation->getIcon());
}


TEST(HoI4World_Operations_OperationFactoryTests, PriorityDefaultsToZero)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ(0, operation->getPriority());
}


TEST(HoI4World_Operations_OperationFactoryTests, PriorityCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tpriority = 42\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ(42, operation->getPriority());
}


TEST(HoI4World_Operations_OperationFactoryTests, PreventCapturedOperativeToDieDefaultsToFalse)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_FALSE(operation->getPreventCapturedOperativeToDie());
}


TEST(HoI4World_Operations_OperationFactoryTests, PreventCapturedOperativeToDieCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tprevent_captured_operative_to_die = yes\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_TRUE(operation->getPreventCapturedOperativeToDie());
}


TEST(HoI4World_Operations_OperationFactoryTests, DaysDefaultsToZero)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ(0, operation->getDays());
}


TEST(HoI4World_Operations_OperationFactoryTests, DaysCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tdays = 42\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ(42, operation->getDays());
}


TEST(HoI4World_Operations_OperationFactoryTests, NetworkStrengthDefaultsToZero)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ(0, operation->getNetworkStrength());
}


TEST(HoI4World_Operations_OperationFactoryTests, NetworkStrengthCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tnetwork_strength = 42\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ(42, operation->getNetworkStrength());
}


TEST(HoI4World_Operations_OperationFactoryTests, OperativesDefaultsToZero)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ(0, operation->getOperatives());
}


TEST(HoI4World_Operations_OperationFactoryTests, OperativesCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\toperatives = 42\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ(42, operation->getOperatives());
}


TEST(HoI4World_Operations_OperationFactoryTests, VisibleDefaultsToEmpty)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_TRUE(operation->getVisible().empty());
}


TEST(HoI4World_Operations_OperationFactoryTests, VisibleCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tvisible = {\n";
	input << "\t\ttest_visible\n";
	input << "\t}\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ("= {\n\t\ttest_visible\n\t}", operation->getVisible());
}


TEST(HoI4World_Operations_OperationFactoryTests, ScaleCostIndependentOfTargetDefaultsToFalse)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_FALSE(operation->getScaleCostIndependentOfTarget());
}


TEST(HoI4World_Operations_OperationFactoryTests, ScaleCostIndependentOfTargetCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tscale_cost_independent_of_target = yes\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_TRUE(operation->getScaleCostIndependentOfTarget());
}


TEST(HoI4World_Operations_OperationFactoryTests, RequirementsDefaultsToNullopt)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_FALSE(operation->getRequirements());
}


TEST(HoI4World_Operations_OperationFactoryTests, RequirementsCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\trequirements = {\n";
	input << "\t\ttest_requirement\n";
	input << "\t}\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ("= {\n\t\ttest_requirement\n\t}", operation->getRequirements());
}


TEST(HoI4World_Operations_OperationFactoryTests, SelectionTargetStateDefaultsToNullopt)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_FALSE(operation->getSelectionTargetState());
}


TEST(HoI4World_Operations_OperationFactoryTests, SelectionTargetStateCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tselection_target_state = {\n";
	input << "\t\ttest_target_state\n";
	input << "\t}\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ("= {\n\t\ttest_target_state\n\t}", operation->getSelectionTargetState());
}


TEST(HoI4World_Operations_OperationFactoryTests, SelectionTargetDefaultsToNullopt)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_FALSE(operation->getSelectionTarget());
}


TEST(HoI4World_Operations_OperationFactoryTests, SelectionTargetCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tselection_target = {\n";
	input << "\t\ttest_selection_target\n";
	input << "\t}\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ("= {\n\t\ttest_selection_target\n\t}", operation->getSelectionTarget());
}


TEST(HoI4World_Operations_OperationFactoryTests, AllowedDefaultsToNullopt)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_FALSE(operation->getAllowed());
}


TEST(HoI4World_Operations_OperationFactoryTests, AllowedCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tallowed = {\n";
	input << "\t\ttest_allowed\n";
	input << "\t}\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ("= {\n\t\ttest_allowed\n\t}", operation->getAllowed());
}


TEST(HoI4World_Operations_OperationFactoryTests, AvailableDefaultsToNullopt)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_FALSE(operation->getAvailable());
}


TEST(HoI4World_Operations_OperationFactoryTests, AvailableCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tavailable = {\n";
	input << "\t\ttest_available\n";
	input << "\t}\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ("= {\n\t\ttest_available\n\t}", operation->getAvailable());
}


TEST(HoI4World_Operations_OperationFactoryTests, AwardedTokensDefaultsToEmpty)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_FALSE(operation->getAwardedTokens());
}


TEST(HoI4World_Operations_OperationFactoryTests, AwardedTokensCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tawarded_tokens = {\n";
	input << "\t\ttest_awarded_tokens\n";
	input << "\t}\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ("= {\n\t\ttest_awarded_tokens\n\t}", operation->getAwardedTokens());
}


TEST(HoI4World_Operations_OperationFactoryTests, EquipmentDefaultsToEmpty)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_TRUE(operation->getEquipment().empty());
}


TEST(HoI4World_Operations_OperationFactoryTests, EquipmentCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tequipment = {\n";
	input << "\t\ttest_equipment\n";
	input << "\t}\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ("= {\n\t\ttest_equipment\n\t}", operation->getEquipment());
}


TEST(HoI4World_Operations_OperationFactoryTests, RequiredTokensDefaultsToEmpty)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_FALSE(operation->getRequiredTokens());
}


TEST(HoI4World_Operations_OperationFactoryTests, RequiredTokensCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\trequired_tokens = {\n";
	input << "\t\ttest_required_tokens\n";
	input << "\t}\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ("= {\n\t\ttest_required_tokens\n\t}", operation->getRequiredTokens());
}


TEST(HoI4World_Operations_OperationFactoryTests, OnStartDefaultsToEmpty)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_FALSE(operation->getOnStart());
}


TEST(HoI4World_Operations_OperationFactoryTests, OnStartCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ton_start = {\n";
	input << "\t\ttest_on_start\n";
	input << "\t}\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ("= {\n\t\ttest_on_start\n\t}", operation->getOnStart());
}


TEST(HoI4World_Operations_OperationFactoryTests, WillLeadToWarWithDefaultsToFalse)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_FALSE(operation->getWillLeadToWarWith());
}


TEST(HoI4World_Operations_OperationFactoryTests, WillLeadToWarWithCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\twill_lead_to_war_with = yes\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_TRUE(operation->getWillLeadToWarWith());
}


TEST(HoI4World_Operations_OperationFactoryTests, RiskChanceDefaultsToZero)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_NEAR(0.0f, operation->getRiskChance(), 0.001);
}


TEST(HoI4World_Operations_OperationFactoryTests, RiskChanceCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\trisk_chance = 4.2\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_NEAR(4.2f, operation->getRiskChance(), 0.001);
}


TEST(HoI4World_Operations_OperationFactoryTests, OutcomeExtraChanceDefaultsToNullopt)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_FALSE(operation->getOutcomeExtraChance());
}


TEST(HoI4World_Operations_OperationFactoryTests, OutcomeExtraChanceCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\toutcome_extra_chance = 4.2\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_NEAR(4.2f, *operation->getOutcomeExtraChance(), 0.001);
}


TEST(HoI4World_Operations_OperationFactoryTests, RiskModifiersDefaultsToNullopt)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_FALSE(operation->getRiskModifiers());
}


TEST(HoI4World_Operations_OperationFactoryTests, RiskModifiersCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\trisk_modifiers = {\n";
	input << "\t\ttest_risk_modifier\n";
	input << "\t}\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ("= {\n\t\ttest_risk_modifier\n\t}", operation->getRiskModifiers());
}


TEST(HoI4World_Operations_OperationFactoryTests, OutcomeModifiersDefaultsToNullopt)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_FALSE(operation->getOutcomeModifiers());
}


TEST(HoI4World_Operations_OperationFactoryTests, OutcomeModifiersCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\toutcome_modifiers = {\n";
	input << "\t\ttest_outcome_modifier\n";
	input << "\t}\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ("= {\n\t\ttest_outcome_modifier\n\t}", operation->getOutcomeModifiers());
}


TEST(HoI4World_Operations_OperationFactoryTests, CostModifiersDefaultsToNullopt)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_FALSE(operation->getCostModifiers());
}


TEST(HoI4World_Operations_OperationFactoryTests, CostModifiersCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tcost_modifiers = {\n";
	input << "\t\ttest_cost_modifier\n";
	input << "\t}\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ("= {\n\t\ttest_cost_modifier\n\t}", operation->getCostModifiers());
}


TEST(HoI4World_Operations_OperationFactoryTests, ExperienceDefaultsToNullopt)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_FALSE(operation->getExperience());
}


TEST(HoI4World_Operations_OperationFactoryTests, ExperienceCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\texperience = 4.2\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_NEAR(4.2, *operation->getExperience(), 0.001);
}


TEST(HoI4World_Operations_OperationFactoryTests, CostMultiplierDefaultsToNullopt)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_FALSE(operation->getCostMultiplier());
}


TEST(HoI4World_Operations_OperationFactoryTests, CostMultiplierCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tcost_multiplier = 4.2\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_NEAR(4.2, *operation->getCostMultiplier(), 0.0001);
}


TEST(HoI4World_Operations_OperationFactoryTests, OutcomeExecuteDefaultsToEmpty)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_TRUE(operation->getOutcomeExecute().empty());
}


TEST(HoI4World_Operations_OperationFactoryTests, OutcomeExecuteCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\toutcome_execute = {\n";
	input << "\t\ttest_execute\n";
	input << "\t}\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ("= {\n\t\ttest_execute\n\t}", operation->getOutcomeExecute());
}


TEST(HoI4World_Operations_OperationFactoryTests, OutcomeExtraExecuteDefaultsToEmpty)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_FALSE(operation->getOutcomeExtraExecute());
}


TEST(HoI4World_Operations_OperationFactoryTests, OutcomeExtraExecuteCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\toutcome_extra_execute = {\n";
	input << "\t\ttest_extra_execute\n";
	input << "\t}\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ("= {\n\t\ttest_extra_execute\n\t}", *operation->getOutcomeExtraExecute());
}


TEST(HoI4World_Operations_OperationFactoryTests, OutcomePotentialDefaultsToEmpty)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_TRUE(operation->getOutcomePotential().empty());
}


TEST(HoI4World_Operations_OperationFactoryTests, OutcomePotentialCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\toutcome_potential = {\n";
	input << "\t\ttest_potential\n";
	input << "\t}\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ("= {\n\t\ttest_potential\n\t}", operation->getOutcomePotential());
}


TEST(HoI4World_Operations_OperationFactoryTests, TargetWeightDefaultsToEmpty)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_FALSE(operation->getTargetWeight());
}


TEST(HoI4World_Operations_OperationFactoryTests, TargetWeightCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ttarget_weight = {\n";
	input << "\t\ttest_target_weight\n";
	input << "\t}\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ("= {\n\t\ttest_target_weight\n\t}", *operation->getTargetWeight());
}


TEST(HoI4World_Operations_OperationFactoryTests, PhasesDefaultToEmpty)
{
	std::stringstream input;
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_TRUE(operation->getPhases().empty());
}


TEST(HoI4World_Operations_OperationFactoryTests, PhasesCanBeAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tphases = {\n";
	input << "\t\tphase_1\n";
	input << "\t}\n";
	input << "\tphases = {\n";
	input << "\t\tphase_2\n";
	input << "\t}\n";
	input << "}";
	const auto operation = HoI4::Operation::Factory().getOperation("operation_name", input);

	ASSERT_EQ(2, operation->getPhases().size());
	ASSERT_EQ("= {\n\t\tphase_1\n\t}", operation->getPhases()[0]);
	ASSERT_EQ("= {\n\t\tphase_2\n\t}", operation->getPhases()[1]);
}