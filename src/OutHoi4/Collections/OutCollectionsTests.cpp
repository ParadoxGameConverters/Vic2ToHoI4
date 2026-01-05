#include "external/common_items/OSCompatibilityLayer.h"
#include "external/common_items/external/googletest/googletest/include/gtest/gtest.h"
#include "src/OutHoi4/Collections/OutCollections.h"
#include <fstream>



using HoI4::Collection;



TEST(OutHoI4_Collections_OutCollections, CollectionsAreOutput)
{
	std::filesystem::create_directories("OutHoI4Tests/Collections/common/collections");

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
	Collection theCollection("democratic_faction_members", theStream);
	HoI4::outputCollections("OutHoI4Tests/Collections", {theCollection});

	std::ifstream file("OutHoI4Tests/Collections/common/collections/ideological_collections.txt");
	const std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

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
	expected << "\n";
	EXPECT_EQ(content, expected.str());
}