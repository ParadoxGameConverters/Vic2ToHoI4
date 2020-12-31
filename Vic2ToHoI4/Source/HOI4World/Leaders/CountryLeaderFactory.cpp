#include "CountryLeaderFactory.h"
#include "CommonRegexes.h"
#include "Log.h"
#include "ParserHelpers.h"



HoI4::CountryLeader::Factory::Factory()
{
	registerKeyword("name", [this](const std::string& unused, std::istream& theStream) {
		countryLeader->name = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("desc", [this](const std::string& unused, std::istream& theStream) {
		countryLeader->description = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("picture", [this](const std::string& unused, std::istream& theStream) {
		countryLeader->picture = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("ideology", [this](const std::string& unused, std::istream& theStream) {
		countryLeader->ideology = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("traits", [this](const std::string& unused, std::istream& theStream) {
		countryLeader->traits = commonItems::stringList{theStream}.getStrings();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


HoI4::CountryLeader HoI4::CountryLeader::Factory::createNewLeader(const std::string& primaryCulture,
	 const std::string& primaryCultureGroup,
	 const std::string& governmentIdeology,
	 const std::string& leaderIdeology,
	 Names& names,
	 graphicsMapper& theGraphics)
{
	CountryLeader leader;
	leader.ideology = leaderIdeology;
	leader.picture = theGraphics.getLeaderPortrait(primaryCultureGroup, governmentIdeology);

	const auto firstName = names.getMaleName(primaryCulture);
	const auto surname = names.getSurname(primaryCulture);

	if (!firstName || !surname)
	{
		Log(LogLevel::Warning) << "Could not set leader, as there were no names for " << primaryCulture << ".";
		return leader;
	}

	leader.name = *firstName + " " + *surname;

	auto upperFirstName = *firstName;
	std::transform(upperFirstName.begin(), upperFirstName.end(), upperFirstName.begin(), toupper);
	auto upperSurname = *surname;
	std::transform(upperSurname.begin(), upperSurname.end(), upperSurname.begin(), toupper);
	leader.description = "POLITICS_" + upperFirstName + "_" + upperSurname + "_DESC";

	return leader;
}


std::unique_ptr<HoI4::CountryLeader> HoI4::CountryLeader::Factory::importCountryLeader(std::istream& theStream)
{
	countryLeader = std::make_unique<CountryLeader>();
	parseStream(theStream);
	return std::move(countryLeader);
}