#include "src/HOI4World/MilitaryMappings/UnitMapping.h"
#include "external/googletest/googletest/include/gtest/gtest.h"



TEST(HoI4World_MilitaryMappings_UnitMappingTests, NulloptOnNoVic2Type)
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


TEST(HoI4World_MilitaryMappings_UnitMappingTests, Vic2TypeCanBeSet)
{
	std::stringstream input;
	input << " = {\n";
	input << "\t\t\tvic = irregular\n";
	input << "\t\t\thoi = {\n";
	input << "\t\t\t\ttype = land\n";
	input << "\t\t\t}\n";
	input << "\t\t}";

	const HoI4::UnitMapping theMapping(input);

	auto mapping = theMapping.getMappings();
	ASSERT_TRUE(mapping);
	ASSERT_EQ("irregular", mapping->first);
}


TEST(HoI4World_MilitaryMappings_UnitMappingTests, DefaultHoI4TypeIsEmpty)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t\tvic = irregular\n";
	input << "\t}";

	const HoI4::UnitMapping theMapping(input);

	ASSERT_TRUE(theMapping.getMappings()->second.empty());
}


TEST(HoI4World_MilitaryMappings_UnitMappingTests, UnitMappingHandlesFilledHoI4UnitTypeCorrectly)
{
	std::stringstream input;
	input << " = {\n";
	input << "\t\t\tvic = infantry\n";
	input << "\t\t\thoi = {\n";
	input << "\t\t\t\ttype = land\n";
	input << "\t\t\t}\n";
	input << "\t\t}";

	const HoI4::UnitMapping theMapping(input);

	auto mapping = theMapping.getMappings();
	ASSERT_TRUE(mapping);
	ASSERT_EQ("land", mapping->second[0].getType());
}


TEST(HoI4World_MilitaryMappings_UnitMappingTests, UnitMappingHandlesMultipleHoI4Type)
{
	std::stringstream input;
	input << " = {\n";
	input << "\t\t\tvic = infantry\n";
	input << "\t\t\thoi = {\n";
	input << "\t\t\t\ttype = land\n";
	input << "\t\t\t}\n";
	input << "\t\t\thoi = {\n";
	input << "\t\t\t\ttype = sea\n";
	input << "\t\t\t}\n";
	input << "\t\t}";

	const HoI4::UnitMapping theMapping(input);
	ASSERT_EQ("sea", theMapping.getMappings()->second[1].getType());
}