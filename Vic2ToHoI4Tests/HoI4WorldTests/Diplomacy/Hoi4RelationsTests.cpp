#include "../Vic2ToHoI4/Source/HOI4World/Diplomacy/HoI4Relations.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Diplomacy_RelationsTests, tagCanBeSet)
{
	const HoI4::Relations relations("TAG");

	ASSERT_EQ(relations.getTag(), "TAG");
}


TEST(HoI4World_Diplomacy_RelationsTests, relationsDefaultsToZero)
{
	const HoI4::Relations relations("TAG");

	ASSERT_EQ(relations.getRelations(), 0);
}


TEST(HoI4World_Diplomacy_RelationsTests, relationsInheretedFromOldRelations)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tvalue = 56\n";
	input << "}";
	Vic2::Relations oldRelations("TAG", input);

	const HoI4::Relations relations("TAG", oldRelations);

	ASSERT_EQ(relations.getRelations(), 56);
}


TEST(HoI4World_Diplomacy_RelationsTests, guaranteeDefaultsToFalse)
{
	const HoI4::Relations relations("TAG");

	ASSERT_FALSE(relations.getGuarantee());
}


TEST(HoI4World_Diplomacy_RelationsTests, guaranteeTrueIfLevelEqualsFour)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tlevel = 4\n";
	input << "}";
	Vic2::Relations oldRelations("TAG", input);

	const HoI4::Relations relations("TAG", oldRelations);

	ASSERT_TRUE(relations.getGuarantee());
}


TEST(HoI4World_Diplomacy_RelationsTests, guaranteeTrueIfLevelGreaterThanFour)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tlevel = 5\n";
	input << "}";
	Vic2::Relations oldRelations("TAG", input);

	const HoI4::Relations relations("TAG", oldRelations);

	ASSERT_TRUE(relations.getGuarantee());
}


TEST(HoI4World_Diplomacy_RelationsTests, guaranteeFalseIfLevelLessThanFour)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tlevel = 3\n";
	input << "}";
	Vic2::Relations oldRelations("TAG", input);

	const HoI4::Relations relations("TAG", oldRelations);

	ASSERT_FALSE(relations.getGuarantee());
}


TEST(HoI4World_Diplomacy_RelationsTests, sphereLeaderDefaultsToFalse)
{
	const HoI4::Relations relations("TAG");

	ASSERT_FALSE(relations.getSphereLeader());
}


TEST(HoI4World_Diplomacy_RelationsTests, sphereLeaderTrueIfLevelEqualsFive)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tlevel = 5\n";
	input << "}";
	Vic2::Relations oldRelations("TAG", input);

	const HoI4::Relations relations("TAG", oldRelations);

	ASSERT_TRUE(relations.getSphereLeader());
}


TEST(HoI4World_Diplomacy_RelationsTests, sphereLeaderTrueIfLevelGreaterThanFive)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tlevel = 6\n";
	input << "}";
	Vic2::Relations oldRelations("TAG", input);

	const HoI4::Relations relations("TAG", oldRelations);

	ASSERT_TRUE(relations.getSphereLeader());
}


TEST(HoI4World_Diplomacy_RelationsTests, sphereLeaderFalseIfLevelLessThanFive)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tlevel = 4\n";
	input << "}";
	Vic2::Relations oldRelations("TAG", input);

	const HoI4::Relations relations("TAG", oldRelations);

	ASSERT_FALSE(relations.getSphereLeader());
}


TEST(HoI4World_Diplomacy_RelationsTests, influenceValueDefaultsToZero)
{
	const HoI4::Relations relations("TAG");

	ASSERT_EQ(relations.getInfluenceValue(), 0);
}


TEST(HoI4World_Diplomacy_RelationsTests, influenceValueInheretedFromOldRelations)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tinfluence_value = 56\n";
	input << "}";
	Vic2::Relations oldRelations("TAG", input);

	const HoI4::Relations relations("TAG", oldRelations);

	ASSERT_EQ(relations.getInfluenceValue(), 56);
}