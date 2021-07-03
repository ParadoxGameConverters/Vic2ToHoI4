#include "CommonCountryDataFactory.h"
#include "Color.h"
#include "CommonCountryData.h"
#include "CommonRegexes.h"
#include "Configuration.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"
#include "V2World/Politics/PartyFactory.h"



Vic2::CommonCountryData::Factory::Factory()
{
	registerKeyword("color", [this](std::istream& theStream) {
		const commonItems::intList colorComponents(theStream);
		commonCountryData->theColor = commonItems::Color(
			 std::array{colorComponents.getInts()[0], colorComponents.getInts()[1], colorComponents.getInts()[2]});
	});
	registerKeyword("unit_names", [this](std::istream& theStream) {
		commonCountryData->unitNames = unitNamesFactory.importUnitNames(theStream);
	});
	registerKeyword("party", [this](std::istream& theStream) {
		commonCountryData->parties.emplace_back(*partyFactory.getParty(theStream));
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::CommonCountryData> Vic2::CommonCountryData::Factory::importCommonCountryData(
	 const std::string& filename,
	 const Mods& vic2Mods,
	 const Configuration& theConfiguration)
{
	commonCountryData = std::make_unique<CommonCountryData>();

	for (const auto& mod: vic2Mods)
	{
		const auto file = mod.path + "/common/countries/" + filename;
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