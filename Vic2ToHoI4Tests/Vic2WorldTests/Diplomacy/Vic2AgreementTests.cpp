#include "../Vic2ToHoI4/Source/V2World/Diplomacy/Agreement.h"
#include "gtest/gtest.h"



TEST(Vic2World_Vic2AgreementTests, TypeNotSetWhenNotGivenInput)
{
	std::istringstream input("");
	Vic2::Agreement newAgreement("", input);
	ASSERT_EQ(std::string(""), newAgreement.getType());
}
TEST(Vic2World_Vic2AgreementTests, TypeSetWhenGivenInput)
{
	std::istringstream input(
		 "{\n"
		 "\t\tfirst=\"LUA\"\n"
		 "\t\tsecond=\"MKS\"\n"
		 "\t\tend_date=\"1936.1.1\""
		 "\t\tstart_date=\"1910.7.1\""
		 "\t}");
	Vic2::Agreement newAgreement("alliance", input);
	ASSERT_EQ(std::string("alliance"), newAgreement.getType());
}
TEST(Vic2World_Vic2AgreementTests, CountryOneNotSetWhenNotGivenInput)
{
	std::istringstream input("");
	Vic2::Agreement newAgreement("alliance", input);
	ASSERT_EQ(std::string(""), newAgreement.getCountry1());
}
TEST(Vic2World_Vic2AgreementTests, CountryOneSetWhenGivenInput)
{
	std::istringstream input(
		 "{\n"
		 "\t\tfirst=\"LUA\"\n"
		 "\t\tsecond=\"MKS\"\n"
		 "\t\tend_date=\"1936.1.1\""
		 "\t\tstart_date=\"1910.7.1\""
		 "\t}");
	Vic2::Agreement newAgreement("alliance", input);
	ASSERT_EQ(std::string("LUA"), newAgreement.getCountry1());
}
TEST(Vic2World_Vic2AgreementTests, CountryTwoNotSetWhenNotGivenInput)
{
	std::istringstream input("");
	Vic2::Agreement newAgreement("alliance", input);
	ASSERT_EQ(std::string(""), newAgreement.getCountry2());
}
TEST(Vic2World_Vic2AgreementTests, CountryTwoSetWhenGivenInput)
{
	std::istringstream input(
		 "{\n"
		 "\t\tfirst=\"LUA\"\n"
		 "\t\tsecond=\"MKS\"\n"
		 "\t\tend_date=\"1936.1.1\""
		 "\t\tstart_date=\"1910.7.1\""
		 "\t}");
	Vic2::Agreement newAgreement("alliance", input);
	ASSERT_EQ(std::string("MKS"), newAgreement.getCountry2());
}
TEST(Vic2World_Vic2AgreementTests, DateNotSetWhenNotGivenInput)
{
	std::istringstream input("");
	Vic2::Agreement newAgreement("alliance", input);
	ASSERT_TRUE(date() == newAgreement.getDate());
}
TEST(Vic2World_Vic2AgreementTests, DateSetWhenGivenInput)
{
	std::istringstream input(
		 "{\n"
		 "\t\tfirst=\"LUA\"\n"
		 "\t\tsecond=\"MKS\"\n"
		 "\t\tend_date=\"1936.1.1\""
		 "\t\tstart_date=\"1910.7.1\""
		 "\t}");
	Vic2::Agreement newAgreement("alliance", input);
	ASSERT_TRUE(date("1910.7.1") == newAgreement.getDate());
}