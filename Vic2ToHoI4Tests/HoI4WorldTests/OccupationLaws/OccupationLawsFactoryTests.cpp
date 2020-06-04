#include "../Vic2ToHoI4/Source/HOI4World/OccupationLaws/OccupationLawsFactory.h"
#include "gtest/gtest.h"



TEST(HoI4World_OccupationLaws_OccupationLawsFactoryTests, ZeroLawsByDefault)
{
	std::stringstream input;
	const Configuration configuration("",
		 "",
		 "EmptyOccupationLaws/",
		 "",
		 {},
		 1.0,
		 1.0,
		 1.0,
		 1.0,
		 ideologyOptions::keep_major,
		 {},
		 false,
		 false,
		 false);
	const auto occupationLaws = HoI4::OccupationLaws::Factory{}.getOccupationLaws(configuration);

	ASSERT_TRUE(occupationLaws->getOccupationLaws().empty());
}


TEST(HoI4World_OccupationLaws_OccupationLawsFactoryTests, LawsCanBeImported)
{
	std::stringstream input;
	const Configuration configuration("",
		 "",
		 "OccupationLaws/",
		 "",
		 {},
		 1.0,
		 1.0,
		 1.0,
		 1.0,
		 ideologyOptions::keep_major,
		 {},
		 false,
		 false,
		 false);
	const auto occupationLaws = HoI4::OccupationLaws::Factory{}.getOccupationLaws(configuration);

	ASSERT_EQ(2, occupationLaws->getOccupationLaws().size());
	ASSERT_EQ("law_one", occupationLaws->getOccupationLaws()[0].getName());
	ASSERT_EQ("law_two", occupationLaws->getOccupationLaws()[1].getName());
}