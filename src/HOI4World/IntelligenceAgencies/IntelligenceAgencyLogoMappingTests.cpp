#include "src/HOI4World/IntelligenceAgencies/IntelligenceAgencyLogoMapping.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include <sstream>



TEST(HoI4World_IntelligenceAgencies_IntelligenceAgencyLogoMappingTests, CulturesDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::IntelligenceAgencyLogoMapping mapping(input);

	ASSERT_TRUE(mapping.takeCultures().empty());
}


TEST(HoI4World_IntelligenceAgencies_IntelligenceAgencyLogoMappingTests, CulturesCanBeInput)
{
	std::stringstream input;
	input << "culture = portuguese culture = brazilian";
	HoI4::IntelligenceAgencyLogoMapping mapping(input);

	ASSERT_EQ(2, mapping.takeCultures().size());
	ASSERT_EQ("portuguese", mapping.takeCultures()[0]);
	ASSERT_EQ("brazilian", mapping.takeCultures()[1]);
}


TEST(HoI4World_IntelligenceAgencies_IntelligenceAgencyLogoMappingTests, LogoDefaultsToGenericOne)
{
	std::stringstream input;
	HoI4::IntelligenceAgencyLogoMapping mapping(input);

	ASSERT_EQ("GFX_intelligence_agency_logo_generic_1", mapping.getLogo());
}


TEST(HoI4World_IntelligenceAgencies_IntelligenceAgencyLogoMappingTests, LogoCanBeSet)
{
	std::stringstream input;
	input << "logo = test_logo";
	HoI4::IntelligenceAgencyLogoMapping mapping(input);

	ASSERT_EQ("test_logo", mapping.getLogo());
}


TEST(HoI4World_IntelligenceAgencies_IntelligenceAgencyLogoMappingTests, LogoCanBeGotenMultipleTimes)
{
	std::stringstream input;
	input << "logo = test_logo";
	HoI4::IntelligenceAgencyLogoMapping mapping(input);

	const auto unused = mapping.getLogo();
	ASSERT_EQ("test_logo", mapping.getLogo());
}