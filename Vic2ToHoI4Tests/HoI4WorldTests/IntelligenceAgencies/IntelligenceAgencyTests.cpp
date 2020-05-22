#include "../Vic2ToHoI4/Source/HOI4World/IntelligenceAgencies/IntelligenceAgency.h"
#include "gtest/gtest.h"



TEST(HoI4World_IntelligenceAgencies_IntelligenceAgencyTests, CountryCanBeSet)
{
	const HoI4::IntelligenceAgency agency("TAG");

	ASSERT_EQ("TAG", agency.getCountry());
}