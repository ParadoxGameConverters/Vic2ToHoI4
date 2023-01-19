#include "src/Mappers/Country/CountryMapper.h"
#include "src/V2World/World/World.h"



std::optional<std::string> Mappers::CountryMapper::getHoI4Tag(const std::string& V2Tag) const
{
	const auto mapping = Vic2TagToHoI4TagMap.find(V2Tag);
	if (mapping == Vic2TagToHoI4TagMap.end())
	{
		return std::nullopt;
	}

	return mapping->second;
}