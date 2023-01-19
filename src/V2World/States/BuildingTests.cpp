#include "external/googletest/googletest/include/gtest/gtest.h"
#include "src/V2World/States/BuildingReader.h"
#include <sstream>



TEST(Vic2World_States_BuildingReaderTests, LevelDefaultsToZero)
{
	Vic2::BuildingReader reader;

	std::stringstream input;
	ASSERT_EQ(0, reader.getLevel(input));
}


TEST(Vic2World_States_BuildingReaderTests, LevelCanBeRead)
{
	Vic2::BuildingReader reader;

	std::stringstream input;
	input << "= {\n";
	input << "\tlevel = 7\n";
	input << "}";
	ASSERT_EQ(7, reader.getLevel(input));
}