#include "HOI4World/MilitaryMappings/SubstitutesImporter.h"
#include "gtest/gtest.h"



TEST(HoI4World_MilitaryMappings_SubstitutesImporterTests, SubstitutesDefaultToEmpty)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t}";
	const HoI4::substitutesImporter importer(input);
	ASSERT_TRUE(importer.getSubstitutes().empty());
}


TEST(HoI4World_MilitaryMappings_SubstitutesImporterTests, SubstitutesCanBeAdded)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tsubstitutes_one = match_one\n";
	input << "\t\tsubstitutes_two = match_two\n";
	input << "\t}";
	const HoI4::substitutesImporter importer(input);

	const std::map<std::string, std::string> expectedSubstitutes{{"substitutes_one", "match_one"},
		 {"substitutes_two", "match_two"}};
	ASSERT_EQ(expectedSubstitutes, importer.getSubstitutes());
}