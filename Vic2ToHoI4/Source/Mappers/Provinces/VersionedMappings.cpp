#include "VersionedMappings.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"
#include "ProvinceMapping.h"
#include "ProvinceMappingFactory.h"



Mappers::VersionedMappings::VersionedMappings(std::istream& theStream)
{
	Mappers::ProvinceMapping::Factory provinceMappingFactory;
	registerKeyword("link", [this, &provinceMappingFactory](std::istream& theStream) {
		const auto theMapping = provinceMappingFactory.importProvinceMapping(theStream);
		if (theMapping->getHoI4Provinces().empty() && theMapping->getVic2Provinces().empty())
			return;
		insertIntoHoI4ToVic2ProvinceMap(theMapping->getVic2Provinces(), theMapping->getHoI4Provinces());
		insertIntoVic2ToHoI4ProvinceMap(theMapping->getVic2Provinces(), theMapping->getHoI4Provinces());
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}


void Mappers::VersionedMappings::insertIntoHoI4ToVic2ProvinceMap(const std::vector<int>& Vic2Provinces,
	 const std::vector<int>& HoI4Provinces)
{
	for (auto num: HoI4Provinces)
	{
		if (num != 0)
		{
			HoI4ToVic2ProvinceMap.insert(make_pair(num, Vic2Provinces));
		}
	}
}


void Mappers::VersionedMappings::insertIntoVic2ToHoI4ProvinceMap(const std::vector<int>& Vic2Provinces,
	 const std::vector<int>& HoI4Provinces)
{
	for (auto num: Vic2Provinces)
	{
		if (num != 0)
		{
			Vic2ToHoI4ProvinceMap.insert(make_pair(num, HoI4Provinces));
		}
	}
}