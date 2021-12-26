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

	const auto mapping = colorToProvinceMap.find(colorInt);
	if (mapping == colorToProvinceMap.end())
	{
		return std::nullopt;
	}
	return mapping->second;
}


std::string Maps::ProvinceDefinitions::getTerrainType(int province) const
{
	const auto terrain = terrain_types_.find(province);
	if (terrain == terrain_types_.end())
	{
		return "";
	}

	return terrain->second;
}