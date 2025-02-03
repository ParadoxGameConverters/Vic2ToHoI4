#include "src/V2World/Map/Vic2ProvinceDefinitionImporter.h"
#include <fstream>



namespace
{

std::optional<int> extractNumber(std::string& string)
{
	const auto pos = string.find_first_of(';');
	if (pos == std::string::npos)
	{
		return std::nullopt;
	}

	const auto provinceNumberString = string.substr(0, pos);
	string = string.substr(pos + 1, string.length());

	if (provinceNumberString.empty())
	{
		return std::nullopt;
	}
	try
	{
		return std::stoi(provinceNumberString);
	}
	catch (...)
	{
		return std::nullopt;
	}
}

} // namespace



Maps::ProvinceDefinitions Vic2::ImportProvinceDefinitions(const commonItems::ModFilesystem& mod_filesystem,
	 const std::map<int, std::shared_ptr<Province>>& provinces)
{
	const auto path = mod_filesystem.GetActualFileLocation("/map/definition.csv");
	if (!path)
	{
		throw std::runtime_error("Could not find /map/definition.csv");
	}

	std::ifstream definitions(*path);
	if (!definitions.is_open())
	{
		throw std::runtime_error("Could not open " + path->string());
	}

	std::set<int> landProvinces;
	std::set<int> seaProvinces;
	std::map<int, std::string> terrain_types;
	std::map<int, int> colorToProvinceMap;

	while (true)
	{
		std::string line;
		getline(definitions, line);
		if (line.empty())
		{
			break;
		}
		if (line.starts_with("province"))
		{
			continue;
		}

		const auto provinceNumber = extractNumber(line);
		if (!provinceNumber)
		{
			continue;
		}

		const auto red = extractNumber(line);
		if (!red)
		{
			continue;
		}

		const auto green = extractNumber(line);
		if (!green)
		{
			continue;
		}

		const auto blue = extractNumber(line);
		if (!blue)
		{
			continue;
		}

		auto colorInt = Maps::getIntFromColor(commonItems::Color(std::array{*red, *green, *blue}));
		colorToProvinceMap.insert(std::make_pair(colorInt, *provinceNumber));

		const auto possibleProvince = provinces.find(*provinceNumber);
		if (possibleProvince == provinces.end() || !possibleProvince->second)
		{
			continue;
		}

		if (possibleProvince->second->isLandProvince())
		{
			landProvinces.insert(*provinceNumber);
		}
		else
		{
			seaProvinces.insert(*provinceNumber);
		}
	}

	return Maps::ProvinceDefinitions(landProvinces, seaProvinces, terrain_types, colorToProvinceMap);
}