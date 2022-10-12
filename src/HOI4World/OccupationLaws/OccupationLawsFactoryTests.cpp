#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/OccupationLaws/OccupationLawsFactory.h"



TEST(HoI4World_OccupationLaws_OccupationLawsFactoryTests, LawsCanBeImported)
{
	const auto occupationLaws = HoI4::OccupationLaws::Factory().getOccupationLaws();

	ASSERT_EQ(2, occupationLaws->getOccupationLaws().size());
	ASSERT_EQ("law_one", occupationLaws->getOccupationLaws()[0].getName());
	ASSERT_EQ("law_two", occupationLaws->getOccupationLaws()[1].getName());
}