#include "HoI4ProvinceDefinitionImporter.h"
#include <fstream>



Maps::ProvinceDefinitions HoI4::importProvinceDefinitions(const std::string& path)
{
	std::ifstream definitions(path + "/map/definition.csv");
	if (!definitions.is_open())
	{
		throw std::runtime_error("Could not open " + path + "/map/definition.csv");
	}

	std::set<int> landProvinces;
	std::set<int> seaProvinces;
	std::map<int, std::string> terrain_types;
	std::map<int, int> colorToProvinceMap;

	while (true)
	{
		std::string line;
		getline(definitions, line);

		// number
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

		// red
		pos = line.find_first_of(';');
		if (pos == std::string::npos)
		{
			break;
		}
		const int red(stoi(line.substr(0, pos)));
		line = line.substr(pos + 1, line.length());

		// green
		pos = line.find_first_of(';');
		if (pos == std::string::npos)
		{
			break;
		}
		const int green(stoi(line.substr(0, pos)));
		line = line.substr(pos + 1, line.length());

		// blue
		pos = line.find_first_of(';');
		if (pos == std::string::npos)
		{
			break;
		}
		const int blue(stoi(line.substr(0, pos)));
		line = line.substr(pos + 1, line.length());

		auto colorInt = Maps::getIntFromColor(commonItems::Color(std::array{red, green, blue}));
		colorToProvinceMap.insert(std::make_pair(colorInt, provNum));

		// land or sea
		pos = line.find_first_of(';');
		if (pos == std::string::npos)
		{
			break;
		}
		const std::string landOrSea = line.substr(0, pos);
		line = line.substr(pos + 1, line.length());
		if (landOrSea == "land")
		{
			landProvinces.insert(provNum);
		}
		else if (landOrSea == "sea")
		{
			seaProvinces.insert(provNum);
		}

		// false or true
		pos = line.find_first_of(';');
		if (pos == std::string::npos)
		{
			break;
		}
		line = line.substr(pos + 1, line.length());

		// terrain
		pos = line.find_first_of(';');
		if (pos == std::string::npos)
		{
			break;
		}
		const std::string terrain = line.substr(0, pos);
		line = line.substr(pos + 1, line.length());
		terrain_types.emplace(provNum, terrain);
	}

	return Maps::ProvinceDefinitions(landProvinces, seaProvinces, terrain_types, colorToProvinceMap);
}