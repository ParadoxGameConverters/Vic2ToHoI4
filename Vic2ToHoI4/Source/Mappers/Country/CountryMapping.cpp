#include "CountryMapping.h"
#include "V2World/World/World.h"



std::optional<std::string> Mappers::CountryMapper::getHoI4Tag(const std::string& V2Tag) const
{
	auto findIter = V2TagToHoI4TagMap.find(V2Tag);
	if (findIter != V2TagToHoI4TagMap.end())
	{
		return findIter->second;
	}
	else
	{
		return {};
	}
}


std::optional<std::string> Mappers::CountryMapper::getVic2Tag(const std::string& HoI4Tag) const
{
	auto findIter = HoI4TagToV2TagMap.find(HoI4Tag);
	if (findIter != HoI4TagToV2TagMap.end())
	{
		return findIter->second;
	}
	else
	{
		return {};
	}
}