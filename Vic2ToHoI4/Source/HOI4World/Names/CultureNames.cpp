#include "CultureNames.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"



HoI4::CultureNames::CultureNames(std::istream& theStream)
{
	registerKeyword("first_names", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		maleNames = nameStrings.getStrings();
	});
	registerKeyword("last_names", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		surnames = nameStrings.getStrings();
	});
	registerKeyword("female_names", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		femaleNames = nameStrings.getStrings();
	});
	registerKeyword("female_surnames", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		femaleSurnames = nameStrings.getStrings();
	});
	registerKeyword("callsigns", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		callsigns = nameStrings.getStrings();
	});
	registerKeyword("industry_companies", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		industryCompanies = nameStrings.getStrings();
	});
	registerKeyword("electronic_companies", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		electronicCompanies = nameStrings.getStrings();
	});
	registerKeyword("car_companies", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		carCompanies = nameStrings.getStrings();
	});
	registerKeyword("naval_companies", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		navalCompanies = nameStrings.getStrings();
	});
	registerKeyword("weapon_companies", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		weaponCompanies = nameStrings.getStrings();
	});
	registerKeyword("aircraft_companies", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		aircraftCompanies = nameStrings.getStrings();
	});
	registerKeyword("intelligence_agencies", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		intelligenceAgencies = nameStrings.getStrings();
	});
	registerRegex("[A-Za-z0-9\\_]+", commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}


void HoI4::CultureNames::convertVic2NamesToUTF8()
{
	std::for_each(maleNames.begin(), maleNames.end(), [](std::string& name) {
		name = Utils::convertWin1252ToUTF8(name);
	});
	std::for_each(surnames.begin(), surnames.end(), [](std::string& name) {
		name = Utils::convertWin1252ToUTF8(name);
	});
}