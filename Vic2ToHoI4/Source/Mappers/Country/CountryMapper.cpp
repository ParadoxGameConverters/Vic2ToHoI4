#include "CountryMapper.h"
#include "V2World/World/World.h"



std::optional<std::string> Mappers::CountryMapper::getHoI4Tag(const std::string& V2Tag) const
{
	const auto mapping = V2TagToHoI4TagMap.find(V2Tag);
	if (mapping == V2TagToHoI4TagMap.end())
	{
		return std::nullopt;
	}

	return mapping->second;
}


std::optional<std::string> Mappers::CountryMapper::getVic2Tag(const std::string& HoI4Tag) const
{
	const auto mapping = HoI4TagToV2TagMap.find(HoI4Tag);
	if (mapping == HoI4TagToV2TagMap.end())
	{
		return std::nullopt;
	}

	return mapping->second;
}