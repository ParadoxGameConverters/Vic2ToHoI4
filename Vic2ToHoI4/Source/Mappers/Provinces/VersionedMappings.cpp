#include "VersionedMappings.h"
#include "ProvinceMapping.h"



mappers::VersionedMappings::VersionedMappings(std::istream& theStream)
{
	registerKeyword(std::regex("link"), [this](const std::string& unused, std::istream& theStream) {
		ProvinceMapping theMapping(theStream);
		insertIntoHoI4ToVic2ProvinceMap(theMapping.getVic2Nums(), theMapping.getHoI4Nums());
		insertIntoVic2ToHoI4ProvinceMap(theMapping.getVic2Nums(), theMapping.getHoI4Nums());
	});

	parseStream(theStream);
}


void mappers::VersionedMappings::insertIntoHoI4ToVic2ProvinceMap(const std::vector<int>& Vic2Nums,
	 const std::vector<int>& HoI4Nums)
{
	for (auto num: HoI4Nums)
	{
		if (num != 0)
		{
			HoI4ToVic2ProvinceMap.insert(make_pair(num, Vic2Nums));
		}
	}
}


void mappers::VersionedMappings::insertIntoVic2ToHoI4ProvinceMap(const std::vector<int>& Vic2Nums,
	 const std::vector<int>& HoI4Nums)
{
	for (auto num: Vic2Nums)
	{
		if (num != 0)
		{
			Vic2ToHoI4ProvinceMap.insert(make_pair(num, HoI4Nums));
		}
	}
}