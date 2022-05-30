#include "V2World/Diplomacy/Agreement.h"
#include "V2World/Diplomacy/AgreementFactory.h"
#include "gtest/gtest.h"



TEST(Vic2World_Diplomacy_AgreementTests, TypeNotSetWhenNotGivenInput)
{
	std::stringstream input;
	const auto newAgreement = Vic2::Agreement::Factory().getAgreement("", input);

	ASSERT_TRUE(newAgreement->getType().empty());
}


TEST(Vic2World_Diplomacy_AgreementTests, TypeSetWhenGivenInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tfirst=\"LUA\"\n";
	input << "\t\tsecond=\"MKS\"\n";
	input << "\t\tend_date=\"1936.1.1\"";
	input << "\t\tstart_date=\"1910.7.1\"";
	input << "\t}";
	const auto newAgreement = Vic2::Agreement::Factory().getAgreement("alliance", input);

	ASSERT_EQ("alliance", newAgreement->getType());
}


TEST(Vic2World_Diplomacy_AgreementTests, CountryOneNotSetWhenNotGivenInput)
{
	std::stringstream input;
	const auto newAgreement = Vic2::Agreement::Factory().getAgreement("alliance", input);

	ASSERT_TRUE(newAgreement->getCountry1().empty());
}


TEST(Vic2World_Diplomacy_AgreementTests, CountryOneSetWhenGivenInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tfirst=\"LUA\"\n";
	input << "\t\tsecond=\"MKS\"\n";
	input << "\t\tend_date=\"1936.1.1\"";
	input << "\t\tstart_date=\"1910.7.1\"";
	input << "\t}";
	const auto newAgreement = Vic2::Agreement::Factory().getAgreement("alliance", input);

	ASSERT_EQ("LUA", newAgreement->getCountry1());
}


TEST(Vic2World_Diplomacy_AgreementTests, CountryTwoNotSetWhenNotGivenInput)
{
	std::stringstream input;
	const auto newAgreement = Vic2::Agreement::Factory().getAgreement("alliance", input);

	ASSERT_TRUE(newAgreement->getCountry2().empty());
}


TEST(Vic2World_Diplomacy_AgreementTests, CountryTwoSetWhenGivenInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\t\tfirst=\"LUA\"\n";
	input << "\t\tsecond=\"MKS\"\n";
	input << "\t\tend_date=\"1936.1.1\"";
	input << "\t\tstart_date=\"1910.7.1\"";
	input << "\t}";
	const auto newAgreement = Vic2::Agreement::Factory().getAgreement("alliance", input);

	ASSERT_EQ(std::string("MKS"), newAgreement->getCountry2());
}


TEST(Vic2World_Diplomacy_AgreementTests, DateNotSetWhenNotGivenInput)
{
	std::stringstream input;
	const auto newAgreement = Vic2::Agreement::Factory().getAgreement("alliance", input);

	ASSERT_EQ(date(), newAgreement->getDate());
}


TEST(Vic2World_Diplomacy_AgreementTests, DateSetWhenGivenInput)
{
	std::stringstream input;
	input << "{\n";
	input << "\t\tfirst=\"LUA\"\n";
	input << "\t\tsecond=\"MKS\"\n";
	input << "\t\tend_date=\"1936.1.1\"";
	input << "\t\tstart_date=\"1910.7.1\"";
	input << "\t}";
	const auto newAgreement = Vic2::Agreement::Factory().getAgreement("alliance", input);

	ASSERT_EQ(date("1910.7.1"), newAgreement->getDate());
}