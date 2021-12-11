#include "Vic2ProvinceDefinitionImporter.h"
#include <fstream>



Maps::ProvinceDefinitions Vic2::importProvinceDefinitions(const std::string& path,
	 const std::map<int, std::shared_ptr<Province>>& provinces)
{
	const auto filepath = path + "/map/definition.csv";
	std::ifstream definitions(filepath);
	if (!definitions.is_open())
	{
		throw std::runtime_error("Could not open " + filepath);
	}

	std::set<int> landProvinces;
	std::set<int> seaProvinces;
	std::map<int, int> colorToProvinceMap;

	while (true)
	{
		std::string line;
		getline(definitions, line);
		if (line.starts_with("province"))
		{
			continue;
		}

		auto pos = line.find_first_of(';');
		if (pos == std::string::npos)
		{
			break;
		}

		const auto provinceNumberString = line.substr(0, pos);
		if (provinceNumberString.empty())
		{
			continue;
		}
		const int provinceNumber = stoi(provinceNumberString);
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

		auto colorInt = Maps::getIntFromColor(commonItems::Color(std::array{red, green, blue}));
		colorToProvinceMap.insert(std::make_pair(colorInt, provinceNumber));

		const auto possibleProvince = provinces.find(provinceNumber);
		if (possibleProvince == provinces.end() || !possibleProvince->second)
		{
			continue;
		}

		if (possibleProvince->second->isLandProvince())
		{
			landProvinces.insert(provinceNumber);
		}
		else
		{
			seaProvinces.insert(provinceNumber);
		}
	}

	return Maps::ProvinceDefinitions(landProvinces, seaProvinces, colorToProvinceMap);
}