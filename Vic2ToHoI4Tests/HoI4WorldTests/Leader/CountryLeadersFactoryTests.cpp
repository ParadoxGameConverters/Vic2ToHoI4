#include "HOI4World/Leaders/CountryLeadersFactory.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Leaders_CountryLeadersFactoryTests, LeadersCanBeImported)
{
	const auto leaders = HoI4::CountryLeadersFactory().importCountryLeaders();

	ASSERT_EQ(1, leaders.count("ONE"));
	ASSERT_EQ(2, leaders.count("TWO"));
}