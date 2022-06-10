#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/Mappers/Country/CountryMapper.h"
#include "src/Mappers/Country/CountryMapperBuilder.h"
#include "src/Mappers/Country/CountryMapperFactory.h"
#include "src/V2World/Countries/CountryBuilder.h"
#include "src/V2World/World/WorldBuilder.h"



TEST(Mappers_Country_CountryMapperTests, UnmatchedVic2TagReturnsNullopt)
{
	const auto mapper = Mappers::CountryMapper::Builder().Build();

	ASSERT_EQ(std::nullopt, mapper->getHoI4Tag("NON"));
}


TEST(Mappers_Country_CountryMapperTests, MatchedVic2TagReturnsHoI4Tag)
{
	const auto mapper = Mappers::CountryMapper::Builder().addMapping("VIC", "HOI").Build();

	ASSERT_EQ("HOI", mapper->getHoI4Tag("VIC"));
}


TEST(Mappers_Country_CountryMapperTests, MappingCanBeGivenFromRule)
{
	const auto mapper = Mappers::CountryMapper::Factory().importCountryMapper(
		 *Vic2::World::Builder().addCountry("AAA", *Vic2::Country::Builder().Build()).Build(),
		 false);

	ASSERT_EQ("HOI", mapper->getHoI4Tag("AAA"));
}


TEST(Mappers_Country_CountryMapperTests, RuleMappingIsLogged)
{
	std::stringstream log;
	auto stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const auto mapper = Mappers::CountryMapper::Factory().importCountryMapper(
		 *Vic2::World::Builder().addCountry("AAA", *Vic2::Country::Builder().Build()).Build(),
		 true);

	std::cout.rdbuf(stdOutBuf);

	ASSERT_EQ(log.str(),
		 "    [INFO] Getting country mappings\n"
		 "    [INFO] \tReading country mapping rules\n"
		 "    [INFO] \tCreating country mappings\n"
		 "   [DEBUG]     Mapping AAA -> HOI (mapping rule)\n");
}


TEST(Mappers_Country_CountryMapperTests, UsedHoI4TagForcesGeneratedTag)
{
	const auto mapper =
		 Mappers::CountryMapper::Factory().importCountryMapper(*Vic2::World::Builder()
																						.addCountry("AAA", *Vic2::Country::Builder().Build())
																						.addCountry("BBB", *Vic2::Country::Builder().Build())
																						.Build(),
			  false);

	ASSERT_EQ("HOI", mapper->getHoI4Tag("AAA"));
	ASSERT_EQ("X00", mapper->getHoI4Tag("BBB"));
}


TEST(Mappers_Country_CountryMapperTests, NoRulesMeansGeneratedTag)
{
	const auto mapper = Mappers::CountryMapper::Factory().importCountryMapper(
		 *Vic2::World::Builder().addCountry("CCC", *Vic2::Country::Builder().Build()).Build(),
		 false);

	ASSERT_EQ("X00", mapper->getHoI4Tag("CCC"));
}


TEST(Mappers_Country_CountryMapperTests, GeneratedMappingIsLogged)
{
	std::stringstream log;
	auto stdOutBuf = std::cout.rdbuf();
	std::cout.rdbuf(log.rdbuf());

	const auto mapper = Mappers::CountryMapper::Factory().importCountryMapper(
		 *Vic2::World::Builder().addCountry("CCC", *Vic2::Country::Builder().Build()).Build(),
		 true);

	std::cout.rdbuf(stdOutBuf);

	ASSERT_EQ(log.str(),
		 "    [INFO] Getting country mappings\n"
		 "    [INFO] \tReading country mapping rules\n"
		 "    [INFO] \tCreating country mappings\n"
		 "   [DEBUG]     Mapping CCC -> X00 (generated tag)\n");
}


