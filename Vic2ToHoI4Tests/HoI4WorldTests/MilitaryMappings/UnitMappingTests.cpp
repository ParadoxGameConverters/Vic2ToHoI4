#include "../Vic2ToHoI4/Source/HOI4World/MilitaryMappings/UnitMapping.h"
#include "gtest/gtest.h"



TEST(HoI4World_MilitaryMappings_unitMappingTests, NulloptOnNoVic2Type)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t\thoi = {\n";
	input << "\t\t\t\ttype = land\n";
	input << "\t\t\t}\n";
	input << "\t}";

	const HoI4::UnitMapping theMapping(input);

	ASSERT_EQ(std::nullopt, theMapping.getMappings());
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
	ASSERT_EQ("irregular", mapping->first);
}


TEST(HoI4World_MilitaryMappings_unitMappingTests, NulloptOnNoHoI4Type)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t\tvic = irregular\n";
	input << "\t}";

	const HoI4::UnitMapping theMapping(input);

	ASSERT_EQ(std::nullopt, theMapping.getMappings()->second);
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
	ASSERT_EQ("land", mapping->second->getType());
}