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