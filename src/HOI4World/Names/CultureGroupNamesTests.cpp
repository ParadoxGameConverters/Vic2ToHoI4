#include "src/HOI4World/Names/CultureGroupNames.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Names_CultureGroupNamesTests, MaleNamesDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::CultureGroupNames cultureGroupNames(input);

	ASSERT_TRUE(cultureGroupNames.takeMaleNames().empty());
}


TEST(HoI4World_Names_CultureGroupNamesTests, MaleNamesCanBeAdded)
{
	std::stringstream input;
	input << "american = {\n";
	input << "\tfirst_names = { Bob }\n";
	input << "}";
	input << "german = {\n";
	input << "\tfirst_names = { Hans }\n";
	input << "}";
	HoI4::CultureGroupNames cultureGroupNames(input);

	const std::map<std::string, std::vector<std::string>> expectedNames{{"american", {"Bob"}}, {"german", {"Hans"}}};
	ASSERT_EQ(expectedNames, cultureGroupNames.takeMaleNames());
}


TEST(HoI4World_Names_CultureGroupNamesTests, SurnamesDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::CultureGroupNames cultureGroupNames(input);

	ASSERT_TRUE(cultureGroupNames.takeSurnames().empty());
}


TEST(HoI4World_Names_CultureGroupNamesTests, SurnamesCanBeAdded)
{
	std::stringstream input;
	input << "american = {\n";
	input << "\tlast_names = { Smith }\n";
	input << "}";
	input << "german = {\n";
	input << "\tlast_names = { Meier }\n";
	input << "}";
	HoI4::CultureGroupNames cultureGroupNames(input);

	const std::map<std::string, std::vector<std::string>> expectedNames{{"american", {"Smith"}}, {"german", {"Meier"}}};
	ASSERT_EQ(expectedNames, cultureGroupNames.takeSurnames());
}