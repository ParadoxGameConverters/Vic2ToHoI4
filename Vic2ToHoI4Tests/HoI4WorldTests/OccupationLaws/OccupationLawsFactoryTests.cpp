#include "HOI4World/OccupationLaws/OccupationLawsFactory.h"
#include "gtest/gtest.h"



TEST(HoI4World_OccupationLaws_OccupationLawsFactoryTests, ZeroLawsByDefault)
{
	const auto configuration = Configuration::Builder{}.setHoI4Path("EmptyOccupationLaws/").build();
	const auto occupationLaws = HoI4::OccupationLaws::Factory().getOccupationLaws(*configuration);

	ASSERT_TRUE(occupationLaws->getOccupationLaws().empty());
}


TEST(HoI4World_OccupationLaws_OccupationLawsFactoryTests, LawsCanBeImported)
{
	const auto configuration = Configuration::Builder{}.setHoI4Path("OccupationLaws/").build();
	const auto occupationLaws = HoI4::OccupationLaws::Factory().getOccupationLaws(*configuration);

	ASSERT_EQ(2, occupationLaws->getOccupationLaws().size());
	ASSERT_EQ("law_one", occupationLaws->getOccupationLaws()[0].getName());
	ASSERT_EQ("law_two", occupationLaws->getOccupationLaws()[1].getName());
}