#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/Politics/Party.h"
#include "src/V2World/Politics/PartyFactory.h"
#include <sstream>



TEST(Vic2World_Politics_PartyTests, NameDefaultsToEmpty)
{
	std::stringstream input;
	const auto party = Vic2::Party::Factory().getParty(input);

	ASSERT_TRUE(party->getName().empty());
}


TEST(Vic2World_Politics_PartyTests, NameCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tname = \"test_name\"\n";
	input << "}";
	const auto party = Vic2::Party::Factory().getParty(input);

	ASSERT_EQ("test_name", party->getName());
}


TEST(Vic2World_Politics_PartyTests, IdeologyDefaultsToConservative)
{
	std::stringstream input;
	const auto party = Vic2::Party::Factory().getParty(input);

	ASSERT_EQ("conservative", party->getIdeology());
}


TEST(Vic2World_Politics_PartyTests, IdeologyCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tideology = \"test_ideology\"\n";
	input << "}";
	const auto party = Vic2::Party::Factory().getParty(input);

	ASSERT_EQ("test_ideology", party->getIdeology());
}


TEST(Vic2World_Politics_PartyTests, EconomicPolicyDefaultsToInterventionism)
{
	std::stringstream input;
	const auto party = Vic2::Party::Factory().getParty(input);

	ASSERT_EQ("interventionism", party->getEconomicPolicy());
}


TEST(Vic2World_Politics_PartyTests, EconomicPolicyCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\teconomic_policy = \"test_policy\"\n";
	input << "}";
	const auto party = Vic2::Party::Factory().getParty(input);

	ASSERT_EQ("test_policy", party->getEconomicPolicy());
}


TEST(Vic2World_Politics_PartyTests, TradePolicyDefaultsToProtectionism)
{
	std::stringstream input;
	const auto party = Vic2::Party::Factory().getParty(input);

	ASSERT_EQ("protectionism", party->getTradePolicy());
}


TEST(Vic2World_Politics_PartyTests, TradePolicyCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ttrade_policy = \"test_policy\"\n";
	input << "}";
	const auto party = Vic2::Party::Factory().getParty(input);

	ASSERT_EQ("test_policy", party->getTradePolicy());
}


TEST(Vic2World_Politics_PartyTests, ReligiousPolicyDefaultsToMoralism)
{
	std::stringstream input;
	const auto party = Vic2::Party::Factory().getParty(input);

	ASSERT_EQ("moralism", party->getReligiousPolicy());
}


TEST(Vic2World_Politics_PartyTests, ReligiousPolicyCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\treligious_policy = \"test_policy\"\n";
	input << "}";
	const auto party = Vic2::Party::Factory().getParty(input);

	ASSERT_EQ("test_policy", party->getReligiousPolicy());
}


TEST(Vic2World_Politics_PartyTests, CitizenshipPolicyDefaultsToResidency)
{
	std::stringstream input;
	const auto party = Vic2::Party::Factory().getParty(input);

	ASSERT_EQ("residency", party->getCitizenshipPolicy());
}


TEST(Vic2World_Politics_PartyTests, CitizenshipPolicyCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tcitizenship_policy = \"test_policy\"\n";
	input << "}";
	const auto party = Vic2::Party::Factory().getParty(input);

	ASSERT_EQ("test_policy", party->getCitizenshipPolicy());
}


TEST(Vic2World_Politics_PartyTests, WarPolicyDefaultsToProMilitary)
{
	std::stringstream input;
	const auto party = Vic2::Party::Factory().getParty(input);

	ASSERT_EQ("pro_military", party->getWarPolicy());
}


TEST(Vic2World_Politics_PartyTests, WarPolicyCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\twar_policy = \"test_policy\"\n";
	input << "}";
	const auto party = Vic2::Party::Factory().getParty(input);

	ASSERT_EQ("test_policy", party->getWarPolicy());
}


TEST(Vic2World_Politics_PartyTests, EqualityIsFromName)
{
	Vic2::Party::Factory partyFactory;

	std::stringstream input;
	input << "= {\n";
	input << "\tname = \"test_name\"\n";
	input << "}";
	const auto party = *partyFactory.getParty(input);

	std::stringstream equalInput;
	equalInput << "= {\n";
	equalInput << "\tname = \"test_name\"\n";
	equalInput << "}";
	const auto equalParty = *partyFactory.getParty(equalInput);

	std::stringstream unequalInput;
	unequalInput << "= {\n";
	unequalInput << "\tname = \"other_name\"\n";
	unequalInput << "}";
	const auto unequalParty = *partyFactory.getParty(unequalInput);

	ASSERT_EQ(party, equalParty);
}


TEST(Vic2World_Politics_PartyTests, OrderIsFromName)
{
	Vic2::Party::Factory partyFactory;

	std::stringstream input;
	input << "= {\n";
	input << "\tname = \"test_name\"\n";
	input << "}";
	const auto party = *partyFactory.getParty(input);

	std::stringstream laterInput;
	laterInput << "= {\n";
	laterInput << "\tname = \"z_test_name\"\n";
	laterInput << "}";
	const auto laterParty = *partyFactory.getParty(laterInput);

	std::stringstream earlierInput;
	earlierInput << "= {\n";
	earlierInput << "\tname = \"a_test_name\"\n";
	earlierInput << "}";
	const auto earlierParty = *partyFactory.getParty(earlierInput);

	ASSERT_LT(party, laterParty);
	ASSERT_LT(earlierParty, party);
}