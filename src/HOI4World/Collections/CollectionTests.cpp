#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/HOI4World/Collections/Collection.h"



TEST(HoI4World_Collections_Collection, DefaultInputIsSet)
{
	std::stringstream theStream;
	HoI4::Collection theCollection("test_collection", theStream);

	EXPECT_EQ("game:scope", theCollection.getInput());
}


TEST(HoI4World_Collections_Collection, InputCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "input = game:all_states\n";
	theStream << "}\n";
	HoI4::Collection theCollection("test_collection", theStream);

	EXPECT_EQ("game:all_states", theCollection.getInput());
}


TEST(HoI4World_Collections_Collection, DefaultNameIsSet)
{
	std::stringstream theStream;
	HoI4::Collection theCollection("test_collection", theStream);

	EXPECT_EQ("COLLECTION_DEFAULT", theCollection.getName());
}


TEST(HoI4World_Collections_Collection, NameCanBeSet)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "name = COLLECTION_DEMOCRATIC_FACTION_MEMBERS\n";
	theStream << "}\n";
	HoI4::Collection theCollection("test_collection", theStream);

	EXPECT_EQ("COLLECTION_DEMOCRATIC_FACTION_MEMBERS", theCollection.getName());
}


TEST(HoI4World_Collections_Collection, DefaultOperatorsIsSet)
{
	std::stringstream theStream;
	HoI4::Collection theCollection("test_collection", theStream);

	EXPECT_EQ("= {}", theCollection.getOperators());
}


TEST(HoI4World_Collections_Collection, OperatorsCanBeSet)
{
	std::stringstream theStream;
	theStream << "operators = {\n";
	theStream << "\tfaction_members\n";
	theStream << "\tlimit = {\n";
	theStream << "\t\thas_government = democratic\n";
	theStream << "\t}\n";
	theStream << "}";
	HoI4::Collection theCollection("test_collection", theStream);

	std::string expectedOutput;
	expectedOutput += "= {\n";
	expectedOutput += "\tfaction_members\n";
	expectedOutput += "\tlimit = {\n";
	expectedOutput += "\t\thas_government = democratic\n";
	expectedOutput += "\t}\n";
	expectedOutput += "}";

	EXPECT_EQ(expectedOutput, theCollection.getOperators());
}