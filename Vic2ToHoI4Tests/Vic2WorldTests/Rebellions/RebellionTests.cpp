#include "V2World/Rebellions/Rebellion.h"
#include "V2World/Rebellions/RebellionFactory.h"
#include "gtest/gtest.h"



TEST(Vic2World_Rebellion_Tests, CountryDefaultsToEmpty)
{
	std::stringstream input;
	const auto newRebellion = Vic2::Rebellion::Factory().importRebellion(input);

	ASSERT_TRUE(newRebellion->getCountry().empty());
}


TEST(Vic2World_Rebellion_Tests, CountryCanBeSet)
{
	std::stringstream input;
	input << "country=\"BAV\"";
	const auto newRebellion = Vic2::Rebellion::Factory().importRebellion(input);

	ASSERT_EQ("BAV", newRebellion->getCountry());
}


TEST(Vic2World_Rebellion_Tests, TypeDefaultsToEmpty)
{
	std::stringstream input;
	const auto newRebellion = Vic2::Rebellion::Factory().importRebellion(input);

	ASSERT_TRUE(newRebellion->getType().empty());
}


TEST(Vic2World_Rebellion_Tests, TypeCanBeSet)
{
	std::stringstream input;
	input << "type=\"pan_nationalist_rebels\"";
	const auto newRebellion = Vic2::Rebellion::Factory().importRebellion(input);

	ASSERT_EQ("pan_nationalist_rebels", newRebellion->getType());
}


TEST(Vic2World_Rebellion_Tests, ProvincesDefaultToEmpty)
{
	std::stringstream input;
	const auto newRebellion = Vic2::Rebellion::Factory().importRebellion(input);

	ASSERT_TRUE(newRebellion->getProvinces().empty());
}


TEST(Vic2World_Rebellion_Tests, ProvincesCanBeSet)
{
	std::stringstream input;
	input << "provinces = { 2640 2641 }";
	const auto newRebellion = Vic2::Rebellion::Factory().importRebellion(input);

	ASSERT_EQ(std::vector<int>({2640, 2641}), newRebellion->getProvinces());
}