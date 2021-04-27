#include "V2World/Military/Leaders/Leader.h"
#include "V2World/Military/Leaders/LeaderFactory.h"
#include "V2World/Military/Leaders/Traits.h"
#include "V2World/Military/Leaders/TraitsBuilder.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Vic2World_Military_LeaderTests, NameDefaultsToEmpty)
{
	std::stringstream input;
	const auto leader = Vic2::Leader::Factory(Vic2::Traits{}).getLeader(input);

	ASSERT_TRUE(leader->getName().empty());
}


TEST(Vic2World_Military_LeaderTests, NameCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tname = test_name\n";
	input << "}";
	const auto leader = Vic2::Leader::Factory(Vic2::Traits{}).getLeader(input);

	ASSERT_EQ("test_name", leader->getName());
}


TEST(Vic2World_Military_LeaderTests, TypeDefaultsToEmpty)
{
	std::stringstream input;
	const auto leader = Vic2::Leader::Factory(Vic2::Traits{}).getLeader(input);

	ASSERT_TRUE(leader->getType().empty());
}


TEST(Vic2World_Military_LeaderTests, TypeCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ttype = test_type\n";
	input << "}";
	const auto leader = Vic2::Leader::Factory(Vic2::Traits{}).getLeader(input);

	ASSERT_EQ("test_type", leader->getType());
}


TEST(Vic2World_Military_LeaderTests, TraitEffectValueIsZeroForMissingTraits)
{
	std::stringstream input;
	const auto leader = Vic2::Leader::Factory(Vic2::Traits{}).getLeader(input);

	ASSERT_EQ(0.0F, leader->getTraitEffectValue("missing_trait"));
}


TEST(Vic2World_Military_LeaderTests, TraitEffectValueFromPersonality)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tpersonality = test_personality\n";
	input << "}";

	const auto leader =
		 Vic2::Leader::Factory(
			  std::move(
					*Vic2::Traits::Builder().addTrait("test_personality", {{"effect_1", 0.5}, {"effect_2", -0.25}}).Build()))
			  .getLeader(input);

	ASSERT_EQ(0.5, leader->getTraitEffectValue("effect_1"));
	ASSERT_EQ(-0.25, leader->getTraitEffectValue("effect_2"));
}


TEST(Vic2World_Military_LeaderTests, TraitEffectValueFromBackground)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tbackground = test_background\n";
	input << "}";

	const auto leader =
		 Vic2::Leader::Factory(
			  std::move(
					*Vic2::Traits::Builder().addTrait("test_background", {{"effect_1", 0.5}, {"effect_2", -0.25}}).Build()))
			  .getLeader(input);

	ASSERT_EQ(0.5, leader->getTraitEffectValue("effect_1"));
	ASSERT_EQ(-0.25, leader->getTraitEffectValue("effect_2"));
}


TEST(Vic2World_Military_LeaderTests, TraitEffectValueFromBackgroundAndPersonality)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tpersonality = test_personality\n";
	input << "\tbackground = test_background\n";
	input << "}";

	const auto leader =
		 Vic2::Leader::Factory(std::move(*Vic2::Traits::Builder()
														  .addTrait("test_background", {{"effect_1", 0.5}, {"effect_2", -0.25}})
														  .addTrait("test_personality", {{"effect_1", 0.5}, {"effect_2", -0.25}})
														  .Build()))
			  .getLeader(input);

	ASSERT_EQ(1.0, leader->getTraitEffectValue("effect_1"));
	ASSERT_EQ(-0.5, leader->getTraitEffectValue("effect_2"));
}


TEST(Vic2World_Military_LeaderTests, PrestigeDefaultsToZero)
{
	std::stringstream input;
	const auto leader = Vic2::Leader::Factory(Vic2::Traits{}).getLeader(input);

	ASSERT_EQ(0.0F, leader->getPrestige());
}


TEST(Vic2World_Military_LeaderTests, PrestigeCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tprestige = 0.42\n";
	input << "}";
	const auto leader = Vic2::Leader::Factory(Vic2::Traits{}).getLeader(input);

	ASSERT_NEAR(0.42, leader->getPrestige(), 0.00001);
}