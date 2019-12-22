/*Copyright (c) 2018 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "CoastalProvinces.h"
#include "MapData.h"
#include "Log.h"
#include "../Configuration.h"
#include <fstream>



void HoI4::coastalProvinces::init(const MapData& theMapData)
{
	auto provinces = getProvinces();

	for (auto province: provinces)
	{
		if (!province.second.isLand)
		{
			continue;
		}

		auto neighbors = theMapData.getNeighbors(province.first);
		for (auto adjProvinceNum: neighbors)
		{
			auto adjProvince = provinces.find(adjProvinceNum);
			if ((adjProvince != provinces.end()) && (adjProvince->second.type == "ocean"))
			{
				auto coastalProvince = theCoastalProvinces.find(province.first);
				if (coastalProvince == theCoastalProvinces.end())
				{
					std::vector<int> seaProvince;
					seaProvince.push_back(adjProvinceNum);
					theCoastalProvinces.insert(make_pair(province.first, seaProvince));
				}
				else
				{
					coastalProvince->second.push_back(adjProvinceNum);
				}
			}
		}
	}
}


std::map<int, HoI4::province> HoI4::coastalProvinces::getProvinces() const
{
	std::ifstream provinceDefinitions(theConfiguration.getHoI4Path() + "/map/definition.csv");
	if (!provinceDefinitions.is_open())
	{
		LOG(LogLevel::Error) << "Could not open " << theConfiguration.getHoI4Path() << "/map/definition.csv";
		exit(-1);
	}

	std::map<int, province> provinces;
	while (!provinceDefinitions.eof())
	{
		std::string line;
		getline(provinceDefinitions, line);
		if (line.length() == 0)
		{
			break;
		}

		size_t IDSeparator = line.find_first_of(';');
		int ID = stoi(line.substr(0, IDSeparator));
		if (ID == 0)
		{
			continue;
		}
		line = line.substr(IDSeparator + 1, line.size());

		size_t redSeparator = line.find_first_of(';');
		line = line.substr(redSeparator + 1, line.size());

		size_t greenSeparator = line.find_first_of(';');
		line = line.substr(greenSeparator + 1, line.size());

		size_t blueSeparator = line.find_first_of(';');
		line = line.substr(blueSeparator + 1, line.size());

		size_t landSeaSeparator = line.find_first_of(';');
		std::string landOrSea = line.substr(0, landSeaSeparator);
		bool isLand = (landOrSea == "land");
		line = line.substr(landSeaSeparator + 1, line.size());

		size_t boolSeparator = line.find_first_of(';');
		line = line.substr(boolSeparator + 1, line.size());

		size_t typeSeparator = line.find_first_of(';');
		std::string type = line.substr(0, typeSeparator);

		province newProvince;
		newProvince.isLand = isLand;
		newProvince.type = std::move(type);
		provinces.insert(std::make_pair(ID, newProvince));
	}

	return provinces;
}


bool HoI4::coastalProvinces::isProvinceCoastal(int provinceNum) const
{
	auto province = theCoastalProvinces.find(provinceNum);
	return (province != theCoastalProvinces.end());
}