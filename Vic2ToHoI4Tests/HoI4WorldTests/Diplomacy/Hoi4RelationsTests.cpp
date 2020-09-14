#include "../Vic2ToHoI4/Source/HOI4World/Diplomacy/HoI4Relations.h"
#include "../Vic2ToHoI4/Source/V2World/Diplomacy/RelationsBuilder.h"
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
	const HoI4::Relations relations("TAG", *Vic2::Relations::Builder{}.setValue(56).build());

	ASSERT_EQ(relations.getRelations(), 56);
}


TEST(HoI4World_Diplomacy_RelationsTests, guaranteeDefaultsToFalse)
{
	const HoI4::Relations relations("TAG");

	ASSERT_FALSE(relations.getGuarantee());
}


TEST(HoI4World_Diplomacy_RelationsTests, guaranteeTrueIfLevelIsFriendly)
{
	const HoI4::Relations relations("TAG", *Vic2::Relations::Builder{}.setLevel(Vic2::opinionLevel::friendly).build());

	ASSERT_TRUE(relations.getGuarantee());
}


TEST(HoI4World_Diplomacy_RelationsTests, guaranteeTrueIfLevelAboveFriendly)
{
	const HoI4::Relations relations("TAG", *Vic2::Relations::Builder{}.setLevel(Vic2::opinionLevel::in_sphere).build());

	ASSERT_TRUE(relations.getGuarantee());
}


TEST(HoI4World_Diplomacy_RelationsTests, guaranteeFalseIfLevelBelowFriendly)
{
	const HoI4::Relations relations("TAG", *Vic2::Relations::Builder{}.setLevel(Vic2::opinionLevel::neutral).build());

	ASSERT_FALSE(relations.getGuarantee());
}


TEST(HoI4World_Diplomacy_RelationsTests, sphereLeaderDefaultsToFalse)
{
	const HoI4::Relations relations("TAG");

	ASSERT_FALSE(relations.getSphereLeader());
}


TEST(HoI4World_Diplomacy_RelationsTests, sphereLeaderTrueIfLevelEqualsInSphere)
{
	const HoI4::Relations relations("TAG", *Vic2::Relations::Builder{}.setLevel(Vic2::opinionLevel::in_sphere).build());

	ASSERT_TRUE(relations.getSphereLeader());
}


TEST(HoI4World_Diplomacy_RelationsTests, sphereLeaderFalseIfLevelLessThanInSphere)
{
	const HoI4::Relations relations("TAG", *Vic2::Relations::Builder{}.setLevel(Vic2::opinionLevel::friendly).build());

	ASSERT_FALSE(relations.getSphereLeader());
}


TEST(HoI4World_Diplomacy_RelationsTests, influenceValueDefaultsToZero)
{
	const HoI4::Relations relations("TAG");

	ASSERT_EQ(relations.getInfluenceValue(), 0);
}


TEST(HoI4World_Diplomacy_RelationsTests, influenceValueInheretedFromOldRelations)
{
	const HoI4::Relations relations("TAG", *Vic2::Relations::Builder{}.setInfluenceValue(56).build());

	ASSERT_EQ(relations.getInfluenceValue(), 56);
}