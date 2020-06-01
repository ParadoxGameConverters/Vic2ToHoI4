#include "../Vic2ToHoI4/Source/HOI4World/OccupationLaws/OccupationLawFactory.h"
#include "gtest/gtest.h"



TEST(HoI4World_OccupationLaws_OccupationLawFactoryTests, NameCanBeSet)
{
	std::stringstream input;
	const auto occupationLaw = HoI4::OccupationLaw::Factory{}.getOccupationLaw("law_name", input);

	ASSERT_EQ("law_name", occupationLaw->getName());
}