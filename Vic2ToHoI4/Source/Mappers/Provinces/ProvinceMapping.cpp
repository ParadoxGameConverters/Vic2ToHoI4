#include "ProvinceMapping.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



mappers::ProvinceMapping::ProvinceMapping(std::istream& theStream)
{
	registerKeyword("vic2", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleInt provinceNum(theStream);
		Vic2Provinces.push_back(provinceNum.getInt());
	});
	registerKeyword("hoi4", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleInt provinceNum(theStream);
		HoI4Provinces.push_back(provinceNum.getInt());
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);

	if (Vic2Provinces.empty())
	{
		Vic2Provinces.push_back(0);
	}
	if (HoI4Provinces.empty())
	{
		HoI4Provinces.push_back(0);
	}
}