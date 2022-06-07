#include "src/V2World/Diplomacy/Relations.h"
#include "src/V2World/Diplomacy/RelationsFactory.h"
#include "gtest/gtest.h"



TEST(Vic2World_Diplomacy_RelationsTests, ValueDefaultsToZero)
{
	std::stringstream input;
	const auto relations = Vic2::Relations::Factory().getRelations(input);

	ASSERT_EQ(0, relations->getRelations());
}


TEST(Vic2World_Diplomacy_RelationsTests, ValueCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tvalue = 42\n";
	input << "}";
	const auto relations = Vic2::Relations::Factory().getRelations(input);

	ASSERT_EQ(42, relations->getRelations());
}


TEST(Vic2World_Diplomacy_RelationsTests, LevelDefaultsToNeutral)
{
	std::stringstream input;
	const auto relations = Vic2::Relations::Factory().getRelations(input);

	ASSERT_EQ(Vic2::opinionLevel::neutral, relations->getLevel());
}


TEST(Vic2World_Diplomacy_RelationsTests, LevelCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tlevel = 1\n";
	input << "}";
	const auto relations = Vic2::Relations::Factory().getRelations(input);

	ASSERT_EQ(Vic2::opinionLevel::opposed, relations->getLevel());
}


TEST(Vic2World_Diplomacy_RelationsTests, MilitaryAccessDefaultsToFalse)
{
	std::stringstream input;
	const auto relations = Vic2::Relations::Factory().getRelations(input);

	ASSERT_FALSE(relations->hasMilitaryAccess());
}


TEST(Vic2World_Diplomacy_RelationsTests, MilitaryAccessCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tmilitary_access = yes\n";
	input << "}";
	const auto relations = Vic2::Relations::Factory().getRelations(input);

	ASSERT_TRUE(relations->hasMilitaryAccess());
}


TEST(Vic2World_Diplomacy_RelationsTests, LastSentDiplomatDefaultsToNullopt)
{
	std::stringstream input;
	const auto relations = Vic2::Relations::Factory().getRelations(input);

	ASSERT_FALSE(relations->getDiplomatLastSent());
}


TEST(Vic2World_Diplomacy_RelationsTests, LastSentDiplomatCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tlast_send_diplomat = \"1941.12.7\"\n";
	input << "}";
	const auto relations = Vic2::Relations::Factory().getRelations(input);

	ASSERT_TRUE(relations->getDiplomatLastSent());
	ASSERT_EQ(date(1941, 12, 7), *relations->getDiplomatLastSent());
}


TEST(Vic2World_Diplomacy_RelationsTests, LastWarDefaultsToNullopt)
{
	std::stringstream input;
	const auto relations = Vic2::Relations::Factory().getRelations(input);

	ASSERT_FALSE(relations->getLastWar());
}


TEST(Vic2World_Diplomacy_RelationsTests, LastWarCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tlast_war = \"1941.12.7\"\n";
	input << "}";
	const auto relations = Vic2::Relations::Factory().getRelations(input);

	ASSERT_TRUE(relations->getLastWar());
	ASSERT_EQ(date(1941, 12, 7), *relations->getLastWar());
}


TEST(Vic2World_Diplomacy_RelationsTests, TruceUntilDefaultsToNullopt)
{
	std::stringstream input;
	const auto relations = Vic2::Relations::Factory().getRelations(input);

	ASSERT_FALSE(relations->getTruceUntil());
}


TEST(Vic2World_Diplomacy_RelationsTests, TruceUntilCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ttruce_until = \"1941.12.7\"\n";
	input << "}";
	const auto relations = Vic2::Relations::Factory().getRelations(input);

	ASSERT_TRUE(relations->getTruceUntil());
	ASSERT_EQ(date(1941, 12, 7), *relations->getTruceUntil());
}


TEST(Vic2World_Diplomacy_RelationsTests, InfluenceValueDefaultsToZero)
{
	std::stringstream input;
	const auto relations = Vic2::Relations::Factory().getRelations(input);

	ASSERT_EQ(0, relations->getInfluenceValue());
}


TEST(Vic2World_Diplomacy_RelationsTests, InfluenceValueCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tinfluence_value = 42\n";
	input << "}";
	const auto relations = Vic2::Relations::Factory().getRelations(input);

	ASSERT_EQ(42, relations->getInfluenceValue());
}