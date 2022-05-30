#include "HOI4World/Names/CultureNames.h"
#include "gtest/gtest.h"
#include <sstream>



TEST(HoI4World_Names_CultureNamesTests, MaleNamesDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::CultureNames cultureNames(input);

	ASSERT_TRUE(cultureNames.takeMaleNames().empty());
}


TEST(HoI4World_Names_CultureNamesTests, MaleNamesCanBeAdded)
{
	std::stringstream input;
	input << "first_names = { Bob \"Billy Bob\" }";
	HoI4::CultureNames cultureNames(input);

	const auto maleNames = cultureNames.takeMaleNames();
	ASSERT_EQ(2, maleNames.size());
	ASSERT_EQ("Bob", maleNames[0]);
	ASSERT_EQ("Billy Bob", maleNames[1]);
}


TEST(HoI4World_Names_CultureNamesTests, SurnamesDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::CultureNames cultureNames(input);

	ASSERT_TRUE(cultureNames.takeSurnames().empty());
}


TEST(HoI4World_Names_CultureNamesTests, SurnamesCanBeAdded)
{
	std::stringstream input;
	input << "last_names = { Smith \"Le Smith\" }";
	HoI4::CultureNames cultureNames(input);

	const auto surnames = cultureNames.takeSurnames();
	ASSERT_EQ(2, surnames.size());
	ASSERT_EQ("Smith", surnames[0]);
	ASSERT_EQ("Le Smith", surnames[1]);
}


TEST(HoI4World_Names_CultureNamesTests, FemaleNamesDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::CultureNames cultureNames(input);

	ASSERT_TRUE(cultureNames.takeFemaleNames().empty());
}


TEST(HoI4World_Names_CultureNamesTests, FemaleNamesCanBeAdded)
{
	std::stringstream input;
	input << "female_names = { Sue \"Peggy Sue\" }";
	HoI4::CultureNames cultureNames(input);

	const auto femaleNames = cultureNames.takeFemaleNames();
	ASSERT_EQ(2, femaleNames.size());
	ASSERT_EQ("Sue", femaleNames[0]);
	ASSERT_EQ("Peggy Sue", femaleNames[1]);
}


TEST(HoI4World_Names_CultureNamesTests, FemaleSurnamesDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::CultureNames cultureNames(input);

	ASSERT_TRUE(cultureNames.takeFemaleSurnames().empty());
}


TEST(HoI4World_Names_CultureNamesTests, FemaleSurnamesCanBeAdded)
{
	std::stringstream input;
	input << "female_surnames = { Smith \"Le Smith\" }";
	HoI4::CultureNames cultureNames(input);

	const auto surnames = cultureNames.takeFemaleSurnames();
	ASSERT_EQ(2, surnames.size());
	ASSERT_EQ("Smith", surnames[0]);
	ASSERT_EQ("Le Smith", surnames[1]);
}


TEST(HoI4World_Names_CultureNamesTests, CallsignsDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::CultureNames cultureNames(input);

	ASSERT_TRUE(cultureNames.takeCallsigns().empty());
}


TEST(HoI4World_Names_CultureNamesTests, CallsignsCanBeAdded)
{
	std::stringstream input;
	input << "callsigns = { Maverick \"Ice Man\" }";
	HoI4::CultureNames cultureNames(input);

	const auto callsigns = cultureNames.takeCallsigns();
	ASSERT_EQ(2, callsigns.size());
	ASSERT_EQ("Maverick", callsigns[0]);
	ASSERT_EQ("Ice Man", callsigns[1]);
}


TEST(HoI4World_Names_CultureNamesTests, IndustryCompaniesDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::CultureNames cultureNames(input);

	ASSERT_TRUE(cultureNames.takeIndustryCompanies().empty());
}


TEST(HoI4World_Names_CultureNamesTests, IndustryCompaniesCanBeAdded)
{
	std::stringstream input;
	input << "industry_companies = { Atkins \"Mott McDonald\" }";
	HoI4::CultureNames cultureNames(input);

	const auto industryCompanies = cultureNames.takeIndustryCompanies();
	ASSERT_EQ(2, industryCompanies.size());
	ASSERT_EQ("Atkins", industryCompanies[0]);
	ASSERT_EQ("Mott McDonald", industryCompanies[1]);
}


TEST(HoI4World_Names_CultureNamesTests, ElectronicCompaniesDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::CultureNames cultureNames(input);

	ASSERT_TRUE(cultureNames.takeElectronicCompanies().empty());
}


TEST(HoI4World_Names_CultureNamesTests, ElectronicCompaniesCanBeAdded)
{
	std::stringstream input;
	input << "electronic_companies = { Raytheon \"General Electric\" }";
	HoI4::CultureNames cultureNames(input);

	const auto electronicCompanies = cultureNames.takeElectronicCompanies();
	ASSERT_EQ(2, electronicCompanies.size());
	ASSERT_EQ("Raytheon", electronicCompanies[0]);
	ASSERT_EQ("General Electric", electronicCompanies[1]);
}


