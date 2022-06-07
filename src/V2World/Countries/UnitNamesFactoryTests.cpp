#include "src/V2World/Countries/UnitNamesFactory.h"
#include "external/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "external/googletest/googletest/include/gtest/gtest.h"
#include <sstream>



TEST(Vic2World_Countries_UnitNamesFactoryTests, UnitNamesDefaultToEmpty)
{
	std::stringstream input;
	const auto unitNames = Vic2::UnitNamesFactory().importUnitNames(input);

	ASSERT_TRUE(unitNames.empty());
}


TEST(Vic2World_Countries_UnitNamesFactoryTests, UnitNamesCanBeSet)
{
	std::stringstream input;
	input << "dreadnought = {\n";
	input << "\t\tAzerbaijan \"Nader Shah\"\n";
	input << "\t}\n";
	input << "\tironclad = {\n";
	input << "\t\tErivan Nakchivan\n";
	input << "\t}\n";
	const auto unitNames = Vic2::UnitNamesFactory().importUnitNames(input);

	ASSERT_THAT(unitNames,
		 testing::UnorderedElementsAre(
			  testing::Pair(std::string("dreadnought"), std::vector<std::string>{"Azerbaijan", "Nader Shah"}),
			  testing::Pair(std::string("ironclad"), std::vector<std::string>{"Erivan", "Nakchivan"})));
}


TEST(Vic2World_Countries_UnitNamesFactoryTests, MoreNamesCanBeAdded)
{
	std::stringstream input;
	input << "\tironclad = {\n";
	input << "\t\tErivan\n";
	input << "\t}\n";
	input << "\tironclad = {\n";
	input << "\t\tNakchivan\n";
	input << "\t}\n";
	const auto unitNames = Vic2::UnitNamesFactory().importUnitNames(input);

	ASSERT_THAT(unitNames,
		 testing::UnorderedElementsAre(
			  testing::Pair(std::string("ironclad"), std::vector<std::string>{"Erivan", "Nakchivan"})));
}