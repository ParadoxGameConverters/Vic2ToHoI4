#include "HoI4Provinces.h"
#include "external/common_items/Log.h"
#include <fstream>



std::map<int, HoI4::Province> HoI4::importProvinces(const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\tImporting HoI4 province definitions";

	std::ifstream provinceDefinitions(theConfiguration.getHoI4Path() + "/map/definition.csv");
	if (!provinceDefinitions.is_open())
	{
		throw std::runtime_error("Could not open " + theConfiguration.getHoI4Path() + "/map/definition.csv");
	}

	std::map<int, Province> provinces;
	while (!provinceDefinitions.eof())
	{
		std::string line;
		getline(provinceDefinitions, line);
		if (line.length() == 0)
		{
			break;
		}

		auto IDSeparator = line.find_first_of(';');
		auto ID = stoi(line.substr(0, IDSeparator));
		if (ID == 0)
		{
			continue;
		}
		line = line.substr(IDSeparator + 1, line.size());

		auto redSeparator = line.find_first_of(';');
		line = line.substr(redSeparator + 1, line.size());

		auto greenSeparator = line.find_first_of(';');
		line = line.substr(greenSeparator + 1, line.size());

		auto blueSeparator = line.find_first_of(';');
		line = line.substr(blueSeparator + 1, line.size());

		auto landSeaSeparator = line.find_first_of(';');
		auto landOrSea = line.substr(0, landSeaSeparator);
		auto isLand = (landOrSea == "land");
		line = line.substr(landSeaSeparator + 1, line.size());

		auto boolSeparator = line.find_first_of(';');
		line = line.substr(boolSeparator + 1, line.size());

		auto typeSeparator = line.find_first_of(';');
		auto type = line.substr(0, typeSeparator);

		Province newProvince(isLand, type);
		provinces.insert(std::make_pair(ID, newProvince));
	}

	return provinces;
}
