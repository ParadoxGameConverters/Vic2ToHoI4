#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/MilitaryMappings/MtgUnitMapping.h"



TEST(HoI4World_MilitaryMappings_mtgUnitMappingTests, defaultVic2TypeIsBlank)
{
	std::stringstream input;
	input << "{\n";
	input << "\t}";

	const HoI4::MtgUnitMapping theMapping(input);

	ASSERT_EQ("", theMapping.getMapping().first);
}


TEST(HoI4World_MilitaryMappings_mtgUnitMappingTests, Vic2TypeCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t\tvic = irregular\n";
	input << "\t\t}";

	const HoI4::MtgUnitMapping theMapping(input);

	ASSERT_EQ("irregular", theMapping.getMapping().first);
}


TEST(HoI4World_MilitaryMappings_mtgUnitMappingTests, DefaultHoI4TypeIsEmpty)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t}";

	const HoI4::MtgUnitMapping theMapping(input);

	ASSERT_TRUE(theMapping.getMapping().second.empty());
}


TEST(HoI4World_MilitaryMappings_mtgUnitMappingTests, MtgUnitMappingHandlesFilledHoI4UnitTypeCorrectly)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t\tvic = infantry\n";
	input << "\t\t\thoi = {\n";
	input << "\t\t\t\ttype = land\n";
	input << "\t\t\t}\n";
	input << "\t\t}";

	const HoI4::MtgUnitMapping theMapping(input);
	ASSERT_EQ("land", theMapping.getMapping().second[0].getType());
}


TEST(HoI4World_MilitaryMappings_mtgUnitMappingTests, MtgUnitMappingHandlesMultipleHoI4Type)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\t\tvic = infantry\n";
	input << "\t\t\thoi = {\n";
	input << "\t\t\t\ttype = land\n";
	input << "\t\t\t}\n";
	input << "\t\t\thoi = {\n";
	input << "\t\t\t\ttype = sea\n";
	input << "\t\t\t}\n";
	input << "\t\t}";

	const HoI4::MtgUnitMapping theMapping(input);
	ASSERT_EQ("sea", theMapping.getMapping().second[1].getType());
}