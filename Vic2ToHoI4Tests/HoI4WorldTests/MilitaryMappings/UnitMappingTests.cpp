#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HOI4World/MilitaryMappings/UnitMapping.h"



TEST(HoI4World_MilitaryMappings_unitMappingTests, nulloptOnNoVic2Type)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t}";

	const HoI4::UnitMapping theMapping(input);

	ASSERT_EQ(theMapping.getMappings(), std::nullopt);
}


TEST(HoI4World_MilitaryMappings_unitMappingTests, Vic2TypeCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tlink = {\n";
	input << "\t\t\tvic = irregular\n";
	input << "\t\t\thoi = {\n";
	input << "\t\t\t\ttype = land\n";
	input << "\t\t\t}\n";
	input << "\t\t}\n";
	input << "\t}";

	const HoI4::UnitMapping theMapping(input);

	auto mapping = theMapping.getMappings();
	ASSERT_TRUE(mapping);
	ASSERT_EQ(mapping->first, "irregular");
}


TEST(HoI4World_MilitaryMappings_unitMappingTests, nulloptOnNoHoI4Type)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t}";

	const HoI4::UnitMapping theMapping(input);

	ASSERT_EQ(theMapping.getMappings(), std::nullopt);
}


TEST(HoI4World_MilitaryMappings_unitMappingTests, UnitMappingHandlesFilledHoI4UnitTypeCorrectly)
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

	const HoI4::UnitMapping theMapping(input);

	auto mapping = theMapping.getMappings();
	ASSERT_TRUE(mapping);
	ASSERT_EQ(std::string("land"), mapping->second.getType());
}