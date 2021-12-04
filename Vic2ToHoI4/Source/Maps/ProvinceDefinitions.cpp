#include "ProvinceDefinitions.h"
#include "Configuration.h"



int Maps::getIntFromColor(const commonItems::Color& color)
{
	auto [r, g, b] = color.getRgbComponents();

	return ((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF);
}


std::optional<int> Maps::ProvinceDefinitions::getProvinceFromColor(const commonItems::Color& color) const
{
	const auto colorInt = getIntFromColor(color);

	if (const auto mapping = colorToProvinceMap.find(colorInt); mapping != colorToProvinceMap.end())
	{
		return mapping->second;
	}
	else
	{
		return std::nullopt;
	}
}