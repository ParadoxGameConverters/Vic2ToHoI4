#include "CoastalProvinces.h"
#include "../../Configuration.h"
#include "HoI4Provinces.h"
#include "Hoi4Province.h"
#include "Log.h"
#include "MapData.h"



void HoI4::CoastalProvinces::init(const MapData& theMapData, const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\tInitializing coastal provinces";

	auto provinces = importProvinces(theConfiguration);

	for (const auto& province: provinces)
	{
		if (!province.second.isLandProvince())
		{
			continue;
		}

		auto neighbors = theMapData.getNeighbors(province.first);
		for (auto adjProvinceNum: neighbors)
		{
			if (auto adjProvince = provinces.find(adjProvinceNum);
				 (adjProvince != provinces.end()) && (adjProvince->second.getType() == "ocean"))
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
	return theCoastalProvinces.find(provinceNum) != theCoastalProvinces.end();
}