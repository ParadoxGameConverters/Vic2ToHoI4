#include "CultureNames.h"
#include "CommonRegexes.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"



HoI4::CultureNames::CultureNames(std::istream& theStream)
{
	registerKeyword("first_names", [this](std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		maleNames = nameStrings.getStrings();
	});
	registerKeyword("last_names", [this](std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		surnames = nameStrings.getStrings();
	});
	registerKeyword("female_names", [this](std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		femaleNames = nameStrings.getStrings();
	});
	registerKeyword("female_surnames", [this](std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		femaleSurnames = nameStrings.getStrings();
	});
	registerKeyword("callsigns", [this](std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		callsigns = nameStrings.getStrings();
	});
	registerKeyword("industry_companies", [this](std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		industryCompanies = nameStrings.getStrings();
	});
	registerKeyword("electronic_companies", [this](std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		electronicCompanies = nameStrings.getStrings();
	});
	registerKeyword("car_companies", [this](std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		carCompanies = nameStrings.getStrings();
	});
	registerKeyword("naval_companies", [this](std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		navalCompanies = nameStrings.getStrings();
	});
	registerKeyword("weapon_companies", [this](std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		weaponCompanies = nameStrings.getStrings();
	});
	registerKeyword("aircraft_companies", [this](std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		aircraftCompanies = nameStrings.getStrings();
	});
	registerKeyword("intelligence_agencies", [this](std::istream& theStream) {
		const commonItems::stringList nameStrings(theStream);
		intelligenceAgencies = nameStrings.getStrings();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}


void HoI4::CultureNames::convertVic2NamesToUTF8()
{
	std::for_each(maleNames.begin(), maleNames.end(), [](std::string& name) {
		name = commonItems::convertWin1252ToUTF8(name);
	});
	std::for_each(surnames.begin(), surnames.end(), [](std::string& name) {
		name = commonItems::convertWin1252ToUTF8(name);
	});
}