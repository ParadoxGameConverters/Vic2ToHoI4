#include "Regions.h"



std::optional<std::string> HoI4::Regions::getRegion(int provinceNumber) const
{
	if (regionsMap.contains(provinceNumber))
	{
		return regionsMap.at(provinceNumber);
	}
	else
	{
		return std::nullopt;
	}
}