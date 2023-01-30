#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/OccupationLaws/OccupationLaws.h"



TEST(HoI4World_OccupationLaws_OccupationLaws, ReconciliationRemoved)
{
	HoI4::OccupationLaw reconciliationOccupation;
	reconciliationOccupation.setName("reconciliation");

	HoI4::OccupationLaws laws;
	laws.giveOccupationLaw(std::move(reconciliationOccupation));

	laws.updateLaws({});
	ASSERT_TRUE(laws.getOccupationLaws().empty());
}


TEST(HoI4World_OccupationLaws_OccupationLaws, NoGarrisonSimplifiesAiWillDoIfNoDemocratic)
{
	HoI4::OccupationLaw noGarrison;
	noGarrison.setName("no_garrison");

	HoI4::OccupationLaws laws;
	laws.giveOccupationLaw(std::move(noGarrison));

	laws.updateLaws({});
	ASSERT_FALSE(laws.getOccupationLaws().empty());
	ASSERT_EQ(
		 "= {\n"
		 "\t\tbase = 0\n"
		 "\n"
		 "\t\t# if losing, get manpower & equipment back\n"
		 "\t\tmodifier = {\n"
		 "\t\t\tFROM = {\n"
		 "\t\t\t\tsurrender_progress > 0.15\n"
		 "\t\t\t}\n"
		 "\t\t\tadd = 100\n"
		 "\t\t}\n"
		 "\t\tmodifier = {\n"
		 "\t\t\tFROM = {\n"
		 "\t\t\t\tsurrender_progress > 0.4\n"
		 "\t\t\t}\n"
		 "\t\t\tadd = 500\n"
		 "\t\t}\n"
		 "\t}",
		 laws.getOccupationLaws()[0].getAiWillDo());
}


TEST(HoI4World_OccupationLaws_OccupationLaws, NoGarrisonLeavesAiWillDoIfDemocratic)
{
	HoI4::OccupationLaw noGarrison;
	noGarrison.setName("no_garrison");
	noGarrison.setAiWillDo(" = { test }");

	HoI4::OccupationLaws laws;
	laws.giveOccupationLaw(std::move(noGarrison));

	laws.updateLaws({"democratic"});
	ASSERT_FALSE(laws.getOccupationLaws().empty());
	ASSERT_EQ(" = { test }", laws.getOccupationLaws()[0].getAiWillDo());
}


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


TEST(HoI4World_OccupationLaws_OccupationLaws, BrutallyOppressiveOccupationRemovedIfNoFascism)
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