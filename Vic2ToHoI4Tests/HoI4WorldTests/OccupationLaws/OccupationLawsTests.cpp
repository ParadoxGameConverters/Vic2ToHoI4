#include "../Vic2ToHoI4/Source/HOI4World/OccupationLaws/OccupationLaws.h"
#include "gtest/gtest.h"



TEST(HoI4World_OccupationLaws_OccupationLaws, AutonomousOccupationRemovedIfNoDemocractic)
{
	HoI4::OccupationLaw autonomousOccupation;
	autonomousOccupation.setName("autonomous_occupation");

	HoI4::OccupationLaws laws;
	laws.giveOccupationLaw(std::move(autonomousOccupation));

	laws.updateLaws({});
	ASSERT_TRUE(laws.getOccupationLaws().empty());
}


TEST(HoI4World_OccupationLaws_OccupationLaws, AutonomousOccupationRemainsIfDemocractic)
{
	HoI4::OccupationLaw autonomousOccupation;
	autonomousOccupation.setName("autonomous_occupation");

	HoI4::OccupationLaws laws;
	laws.giveOccupationLaw(std::move(autonomousOccupation));

	laws.updateLaws({"democratic"});
	ASSERT_FALSE(laws.getOccupationLaws().empty());
	ASSERT_EQ("autonomous_occupation", laws.getOccupationLaws()[0].getName());
}


TEST(HoI4World_OccupationLaws_OccupationLaws, LiberateWorkersOccupationRemovedIfNoCommunism)
{
	HoI4::OccupationLaw liberateWorkersOccupation;
	liberateWorkersOccupation.setName("liberate_workers_occupation");

	HoI4::OccupationLaws laws;
	laws.giveOccupationLaw(std::move(liberateWorkersOccupation));

	laws.updateLaws({});
	ASSERT_TRUE(laws.getOccupationLaws().empty());
}


TEST(HoI4World_OccupationLaws_OccupationLaws, LiberateWorkersOccupationRemainsIfCommunism)
{
	HoI4::OccupationLaw liberateWorkersOccupation;
	liberateWorkersOccupation.setName("liberate_workers_occupation");

	HoI4::OccupationLaws laws;
	laws.giveOccupationLaw(std::move(liberateWorkersOccupation));

	laws.updateLaws({"communism"});
	ASSERT_FALSE(laws.getOccupationLaws().empty());
	ASSERT_EQ("liberate_workers_occupation", laws.getOccupationLaws()[0].getName());
}


TEST(HoI4World_OccupationLaws_OccupationLaws, BrutallyOppressiveOccupationRemovedIfNoCommunism)
{
	HoI4::OccupationLaw brutallyOppressiveOccupation;
	brutallyOppressiveOccupation.setName("brutally_oppressive_occupation");

	HoI4::OccupationLaws laws;
	laws.giveOccupationLaw(std::move(brutallyOppressiveOccupation));

	laws.updateLaws({});
	ASSERT_TRUE(laws.getOccupationLaws().empty());
}


TEST(HoI4World_OccupationLaws_OccupationLaws, BrutallyOppressiveOccupationRemainsIfFascism)
{
	HoI4::OccupationLaw brutallyOppressiveOccupation;
	brutallyOppressiveOccupation.setName("brutally_oppressive_occupation");

	HoI4::OccupationLaws laws;
	laws.giveOccupationLaw(std::move(brutallyOppressiveOccupation));

	laws.updateLaws({"fascism"});
	ASSERT_FALSE(laws.getOccupationLaws().empty());
	ASSERT_EQ("brutally_oppressive_occupation", laws.getOccupationLaws()[0].getName());
}