TEST(HoI4World_Names_CultureNamesTests, CarCompaniesDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::CultureNames cultureNames(input);

	ASSERT_TRUE(cultureNames.takeCarCompanies().empty());
}


TEST(HoI4World_Names_CultureNamesTests, CompaniesCanBeAdded)
{
	std::stringstream input;
	input << "car_companies = { Ford \"General Motors\" }";
	HoI4::CultureNames cultureNames(input);

	const auto carCompanies = cultureNames.takeCarCompanies();
	ASSERT_EQ(2, carCompanies.size());
	ASSERT_EQ("Ford", carCompanies[0]);
	ASSERT_EQ("General Motors", carCompanies[1]);
}


TEST(HoI4World_Names_CultureNamesTests, NavalCompaniesDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::CultureNames cultureNames(input);

	ASSERT_TRUE(cultureNames.takeNavalCompanies().empty());
}


TEST(HoI4World_Names_CultureNamesTests, NavalCompaniesCanBeAdded)
{
	std::stringstream input;
	input << "naval_companies = { BAE \"Consolidated Steel\" }";
	HoI4::CultureNames cultureNames(input);

	const auto navalCompanies = cultureNames.takeNavalCompanies();
	ASSERT_EQ(2, navalCompanies.size());
	ASSERT_EQ("BAE", navalCompanies[0]);
	ASSERT_EQ("Consolidated Steel", navalCompanies[1]);
}


TEST(HoI4World_Names_CultureNamesTests, WeaponCompaniesDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::CultureNames cultureNames(input);

	ASSERT_TRUE(cultureNames.takeWeaponCompanies().empty());
}


TEST(HoI4World_Names_CultureNamesTests, WeaponCompaniesCanBeAdded)
{
	std::stringstream input;
	input << "weapon_companies = { Remington \"Smith & Wesson\" }";
	HoI4::CultureNames cultureNames(input);

	const auto weaponCompanies = cultureNames.takeWeaponCompanies();
	ASSERT_EQ(2, weaponCompanies.size());
	ASSERT_EQ("Remington", weaponCompanies[0]);
	ASSERT_EQ("Smith & Wesson", weaponCompanies[1]);
}


TEST(HoI4World_Names_CultureNamesTests, AircraftCompaniesDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::CultureNames cultureNames(input);

	ASSERT_TRUE(cultureNames.takeAircraftCompanies().empty());
}


TEST(HoI4World_Names_CultureNamesTests, AircraftCompaniesCanBeAdded)
{
	std::stringstream input;
	input << "aircraft_companies = { Boeing \"Lockheed Martin\" }";
	HoI4::CultureNames cultureNames(input);

	const auto aircraftCompanies = cultureNames.takeAircraftCompanies();
	ASSERT_EQ(2, aircraftCompanies.size());
	ASSERT_EQ("Boeing", aircraftCompanies[0]);
	ASSERT_EQ("Lockheed Martin", aircraftCompanies[1]);
}


TEST(HoI4World_Names_CultureNamesTests, IntelligenceAgenciesDefaultsToEmpty)
{
	std::stringstream input;
	HoI4::CultureNames cultureNames(input);

	ASSERT_TRUE(cultureNames.takeIntelligenceAgencies().empty());
}


TEST(HoI4World_Names_CultureNamesTests, IntelligenceAgenciesCanBeAdded)
{
	std::stringstream input;
	input << "intelligence_agencies = { CIA \"No Such Agency\" }";
	HoI4::CultureNames cultureNames(input);

	const auto intelligenceAgencies = cultureNames.takeIntelligenceAgencies();
	ASSERT_EQ(2, intelligenceAgencies.size());
	ASSERT_EQ("CIA", intelligenceAgencies[0]);
	ASSERT_EQ("No Such Agency", intelligenceAgencies[1]);
}


#ifndef _DEBUG // disable some test that break code coverage
TEST(HoI4World_Names_CultureNamesTests, MaleNamesCanBeConvertedToUTF8)
{
	std::stringstream input;
	input << "first_names = { Géorge }";
	HoI4::CultureNames cultureNames(input);
	cultureNames.convertVic2NamesToUTF8();

	const auto maleNames = cultureNames.takeMaleNames();
	ASSERT_EQ(1, maleNames.size());
	ASSERT_EQ("GÃ©orge", maleNames[0]);
}


TEST(HoI4World_Names_CultureNamesTests, SurnamesCanBeConvertedToUTF8)
{
	std::stringstream input;
	input << "last_names = { Géorge }";
	HoI4::CultureNames cultureNames(input);
	cultureNames.convertVic2NamesToUTF8();

	const auto surnames = cultureNames.takeSurnames();
	ASSERT_EQ(1, surnames.size());
	ASSERT_EQ("GÃ©orge", surnames[0]);
}
#endif // _DEBUG