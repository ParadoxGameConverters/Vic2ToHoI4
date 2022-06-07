#include "src/HOI4World/Diplomacy/HoI4Relations.h"
#include "src/V2World/Diplomacy/RelationsBuilder.h"
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
	const HoI4::Relations relations("TAG", *Vic2::Relations::Builder().setValue(56).build(), date());

	ASSERT_EQ(relations.getRelations(), 56);
}


TEST(HoI4World_Diplomacy_RelationsTests, guaranteeDefaultsToFalse)
{
	const HoI4::Relations relations("TAG");

	ASSERT_FALSE(relations.getGuarantee());
}


TEST(HoI4World_Diplomacy_RelationsTests, guaranteeTrueIfLevelIsFriendly)
{
	const HoI4::Relations relations("TAG",
		 *Vic2::Relations::Builder().setLevel(Vic2::opinionLevel::friendly).build(),
		 date());

	ASSERT_TRUE(relations.getGuarantee());
}


TEST(HoI4World_Diplomacy_RelationsTests, guaranteeTrueIfLevelAboveFriendly)
{
	const HoI4::Relations relations("TAG",
		 *Vic2::Relations::Builder().setLevel(Vic2::opinionLevel::in_sphere).build(),
		 date());

	ASSERT_TRUE(relations.getGuarantee());
}


TEST(HoI4World_Diplomacy_RelationsTests, guaranteeFalseIfLevelBelowFriendly)
{
	const HoI4::Relations relations("TAG",
		 *Vic2::Relations::Builder().setLevel(Vic2::opinionLevel::neutral).build(),
		 date());

	ASSERT_FALSE(relations.getGuarantee());
}


TEST(HoI4World_Diplomacy_RelationsTests, sphereLeaderDefaultsToFalse)
{
	const HoI4::Relations relations("TAG");

	ASSERT_FALSE(relations.getSphereLeader());
}


TEST(HoI4World_Diplomacy_RelationsTests, sphereLeaderTrueIfLevelEqualsInSphere)
{
	const HoI4::Relations relations("TAG",
		 *Vic2::Relations::Builder().setLevel(Vic2::opinionLevel::in_sphere).build(),
		 date());

	ASSERT_TRUE(relations.getSphereLeader());
}


TEST(HoI4World_Diplomacy_RelationsTests, sphereLeaderFalseIfLevelLessThanInSphere)
{
	const HoI4::Relations relations("TAG",
		 *Vic2::Relations::Builder().setLevel(Vic2::opinionLevel::friendly).build(),
		 date());

	ASSERT_FALSE(relations.getSphereLeader());
}


TEST(HoI4World_Diplomacy_RelationsTests, influenceValueDefaultsToZero)
{
	const HoI4::Relations relations("TAG");

	ASSERT_EQ(relations.getInfluenceValue(), 0);
}


TEST(HoI4World_Diplomacy_RelationsTests, influenceValueInheritedFromOldRelations)
{
	const HoI4::Relations relations("TAG", *Vic2::Relations::Builder().setInfluenceValue(56).build(), date());

	ASSERT_EQ(relations.getInfluenceValue(), 56);
}


TEST(HoI4World_Diplomacy_RelationsTests, hasMilitaryAccessDefaultsToFalse)
{
	const HoI4::Relations relations("TAG");

	ASSERT_FALSE(relations.hasMilitaryAccess());
}


TEST(HoI4World_Diplomacy_RelationsTests, hasMilitaryAccessInheritedFromOldMilitaryAccess)
{
	const HoI4::Relations relationsWithAccess("TAG",
		 *Vic2::Relations::Builder().setMilitaryAccess(true).build(),
		 date());
	ASSERT_TRUE(relationsWithAccess.hasMilitaryAccess());

	const HoI4::Relations relationsWithoutAccess("TAG",
		 *Vic2::Relations::Builder().setMilitaryAccess(false).build(),
		 date());
	ASSERT_FALSE(relationsWithoutAccess.hasMilitaryAccess());
}


TEST(HoI4World_Diplomacy_RelationsTests, truceUntilDefaultsToNullopt)
{
	const HoI4::Relations relations("TAG");

	ASSERT_EQ(relations.getTruceUntil(), std::nullopt);
}


TEST(HoI4World_Diplomacy_RelationsTests, truceUntilInheritedFromOldRelations)
{
	const HoI4::Relations relations("TAG", *Vic2::Relations::Builder().setTruceUntil(date("1939.1.1")).build(), date());

	ASSERT_EQ(relations.getTruceUntil()->toString(), "1939.1.1");
}


TEST(HoI4World_Diplomacy_RelationsTests, truceDurationDefaultsToNullopt)
{
	const HoI4::Relations relations("TAG");

	ASSERT_EQ(relations.getTruceDuration(), std::nullopt);
}


TEST(HoI4World_Diplomacy_RelationsTests, truceDurationCanBeSet)
{
	const HoI4::Relations relations("TAG",
		 *Vic2::Relations::Builder().setTruceUntil(date("1939.1.1")).build(),
		 date("1936.1.1"));

	ASSERT_EQ(*relations.getTruceDuration(), 1095);
}


TEST(HoI4World_Diplomacy_RelationsTests, expiredTrucesDontSetTruceDuration)
{
	const HoI4::Relations relations("TAG",
		 *Vic2::Relations::Builder().setTruceUntil(date("1888.1.1")).build(),
		 date("1936.1.1"));

	ASSERT_EQ(relations.getTruceDuration(), std::nullopt);
}