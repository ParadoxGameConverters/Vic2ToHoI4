#include "V2World/Diplomacy/Diplomacy.h"
#include "V2World/Diplomacy/DiplomacyFactory.h"
#include "gtest/gtest.h"



TEST(Vic2World_Diplomacy_DiplomacyTests, AgreementsDefaultToEmpty)
{
	std::stringstream input;
	const auto diplomacy = Vic2::Diplomacy::Factory().getDiplomacy(input);

	ASSERT_TRUE(diplomacy->getAgreements().empty());
}


TEST(Vic2World_Diplomacy_DiplomacyTests, AgreementsCanBeAdded)
{
	std::stringstream input;
	input << "type_one = {}\n";
	input << "type_two = {}\n";
	const auto diplomacy = Vic2::Diplomacy::Factory().getDiplomacy(input);

	ASSERT_EQ(2, diplomacy->getAgreements().size());
	ASSERT_EQ("type_one", diplomacy->getAgreements()[0].getType());
	ASSERT_EQ("type_two", diplomacy->getAgreements()[1].getType());
}