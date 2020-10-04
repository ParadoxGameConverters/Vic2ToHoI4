#include "../../Vic2ToHoI4/Source/V2World/Military/Leader.h"
#include "../../Vic2ToHoI4/Source/V2World/Military/LeaderFactory.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(Vic2World_Military_LeaderTests, NameDefaultsToEmpty)
{
	std::stringstream input;
	const auto leader = Vic2::Leader::Factory{}.getLeader(input);

	ASSERT_TRUE(leader->getName().empty());
}


TEST(Vic2World_Military_LeaderTests, NameCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tname = test_name\n";
	input << "}";
	const auto leader = Vic2::Leader::Factory{}.getLeader(input);

	ASSERT_EQ("test_name", leader->getName());
}


TEST(Vic2World_Military_LeaderTests, TypeDefaultsToEmpty)
{
	std::stringstream input;
	const auto leader = Vic2::Leader::Factory{}.getLeader(input);

	ASSERT_TRUE(leader->getType().empty());
}


TEST(Vic2World_Military_LeaderTests, TypeCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ttype = test_type\n";
	input << "}";
	const auto leader = Vic2::Leader::Factory{}.getLeader(input);

	ASSERT_EQ("test_type", leader->getType());
}


TEST(Vic2World_Military_LeaderTests, PersonalityDefaultsToEmpty)
{
	std::stringstream input;
	const auto leader = Vic2::Leader::Factory{}.getLeader(input);

	ASSERT_TRUE(leader->getPersonality().empty());
}


TEST(Vic2World_Military_LeaderTests, PersonalityCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tpersonality = test_personality\n";
	input << "}";
	const auto leader = Vic2::Leader::Factory{}.getLeader(input);

	ASSERT_EQ("test_personality", leader->getPersonality());
}


TEST(Vic2World_Military_LeaderTests, BackgroundDefaultsToEmpty)
{
	std::stringstream input;
	const auto leader = Vic2::Leader::Factory{}.getLeader(input);

	ASSERT_TRUE(leader->getBackground().empty());
}


TEST(Vic2World_Military_LeaderTests, BackgroundCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tbackground = test_background\n";
	input << "}";
	const auto leader = Vic2::Leader::Factory{}.getLeader(input);

	ASSERT_EQ("test_background", leader->getBackground());
}


TEST(Vic2World_Military_LeaderTests, PrestigeDefaultsToZero)
{
	std::stringstream input;
	const auto leader = Vic2::Leader::Factory{}.getLeader(input);

	ASSERT_EQ(0.0F, leader->getPrestige());
}


TEST(Vic2World_Military_LeaderTests, PrestigeCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tprestige = 0.42\n";
	input << "}";
	const auto leader = Vic2::Leader::Factory{}.getLeader(input);

	ASSERT_NEAR(0.42, leader->getPrestige(), 0.00001);
}