#include "src/V2World/Countries/CommonCountryDataFactory.h"
#include "external/common_items/Color.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "external/common_items/ParserHelpers.h"
#include "src/V2World/Countries/CommonCountryData.h"
#include "src/V2World/Politics/PartyFactory.h"



Vic2::CommonCountryData::Factory::Factory()
{
	registerKeyword("color", [this](std::istream& theStream) {
		const commonItems::intList color_components(theStream);
		common_country_data_->color_ = commonItems::Color(
			 std::array{color_components.getInts()[0], color_components.getInts()[1], color_components.getInts()[2]});
	});
	registerKeyword("unit_names", [this](std::istream& theStream) {
		common_country_data_->unit_names_ = unit_names_factory_.importUnitNames(theStream);
	});
	registerKeyword("party", [this](std::istream& theStream) {
		common_country_data_->parties_.emplace_back(*party_factory_.getParty(theStream));
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::CommonCountryData> Vic2::CommonCountryData::Factory::ImportCommonCountryData(
	 const std::string& filename,
	 const commonItems::ModFilesystem& mod_filesystem)
{
	common_country_data_ = std::make_unique<CommonCountryData>();

	if (const auto possible_file = mod_filesystem.GetActualFileLocation("/common/" + filename); possible_file)
	{
		parseFile(*possible_file);
	}

	return std::move(common_country_data_);
}