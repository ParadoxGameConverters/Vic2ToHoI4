#include "VersionedMappingsFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



Mappers::VersionedMappings::Factory::Factory()
{
	registerKeyword("link", [this](std::istream& theStream) {
		const auto theMapping = provinceMappingFactory.importProvinceMapping(theStream);
		if (theMapping->getHoI4Provinces().empty() && theMapping->getVic2Provinces().empty())
		{
			return;
		}
		insertIntoHoI4ToVic2ProvinceMap(theMapping->getVic2Provinces(), theMapping->getHoI4Provinces());
		insertIntoVic2ToHoI4ProvinceMap(theMapping->getVic2Provinces(), theMapping->getHoI4Provinces());
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Mappers::VersionedMappings> Mappers::VersionedMappings::Factory::importVersionedMappings(
	 std::istream& theStream)
{
	versionedMappings = std::make_unique<VersionedMappings>();
	parseStream(theStream);
	return std::move(versionedMappings);
}


void Mappers::VersionedMappings::Factory::insertIntoHoI4ToVic2ProvinceMap(const std::vector<int>& Vic2Provinces,
	 const std::vector<int>& HoI4Provinces)
{
	for (auto num: HoI4Provinces)
	{
		versionedMappings->HoI4ToVic2ProvinceMap.insert(make_pair(num, Vic2Provinces));
	}
}


void Mappers::VersionedMappings::Factory::insertIntoVic2ToHoI4ProvinceMap(const std::vector<int>& Vic2Provinces,
	 const std::vector<int>& HoI4Provinces)
{
	for (auto num: Vic2Provinces)
	{
		versionedMappings->Vic2ToHoI4ProvinceMap.insert(make_pair(num, HoI4Provinces));
	}
}