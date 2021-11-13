#include "CountryLeaderFactory.h"
#include "CommonFunctions.h"
#include "CommonRegexes.h"
#include "Log.h"
#include "ParserHelpers.h"



HoI4::CountryLeader::Factory::Factory()
{
	registerKeyword("name", [this](std::istream& theStream) {
		countryLeader->name = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("desc", [this](std::istream& theStream) {
		countryLeader->description = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("picture", [this](std::istream& theStream) {
		countryLeader->picture = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("ideology", [this](std::istream& theStream) {
		countryLeader->ideology = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("traits", [this](std::istream& theStream) {
		countryLeader->traits = commonItems::stringList{theStream}.getStrings();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


HoI4::CountryLeader HoI4::CountryLeader::Factory::createNewLeader(
	 const std::pair<std::string, std::string>& nextMonarch,
	 const std::string& primaryCulture,
	 const std::string& primaryCultureGroup,
	 const std::string& governmentIdeology,
	 const std::string& leaderIdeology,
	 Names& names,
	 Mappers::GraphicsMapper& graphicsMapper)
{
	CountryLeader leader;
	leader.ideology = leaderIdeology;
	leader.picture = graphicsMapper.getLeaderPortrait(primaryCulture, primaryCultureGroup, governmentIdeology);

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

	if (auto [regnalName, regnalNumber] = nextMonarch; !regnalName.empty())
	{
		if (!regnalNumber.empty())
		{
			leader.name = "King " + regnalName + " " + regnalNumber;
			std::transform(regnalName.begin(), regnalName.end(), regnalName.begin(), toupper);
			std::transform(regnalNumber.begin(), regnalNumber.end(), regnalNumber.begin(), toupper);
			leader.description = "POLITICS_KING_" + regnalName + "_" + regnalNumber + "_DESC";
		}
		else
		{
			leader.name = "King " + *firstName;
			leader.description = "POLITICS_KING_" + upperFirstName + "_DESC";
		}
	}

	return leader;
}


std::unique_ptr<HoI4::CountryLeader> HoI4::CountryLeader::Factory::importCountryLeader(std::istream& theStream)
{
	countryLeader = std::make_unique<CountryLeader>();
	parseStream(theStream);
	return std::move(countryLeader);
}