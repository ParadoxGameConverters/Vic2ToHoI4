#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HOI4World/MilitaryMappings/UnitMappings.h"



TEST(HoI4World_MilitaryMappings_unitMappingsTests, NonExistingMappingNotAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t}";
	const HoI4::UnitMappings theMappings(input);
	ASSERT_FALSE(theMappings.hasMatchingType("irregular"));
}


TEST(HoI4World_MilitaryMappings_unitMappingsTests, Vic2UnitAddedToUnitMapping)
{
	std::stringstream input(
		"= {\n"\
		"\t\tlink = {\n"\
		"\t\t\tvic = irregular\n"\
		"\t\t\thoi = { type = foo }\n"\
		"\t\t}\n"\
		"\t}"
	);
	const HoI4::UnitMappings theMappings(input);
	ASSERT_TRUE(theMappings.hasMatchingType("irregular"));
}


TEST(HoI4World_MilitaryMappings_unitMappingsTests, UnitMappingHandlesFilledHoI4UnitTypeCorrectly)
{
	std::stringstream input(
		"= {\n"\
		"\tmap = {\n"\
		"\t\tlink = {\n"\
		"\t\t\tvic = infantry\n"\
		"\t\t\thoi = {\n"\
		"\t\t\t\ttype = land\n"\
		"\t\t\t}\n"\
		"\t\t}\n"\
		"\t}"\
		"}"
	);
	const HoI4::UnitMappings theMappings(input);

	auto mapping = theMappings.getMatchingUnitInfo("infantry");
	ASSERT_TRUE(mapping);
	ASSERT_EQ(std::string("land"), mapping->getType());
}