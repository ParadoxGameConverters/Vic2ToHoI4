#include "ProvinceDefinitions.h"
#include "Configuration.h"
#include <fstream>



int getIntFromColor(const commonItems::Color& color)
{
	auto [r, g, b] = color.getRgbComponents();

	return ((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF);
}


Maps::ProvinceDefinitions Maps::importProvinceDefinitions(const std::string& path)
{
	std::ifstream definitions(path + "/map/definition.csv");
	if (!definitions.is_open())
	{
		throw std::runtime_error("Could not open " + path + "/map/definition.csv");
	}

	std::set<int> landProvinces;
	std::set<int> seaProvinces;
	std::map<int, int> colorToProvinceMap;

	while (true)
	{
		std::string line;
		getline(definitions, line);
		auto pos = line.find_first_of(';');
		if (pos == std::string::npos)
		{
			break;
		}
		auto provNum = stoi(line.substr(0, pos));
		if (provNum == 0)
		{
			continue;
		}
		line = line.substr(pos + 1, line.length());

		pos = line.find_first_of(';');
		const int red(stoi(line.substr(0, pos)));
		line = line.substr(pos + 1, line.length());

		pos = line.find_first_of(';');
		const int green(stoi(line.substr(0, pos)));
		line = line.substr(pos + 1, line.length());

		pos = line.find_first_of(';');
		const int blue(stoi(line.substr(0, pos)));
		line = line.substr(pos + 1, line.length());

		auto colorInt = getIntFromColor(commonItems::Color(std::array{red, green, blue}));
		colorToProvinceMap.insert(std::make_pair(colorInt, provNum));

		pos = line.find_first_of(';');
		line = line.substr(0, pos);
		if (line == "land")
		{
			landProvinces.insert(provNum);
		}
		else if (line == "sea")
		{
			seaProvinces.insert(provNum);
		}
	}

	return ProvinceDefinitions(landProvinces, seaProvinces, colorToProvinceMap);
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