#include "CommonCountryDataFactory.h"
#include "Color.h"
#include "CommonCountryData.h"
#include "Configuration.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"
#include "V2World/Politics/PartyFactory.h"



Vic2::CommonCountryData::Factory::Factory()
{
	registerKeyword("color", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::intList colorComponents(theStream);
		commonCountryData->theColor = commonItems::Color(
			 std::array<int, 3>{colorComponents.getInts()[0], colorComponents.getInts()[1], colorComponents.getInts()[2]});
	});
	registerKeyword("unit_names", [this](const std::string& unused, std::istream& theStream) {
		// todo - clean up this mess. Probably add a UnitNamesFactory class to handle it all
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
				commonCountryData->unitNames[*token].emplace_back(commonItems::convertWin1252ToUTF8(name));
			}

			token = getNextTokenWithoutMatching(theStream);
		}
	});
	registerKeyword("party", [this](const std::string& unused, std::istream& theStream) {
		commonCountryData->parties.emplace_back(*partyFactory.getParty(theStream));
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::CommonCountryData> Vic2::CommonCountryData::Factory::importCommonCountryData(
	 const std::string& filename,
	 const std::optional<std::string>& modFolder,
	 const Configuration& theConfiguration)
{
	commonCountryData = std::make_unique<CommonCountryData>();

	if (modFolder)
	{
		const auto file = *modFolder + "/common/countries/" + filename;
		if (commonItems::DoesFileExist(file))
		{
			parseFile(file);
			return std::move(commonCountryData);
		}
	}

	const auto file = theConfiguration.getVic2Path() + "/common/countries/" + filename;
	parseFile(file);
	return std::move(commonCountryData);
}