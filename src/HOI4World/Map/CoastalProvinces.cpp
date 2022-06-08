#include "src/HOI4World/Map/CoastalProvinces.h"
#include "src/Configuration.h"
#include "src/HOI4World/Map/Hoi4Province.h"
#include "external/common_items/Log.h"
#include "src/Maps/MapData.h"



void HoI4::CoastalProvinces::init(const Maps::MapData& theMapData, const std::map<int, Province>& theProvinces)
{
	Log(LogLevel::Info) << "\tInitializing coastal provinces";

	for (const auto& province: theProvinces)
	{
		if (!province.second.isLandProvince())
		{
			continue;
		}

		auto neighbors = theMapData.getNeighbors(province.first);
		for (auto adjProvinceNum: neighbors)
		{
			if (auto adjProvince = theProvinces.find(adjProvinceNum);
				 (adjProvince != theProvinces.end()) && (adjProvince->second.getType() == "ocean"))
			{
				if (auto coastalProvince = theCoastalProvinces.find(province.first);
					 coastalProvince == theCoastalProvinces.end())
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


bool HoI4::CoastalProvinces::isProvinceCoastal(const int provinceNum) const
{
	return theCoastalProvinces.contains(provinceNum);
}