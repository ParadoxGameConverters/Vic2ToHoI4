#include "CommonCountryData.h"
#include "Configuration.h"
#include "Color.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"
#include "Politics/PartyFactory.h"



Vic2::commonCountryData::commonCountryData(const std::string& filename,
	 const std::optional<Mod>& mod,
	 const Configuration& theConfiguration,
	 Party::Factory* partyFactory)
{
	registerKeyword("color", [this](const std::string& unused, std::istream& theStream) {
		commonItems::intList colorInts(theStream);
		theColor = commonItems::Color(
			 std::array<int, 3>{colorInts.getInts()[0], colorInts.getInts()[1], colorInts.getInts()[2]});
	});
	registerKeyword("unit_names", [this](const std::string& unused, std::istream& theStream) {
		auto equals = getNextTokenWithoutMatching(theStream);
		auto bracket = getNextTokenWithoutMatching(theStream);
		auto token = getNextTokenWithoutMatching(theStream);
		while (token != "}")
		{
			commonItems::stringList unitNamesStrings(theStream);
			for (auto name: unitNamesStrings.getStrings())
			{
				if (name.substr(0, 1) == "\"")
				{
					name = name.substr(1, name.length() - 2);
				}
				unitNames[*token].emplace_back(commonItems::convertWin1252ToUTF8(name));
			}

			token = getNextTokenWithoutMatching(theStream);
		}
	});
	registerKeyword("party", [this, &partyFactory](const std::string& unused, std::istream& theStream) {
		parties.emplace_back(*partyFactory->getParty(theStream));
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	bool parsedFile = false;
	if (mod)
	{
		std::string file =
			 theConfiguration.getVic2Path() + "/mod/" + mod->getDirectory() + "/common/countries/" + filename;
		if (commonItems::DoesFileExist(file))
		{
			parseFile(file);
			parsedFile = true;
		}
	}
	if (!parsedFile)
	{
		std::string file = theConfiguration.getVic2Path() + "/common/countries/" + filename;
		if (commonItems::DoesFileExist(file))
		{
			parseFile(file);
		}
	}
}