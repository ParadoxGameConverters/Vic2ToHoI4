#include "CountryNameMapper.h"



std::optional<std::string> Mappers::CountryNameMapper::getVic2Government(const std::string& HoI4Ideology,
	 const std::string& Vic2Tag) const
{
	for (const auto& mapping: mappings)
	{
		if ((HoI4Ideology == mapping.hoi4Ideology) && (mapping.vic2Tag.empty() || Vic2Tag == mapping.vic2Tag))
		{
			return mapping.vic2Government;
		}
	}

	return std::nullopt;
}