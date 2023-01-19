#include "src/Mappers/Provinces/ProvinceMappingFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



Mappers::ProvinceMapping::Factory::Factory()
{
	registerKeyword("vic2", [this](std::istream& theStream) {
		provinceMapping->Vic2Provinces.push_back(commonItems::singleInt(theStream).getInt());
	});
	registerKeyword("hoi4", [this](std::istream& theStream) {
		provinceMapping->HoI4Provinces.push_back(commonItems::singleInt(theStream).getInt());
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Mappers::ProvinceMapping> Mappers::ProvinceMapping::Factory::importProvinceMapping(
	 std::istream& theStream)
{
	provinceMapping = std::make_unique<ProvinceMapping>();
	parseStream(theStream);

	return std::move(provinceMapping);
}