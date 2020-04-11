#include "ProvinceDefinitions.h"
#include "../Configuration.h"
#include "Log.h"
#include <fstream>



ProvinceDefinitions::ProvinceDefinitions() noexcept: landProvinces(), colorToProvinceMap()
{
	std::ifstream definitions(theConfiguration.getHoI4Path() + "/map/definition.csv");
	if (!definitions.is_open())
	{
		LOG(LogLevel::Error) << "Could not open " << theConfiguration.getHoI4Path() << "/map/definition.csv";
		exit(-1);
	}

	while (true)
	{
		std::string line;
		getline(definitions, line);
		int pos = line.find_first_of(';');
		if (pos == std::string::npos)
		{
			break;
		}
		int provNum = stoi(line.substr(0, pos));
		if (provNum == 0)
		{
			continue;
		}
		line = line.substr(pos + 1, line.length());

		pos = line.find_first_of(';');
		ConverterColor::red red(stoi(line.substr(0, pos)));
		line = line.substr(pos + 1, line.length());

		pos = line.find_first_of(';');
		ConverterColor::green green(stoi(line.substr(0, pos)));
		line = line.substr(pos + 1, line.length());

		pos = line.find_first_of(';');
		ConverterColor::blue blue(stoi(line.substr(0, pos)));
		line = line.substr(pos + 1, line.length());

		ConverterColor::Color provinceColor(red, green, blue);
		int colorInt = getIntFromColor(provinceColor);
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
}


std::optional<int> ProvinceDefinitions::getProvinceFromColor(const ConverterColor::Color& color) const
{
	int colorInt = getIntFromColor(color);

	auto mapping = colorToProvinceMap.find(colorInt);
	if (mapping != colorToProvinceMap.end())
	{
		return mapping->second;
	}
	else
	{
		return {};
	}
}


int ProvinceDefinitions::getIntFromColor(const ConverterColor::Color& color) const
{
	ConverterColor::red red;
	ConverterColor::green green;
	ConverterColor::blue blue;
	color.GetRGB(red, green, blue);
	int colorInt = ((red.Red & 0xFF) << 16) + ((green.Green & 0xFF) << 8) + (blue.Blue & 0xFF);

	return colorInt;
}