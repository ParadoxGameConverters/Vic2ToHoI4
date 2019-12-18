#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HOI4World/MilitaryMappings/MtgUnitMapping.h"



TEST(HoI4World_MilitaryMappings_mtgUnitMappingTests, defaultVic2TypeIsBlank)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t}";

	const HoI4::MtgUnitMapping theMapping(input);

	ASSERT_EQ(theMapping.getMapping().first, "");
}


TEST(HoI4World_MilitaryMappings_mtgUnitMappingTests, Vic2TypeCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tlink = {\n";
	input << "\t\t\tvic = irregular\n";
	input << "\t\t}\n";
	input << "\t}";

	const HoI4::MtgUnitMapping theMapping(input);

	ASSERT_EQ(theMapping.getMapping().first, "irregular");
}


TEST(HoI4World_MilitaryMappings_mtgUnitMappingTests, noHoI4MeansEmptyVector)
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
	input << "\tmap = {\n";
	input << "\t\tlink = {\n";
	input << "\t\t\tvic = infantry\n";
	input << "\t\t\thoi = {\n";
	input << "\t\t\t\ttype = land\n";
	input << "\t\t\t}\n";
	input << "\t\t}\n";
	input << "\t}";
	input << "}";

	const HoI4::MtgUnitMapping theMapping(input);
	ASSERT_EQ(std::string("land"), theMapping.getMapping().second[0].getType());
}


TEST(HoI4World_MilitaryMappings_mtgUnitMappingTests, MtgUnitMappingHandlesMultipleHoI4Type)
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

	const HoI4::MtgUnitMapping theMapping(input);
	ASSERT_EQ(std::string("sea"), theMapping.getMapping().second[1].getType());
}