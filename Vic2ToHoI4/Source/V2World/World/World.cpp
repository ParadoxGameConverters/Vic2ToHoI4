#include "World.h"
#include "Configuration.h"
#include "V2World/Provinces/Province.h"



std::optional<const std::shared_ptr<Vic2::Province>> Vic2::World::getProvince(const int provNum) const
{
	const auto provinceItr = provinces.find(provNum);
	if (provinceItr == provinces.end())
	{
		return std::nullopt;
	}

	return provinceItr->second;
}