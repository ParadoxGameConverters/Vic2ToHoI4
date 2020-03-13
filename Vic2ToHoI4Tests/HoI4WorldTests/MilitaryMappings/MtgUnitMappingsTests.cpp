#include "../Vic2ToHoI4/Source/HOI4World/MilitaryMappings/MtgUnitMappings.h"
#include "gtest/gtest.h"



TEST(HoI4World_MilitaryMappings_mtgUnitMappingsTests, NonExistingMappingHasNoMatchingType)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t}";
	const HoI4::MtgUnitMappings theMappings(input);
	ASSERT_FALSE(theMappings.hasMatchingType("irregular"));
}


TEST(HoI4World_MilitaryMappings_mtgUnitMappingsTests, MappingCanBeAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tlink = {\n";
	input << "\t\t\tvic = irregular\n";
	input << "\t\t}\n";
	input << "\t}";
	const HoI4::MtgUnitMappings theMappings(input);
	ASSERT_TRUE(theMappings.hasMatchingType("irregular"));
}


TEST(HoI4World_MilitaryMappings_mtgUnitMappingsTests, UnmatchedMappingReturnsEmpty)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	const HoI4::MtgUnitMappings theMappings(input);
	ASSERT_TRUE(theMappings.getMatchingUnitInfo("infantry").empty());
}


TEST(HoI4World_MilitaryMappings_mtgUnitMappingsTests, MatchedMappingReturnsType)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tmap = {\n";
	input << "\t\tlink = {\n";
	input << "\t\t\tvic = infantry\n";
	input << "\t\t\thoi = {\n";
	input << "\t\t\t\ttype = land\n";
	input << "\t\t\t}\n";
	input << "\t\t}\n";
	input << "\t}";
	input << "}";
	const HoI4::MtgUnitMappings theMappings(input);
	ASSERT_EQ("land", theMappings.getMatchingUnitInfo("infantry")[0].getType());
}