#include "../Vic2ToHoI4/Source/HOI4World/IntelligenceAgencies/IntelligenceAgencyLogos.h"
#include "gtest/gtest.h"
#include <sstream>



class HoI4World_IntelligenceAgencies_IntelligenceAgencyLogosTests: public testing::Test
{
  protected:
	HoI4World_IntelligenceAgencies_IntelligenceAgencyLogosTests();

	std::unique_ptr<HoI4::IntelligenceAgencyLogos> logos;
};


HoI4World_IntelligenceAgencies_IntelligenceAgencyLogosTests::
	 HoI4World_IntelligenceAgencies_IntelligenceAgencyLogosTests():
	 logos(HoI4::IntelligenceAgencyLogos::Factory{}.getIntelligenceAgencyLogos())
{
}


TEST_F(HoI4World_IntelligenceAgencies_IntelligenceAgencyLogosTests, UnmappedCultureGetsGenericLogo)
{
	ASSERT_EQ("GFX_intelligence_agency_logo_generic_1", logos->getLogo("unmapped_culture"));
}


TEST_F(HoI4World_IntelligenceAgencies_IntelligenceAgencyLogosTests, LogoCanBeMappedToCulture)
{
	ASSERT_EQ("GFX_intelligence_agency_logo_ger", logos->getLogo("north_german"));
}