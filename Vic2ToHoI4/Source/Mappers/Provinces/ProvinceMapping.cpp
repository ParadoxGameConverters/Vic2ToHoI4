#include "ProvinceMapping.h"
#include "ParserHelpers.h"



mappers::ProvinceMapping::ProvinceMapping(std::istream& theStream)
{
	registerKeyword(std::regex("vic2"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt provinceNum(theStream);
		Vic2Nums.push_back(provinceNum.getInt());
	});
	registerKeyword(std::regex("hoi4"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt provinceNum(theStream);
		HoI4Nums.push_back(provinceNum.getInt());
	});

	parseStream(theStream);

	if (Vic2Nums.size() == 0)
	{
		Vic2Nums.push_back(0);
	}
	if (HoI4Nums.size() == 0)
	{
		HoI4Nums.push_back(0);
	}
}