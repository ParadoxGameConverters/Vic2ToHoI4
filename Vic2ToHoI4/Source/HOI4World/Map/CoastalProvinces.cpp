#include "CoastalProvinces.h"
#include "Hoi4Province.h"
#include "MapData.h"
#include "Log.h"
#include "../../Configuration.h"
#include <fstream>



void HoI4::coastalProvinces::init(const MapData& theMapData)
{
	auto provinces = getProvinces();

	for (auto province: provinces)
	{
		if (!province.second.isLandProvince())
		{
			continue;
		}

		auto neighbors = theMapData.getNeighbors(province.first);
		for (auto adjProvinceNum: neighbors)
		{
			auto adjProvince = provinces.find(adjProvinceNum);
			if ((adjProvince != provinces.end()) && (adjProvince->second.getType() == "ocean"))
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


std::map<int, HoI4::Province> HoI4::coastalProvinces::getProvinces() const
{
	std::ifstream provinceDefinitions(theConfiguration.getHoI4Path() + "/map/definition.csv");
	if (!provinceDefinitions.is_open())
	{
		LOG(LogLevel::Error) << "Could not open " << theConfiguration.getHoI4Path() << "/map/definition.csv";
		exit(-1);
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

		Province newProvince(isLand, type);
		provinces.insert(std::make_pair(ID, newProvince));
	}

	return provinces;
}


bool HoI4::coastalProvinces::isProvinceCoastal(int provinceNum) const
{
	auto province = theCoastalProvinces.find(provinceNum);
	return (province != theCoastalProvinces.end());
}