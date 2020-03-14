#include "../Vic2ToHoI4/Source/HOI4World/MilitaryMappings/UnitMappings.h"
#include "gtest/gtest.h"



TEST(HoI4World_MilitaryMappings_unitMappingsTests, NonExistingMappingHasNoMatchingType)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t}";
	const HoI4::UnitMappings theMappings(input);
	ASSERT_FALSE(theMappings.hasMatchingType("irregular"));
}


TEST(HoI4World_MilitaryMappings_unitMappingsTests, MappingCanBeAdded)
{
	std::stringstream input(
		 "= {\n"
		 "\t\tlink = {\n"
		 "\t\t\tvic = irregular\n"
		 "\t\t\thoi = { type = foo }\n"
		 "\t\t}\n"
		 "\t}");
	const HoI4::UnitMappings theMappings(input);
	ASSERT_TRUE(theMappings.hasMatchingType("irregular"));
}


TEST(HoI4World_MilitaryMappings_UnitMappingsTests, UnmatchedMappingReturnsEmpty)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";
	const HoI4::UnitMappings theMappings(input);
	ASSERT_TRUE(theMappings.getMatchingUnitInfo("infantry").empty());
}


TEST(HoI4World_MilitaryMappings_unitMappingsTests, MatchedMappingReturnsType)
{
	std::stringstream input(
		 "= {\n"
		 "\t\tlink = {\n"
		 "\t\t\tvic = infantry\n"
		 "\t\t\thoi = {\n"
		 "\t\t\t\ttype = land\n"
		 "\t\t\t}\n"
		 "\t\t}\n"
		 "\t}");
	const HoI4::UnitMappings theMappings(input);

	ASSERT_EQ("land", theMappings.getMatchingUnitInfo("infantry")[0].getType());
}