TEST(Mappers_Country_CountryMapperTests, GeneratedTagSuffixesIncrease)
{
	const auto mapper =
		 Mappers::CountryMapper::Factory().importCountryMapper(*Vic2::World::Builder()
																						.addCountry("CCC", *Vic2::Country::Builder().Build())
																						.addCountry("DDD", *Vic2::Country::Builder().Build())
																						.Build(),
			  false);

	ASSERT_EQ("X00", mapper->getHoI4Tag("CCC"));
	ASSERT_EQ("X01", mapper->getHoI4Tag("DDD"));
}


TEST(Mappers_Country_CountryMapperTests, GeneratedTagPrefixesDecrease)
{
	const auto mapper =
		 Mappers::CountryMapper::Factory().importCountryMapper(*Vic2::World::Builder()
																						.addCountry("A00", *Vic2::Country::Builder().Build())
																						.addCountry("A01", *Vic2::Country::Builder().Build())
																						.addCountry("A02", *Vic2::Country::Builder().Build())
																						.addCountry("A03", *Vic2::Country::Builder().Build())
																						.addCountry("A04", *Vic2::Country::Builder().Build())
																						.addCountry("A05", *Vic2::Country::Builder().Build())
																						.addCountry("A06", *Vic2::Country::Builder().Build())
																						.addCountry("A07", *Vic2::Country::Builder().Build())
																						.addCountry("A08", *Vic2::Country::Builder().Build())
																						.addCountry("A09", *Vic2::Country::Builder().Build())
																						.addCountry("A10", *Vic2::Country::Builder().Build())
																						.addCountry("A11", *Vic2::Country::Builder().Build())
																						.addCountry("A12", *Vic2::Country::Builder().Build())
																						.addCountry("A13", *Vic2::Country::Builder().Build())
																						.addCountry("A14", *Vic2::Country::Builder().Build())
																						.addCountry("A15", *Vic2::Country::Builder().Build())
																						.addCountry("A16", *Vic2::Country::Builder().Build())
																						.addCountry("A17", *Vic2::Country::Builder().Build())
																						.addCountry("A18", *Vic2::Country::Builder().Build())
																						.addCountry("A19", *Vic2::Country::Builder().Build())
																						.addCountry("A20", *Vic2::Country::Builder().Build())
																						.addCountry("A21", *Vic2::Country::Builder().Build())
																						.addCountry("A22", *Vic2::Country::Builder().Build())
																						.addCountry("A23", *Vic2::Country::Builder().Build())
																						.addCountry("A24", *Vic2::Country::Builder().Build())
																						.addCountry("A25", *Vic2::Country::Builder().Build())
																						.addCountry("A26", *Vic2::Country::Builder().Build())
																						.addCountry("A27", *Vic2::Country::Builder().Build())
																						.addCountry("A28", *Vic2::Country::Builder().Build())
																						.addCountry("A29", *Vic2::Country::Builder().Build())
																						.addCountry("A30", *Vic2::Country::Builder().Build())
																						.addCountry("A31", *Vic2::Country::Builder().Build())
																						.addCountry("A32", *Vic2::Country::Builder().Build())
																						.addCountry("A33", *Vic2::Country::Builder().Build())
																						.addCountry("A34", *Vic2::Country::Builder().Build())
																						.addCountry("A35", *Vic2::Country::Builder().Build())
																						.addCountry("A36", *Vic2::Country::Builder().Build())
																						.addCountry("A37", *Vic2::Country::Builder().Build())
																						.addCountry("A38", *Vic2::Country::Builder().Build())
																						.addCountry("A39", *Vic2::Country::Builder().Build())
																						.addCountry("A40", *Vic2::Country::Builder().Build())
																						.addCountry("A41", *Vic2::Country::Builder().Build())
																						.addCountry("A42", *Vic2::Country::Builder().Build())
																						.addCountry("A43", *Vic2::Country::Builder().Build())
																						.addCountry("A44", *Vic2::Country::Builder().Build())
																						.addCountry("A45", *Vic2::Country::Builder().Build())
																						.addCountry("A46", *Vic2::Country::Builder().Build())
																						.addCountry("A47", *Vic2::Country::Builder().Build())
																						.addCountry("A48", *Vic2::Country::Builder().Build())
																						.addCountry("A49", *Vic2::Country::Builder().Build())
																						.addCountry("A50", *Vic2::Country::Builder().Build())
																						.addCountry("A51", *Vic2::Country::Builder().Build())
																						.addCountry("A52", *Vic2::Country::Builder().Build())
																						.addCountry("A53", *Vic2::Country::Builder().Build())
																						.addCountry("A54", *Vic2::Country::Builder().Build())
																						.addCountry("A55", *Vic2::Country::Builder().Build())
																						.addCountry("A56", *Vic2::Country::Builder().Build())
																						.addCountry("A57", *Vic2::Country::Builder().Build())
																						.addCountry("A58", *Vic2::Country::Builder().Build())
																						.addCountry("A59", *Vic2::Country::Builder().Build())
																						.addCountry("A60", *Vic2::Country::Builder().Build())
																						.addCountry("A61", *Vic2::Country::Builder().Build())
																						.addCountry("A62", *Vic2::Country::Builder().Build())
																						.addCountry("A63", *Vic2::Country::Builder().Build())
																						.addCountry("A64", *Vic2::Country::Builder().Build())
																						.addCountry("A65", *Vic2::Country::Builder().Build())
																						.addCountry("A66", *Vic2::Country::Builder().Build())
																						.addCountry("A67", *Vic2::Country::Builder().Build())
																						.addCountry("A68", *Vic2::Country::Builder().Build())
																						.addCountry("A69", *Vic2::Country::Builder().Build())
																						.addCountry("A70", *Vic2::Country::Builder().Build())
																						.addCountry("A71", *Vic2::Country::Builder().Build())
																						.addCountry("A72", *Vic2::Country::Builder().Build())
																						.addCountry("A73", *Vic2::Country::Builder().Build())
																						.addCountry("A74", *Vic2::Country::Builder().Build())
																						.addCountry("A75", *Vic2::Country::Builder().Build())
																						.addCountry("A76", *Vic2::Country::Builder().Build())
																						.addCountry("A77", *Vic2::Country::Builder().Build())
																						.addCountry("A78", *Vic2::Country::Builder().Build())
																						.addCountry("A79", *Vic2::Country::Builder().Build())
																						.addCountry("A80", *Vic2::Country::Builder().Build())
																						.addCountry("A81", *Vic2::Country::Builder().Build())
																						.addCountry("A82", *Vic2::Country::Builder().Build())
																						.addCountry("A83", *Vic2::Country::Builder().Build())
																						.addCountry("A84", *Vic2::Country::Builder().Build())
																						.addCountry("A85", *Vic2::Country::Builder().Build())
																						.addCountry("A86", *Vic2::Country::Builder().Build())
																						.addCountry("A87", *Vic2::Country::Builder().Build())
																						.addCountry("A88", *Vic2::Country::Builder().Build())
																						.addCountry("A89", *Vic2::Country::Builder().Build())
																						.addCountry("A90", *Vic2::Country::Builder().Build())
																						.addCountry("A91", *Vic2::Country::Builder().Build())
																						.addCountry("A92", *Vic2::Country::Builder().Build())
																						.addCountry("A93", *Vic2::Country::Builder().Build())
																						.addCountry("A94", *Vic2::Country::Builder().Build())
																						.addCountry("A95", *Vic2::Country::Builder().Build())
																						.addCountry("A96", *Vic2::Country::Builder().Build())
																						.addCountry("A97", *Vic2::Country::Builder().Build())
																						.addCountry("A98", *Vic2::Country::Builder().Build())
																						.addCountry("A99", *Vic2::Country::Builder().Build())
																						.addCountry("B00", *Vic2::Country::Builder().Build())
																						.Build(),
			  false);

	ASSERT_EQ("X00", mapper->getHoI4Tag("A00"));
	ASSERT_EQ("X99", mapper->getHoI4Tag("A99"));
	ASSERT_EQ("W00", mapper->getHoI4Tag("B00"));
}