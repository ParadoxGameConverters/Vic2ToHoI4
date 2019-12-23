#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HOI4World/MilitaryMappings/MtgUnitMappings.h"



TEST(HoI4World_MilitaryMappings_mtgUnitMappingsTests, NonExistingMappingNotAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t}";
	const HoI4::MtgUnitMappings theMappings(input);
	ASSERT_FALSE(theMappings.hasMatchingType("irregular"));
}


TEST(HoI4World_MilitaryMappings_mtgUnitMappingsTests, Vic2UnitAddedToMtgUnitMapping)
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


TEST(HoI4World_MilitaryMappings_mtgUnitMappingsTests, MtgUnitMappingHandlesFilledHoI4UnitTypeCorrectly)
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
	ASSERT_EQ(std::string("land"), theMappings.getMatchingUnitInfo("infantry")[0].getType());
}


TEST(HoI4World_MilitaryMappings_mtgUnitMappingsTests, UnitMappingHandlesMultipleEntries)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tmap = {\n";
	input << "\t\tlink = {\n";
	input << "\t\t\tvic = infantry\n";
	input << "\t\t\thoi = {\n";
	input << "\t\t\t\ttype = land\n";
	input << "\t\t\t}\n";
	input << "\t\t\thoi = {\n";
	input << "\t\t\t\ttype = sea\n";
	input << "\t\t\t}\n";
	input << "\t\t}\n";
	input << "\t}";
	input << "}";
	const HoI4::MtgUnitMappings theMappings(input);
	ASSERT_EQ(std::string("sea"), theMappings.getMatchingUnitInfo("infantry")[1].getType());
}