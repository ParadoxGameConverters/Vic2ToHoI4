#include "Railways.h"
#include "Log.h"



using HoI4::Railway;



std::vector<Railway> HoI4::determineRailways(const std::map<int, std::shared_ptr<Vic2::Province>>& Vic2Provinces,
	 const Maps::MapData& Vic2MapData,
	 const Mappers::ProvinceMapper& provinceMapper,
	 const Maps::MapData& HoI4MapData,
	 const Maps::ProvinceDefinitions& HoI4ProvinceDefinitions)
{
	Log(LogLevel::Info) << "\tDetermining railways";

	std::vector<Railway> railways;

	std::set<std::pair<int, int>> processedPairs;
	for (const auto& [Vic2ProvinceNum, Vic2Province]: Vic2Provinces)
	{
		if (!Vic2Province->isLandProvince())
		{
			continue;
		}

		for (const int Vic2NeighborProvinceNum: Vic2MapData.getNeighbors(Vic2ProvinceNum))
		{
			if (processedPairs.contains(std::make_pair(Vic2NeighborProvinceNum, Vic2ProvinceNum)))
			{
				continue;
			}
			processedPairs.insert(std::make_pair(Vic2ProvinceNum, Vic2NeighborProvinceNum));

			const auto& itr = Vic2Provinces.find(Vic2NeighborProvinceNum);
			if (itr == Vic2Provinces.end())
			{
				continue;
			}
			const auto& Vic2NeighborProvince = itr->second;
			if (!Vic2NeighborProvince->isLandProvince())
			{
				continue;
			}

			const int railwayLevel = (Vic2Province->getRailLevel() + Vic2NeighborProvince->getRailLevel()) / 4;
			if (railwayLevel < 1)
			{
				continue;
			}

			const auto& HoI4ProvinceNumbers = provinceMapper.getVic2ToHoI4ProvinceMapping(Vic2ProvinceNum);
			if (HoI4ProvinceNumbers.empty())
			{
				continue;
			}
			const int HoI4ProvinceNumber = HoI4ProvinceNumbers[0];

			const auto& HoI4NeighborProvinceNumbers = provinceMapper.getVic2ToHoI4ProvinceMapping(Vic2NeighborProvinceNum);
			if (HoI4NeighborProvinceNumbers.empty())
			{
				continue;
			}
			const int HoI4NeighborProvinceNumber = HoI4NeighborProvinceNumbers[0];

			if (HoI4ProvinceNumber == HoI4NeighborProvinceNumber)
			{
				continue;
			}

			std::vector<std::vector<int>> possibleRailwayPaths{{HoI4ProvinceNumber}};
			std::set<int> reachedProvinces{HoI4ProvinceNumber};
			while (!possibleRailwayPaths.empty())
			{
				std::vector<int> possibleRailwayPath = possibleRailwayPaths[0];
				if (possibleRailwayPath[possibleRailwayPath.size() - 1] == HoI4NeighborProvinceNumber)
				{
					break;
				}

				for (const auto& neighborNumber:
					 HoI4MapData.getNeighbors(possibleRailwayPath[possibleRailwayPath.size() - 1]))
				{
					if (reachedProvinces.contains(neighborNumber))
					{
						continue;
					}
					reachedProvinces.insert(neighborNumber);
					if (!HoI4ProvinceDefinitions.isLandProvince(neighborNumber))
					{
						continue;
					}

					std::vector<int> newPossibleRailwayPath = possibleRailwayPath;
					newPossibleRailwayPath.push_back(neighborNumber);
					possibleRailwayPaths.push_back(newPossibleRailwayPath);
				}
				possibleRailwayPaths.erase(possibleRailwayPaths.begin());
			}

			if (!possibleRailwayPaths.empty())
			{
				const auto& firstRailwayPath = possibleRailwayPaths[0];
				Railway railway(railwayLevel, firstRailwayPath);
				railways.push_back(railway);
			}
		}
	}

	return railways;
}