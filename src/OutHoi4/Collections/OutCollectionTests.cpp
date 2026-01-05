#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/OutHoi4/Collections/OutCollection.h"



TEST(OutHoI4World_Collections_Collection, CollectionIsOutput)
{
	std::stringstream theStream;
	theStream << "= {\n";
	theStream << "\tinput = game:scope\n";
	theStream << "\tname = COLLECTION_DEMOCRATIC_FACTION_MEMBERS\n";
	theStream << "\toperators = {\n";
	theStream << "\t\tfaction_members\n";
	theStream << "\t\tlimit = {\n";
	theStream << "\t\t\thas_government = democratic\n";
	theStream << "\t\t}\n";
	theStream << "\t}\n";
	theStream << "}";
	const HoI4::Collection theCollection("democratic_faction_members", theStream);

	std::stringstream output;
	output << theCollection;

	std::stringstream expected;
	expected << "democratic_faction_members = {\n";
	expected << "\tinput = game:scope\n";
	expected << "\tname = COLLECTION_DEMOCRATIC_FACTION_MEMBERS\n";
	expected << "\toperators = {\n";
	expected << "\t\tfaction_members\n";
	expected << "\t\tlimit = {\n";
	expected << "\t\t\thas_government = democratic\n";
	expected << "\t\t}\n";
	expected << "\t}\n";
	expected << "}\n";

	EXPECT_EQ(output.str(), expected.str());
}