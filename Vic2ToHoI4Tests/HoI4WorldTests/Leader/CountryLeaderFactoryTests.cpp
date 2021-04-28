#include "HOI4World/Leaders/CountryLeaderFactory.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Leaders_CountryLeaderFactoryTests, NameDefaultsToNomenNescio)
{
	std::stringstream input;
	const auto leader = HoI4::CountryLeader::Factory().importCountryLeader(input);

	ASSERT_EQ("Nomen Nescio", leader->getName());
}


TEST(HoI4World_Leaders_CountryLeaderFactoryTests, NameCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tname = \"Test Name\"";
	input << "}";
	const auto leader = HoI4::CountryLeader::Factory().importCountryLeader(input);

	ASSERT_EQ("Test Name", leader->getName());
}


TEST(HoI4World_Leaders_CountryLeaderFactoryTests, DescriptionDefaultsToNomenNescio)
{
	std::stringstream input;
	const auto leader = HoI4::CountryLeader::Factory().importCountryLeader(input);

	ASSERT_EQ("POLITICS_NOMEN_NESCIO_DESC", leader->getDescription());
}


TEST(HoI4World_Leaders_CountryLeaderFactoryTests, DescriptionanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tdesc = \"POLITICS_TEST_DESCRIPTION_DESC\"";
	input << "}";
	const auto leader = HoI4::CountryLeader::Factory().importCountryLeader(input);

	ASSERT_EQ("POLITICS_TEST_DESCRIPTION_DESC", leader->getDescription());
}


TEST(HoI4World_Leaders_CountryLeaderFactoryTests, PictureDefaultsToFallenGovernment)
{
	std::stringstream input;
	const auto leader = HoI4::CountryLeader::Factory().importCountryLeader(input);

	ASSERT_EQ("gfx/leaders/ENG/portrait_eng_fallen_government.dds", leader->getPicture());
}


TEST(HoI4World_Leaders_CountryLeaderFactoryTests, PictureCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tpicture = \"gfx/leaders/TAG/portrait_test_picture.dds\"";
	input << "}";
	const auto leader = HoI4::CountryLeader::Factory().importCountryLeader(input);

	ASSERT_EQ("gfx/leaders/TAG/portrait_test_picture.dds", leader->getPicture());
}


TEST(HoI4World_Leaders_CountryLeaderFactoryTests, IdeologyDefaultsToAnarchism)
{
	std::stringstream input;
	const auto leader = HoI4::CountryLeader::Factory().importCountryLeader(input);

	ASSERT_EQ("anarchism", leader->getIdeology());
}


TEST(HoI4World_Leaders_CountryLeaderFactoryTests, IdeologyCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tideology = neutral_test";
	input << "}";
	const auto leader = HoI4::CountryLeader::Factory().importCountryLeader(input);

	ASSERT_EQ("neutral_test", leader->getIdeology());
}


TEST(HoI4World_Leaders_CountryLeaderFactoryTests, TraitsDefaultToEmpty)
{
	std::stringstream input;
	const auto leader = HoI4::CountryLeader::Factory().importCountryLeader(input);

	ASSERT_TRUE(leader->getTraits().empty());
}


TEST(HoI4World_Leaders_CountryLeaderFactoryTests, TraitsCanBeSet)
{
	std::stringstream input;
	input << "= {\n";
	input << "\ttraits = {\n";
	input << "\t\ttest_trait\n";
	input << "\t\ttest_trait_two\n";
	input << "\t}\n";
	input << "}";
	const auto leader = HoI4::CountryLeader::Factory().importCountryLeader(input);

	ASSERT_EQ(2, leader->getTraits().size());
	ASSERT_EQ("test_trait", leader->getTraits()[0]);
	ASSERT_EQ("test_trait_two", leader->getTraits()[1]);
}