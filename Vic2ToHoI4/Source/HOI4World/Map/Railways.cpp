#include "Railways.h"
#include "HOI4World/Map/PossiblePath.h"
#include "Log.h"
#include <queue>



using HoI4::Railway;



namespace
{

std::shared_ptr<Vic2::Province> getValidVic2Province(int provinceNum,
	 const std::map<int, std::shared_ptr<Vic2::Province>>& Vic2Provinces)
{
	const auto& itr = Vic2Provinces.find(provinceNum);
	if (itr == Vic2Provinces.end())
	{
		return nullptr;
	}
	const auto& province = itr->second;
	if (!province->isLandProvince())
	{
		return nullptr;
	}

	return province;
}

// For the given inputs, these are the outputs
//
//   0 1 2 3 4 5 6
//  +-------------
// 0|0 0 0 0 0 0 0
// 1|0 0 0 0 0 1 1
// 2|0 0 0 0 1 1 2
// 3|0 0 0 1 1 2 2
// 4|0 0 1 1 2 2 3
// 5|0 1 1 2 2 3 3
// 6|0 1 2 2 3 3 3
int getRailwayLevel(int provinceOneRailLevel, int provinceTwoRailLevel)
{
	if (provinceOneRailLevel == 0 || provinceTwoRailLevel == 0)
	{
		return 0;
	}

	return std::clamp((provinceOneRailLevel - 2 + provinceTwoRailLevel - 2) / 2, 0, 3);
}


std::optional<int> getBestHoI4ProvinceNumber(int Vic2ProvinceNum,
	 const Mappers::ProvinceMapper& provinceMapper,
	 const HoI4::ImpassableProvinces& impassableProvinces,
	 const std::map<int, HoI4::Province>& hoi4Provinces,
	 const std::set<int>& navalBaseLocations)
{
	const auto& HoI4ProvinceNumbers = provinceMapper.getVic2ToHoI4ProvinceMapping(Vic2ProvinceNum);
	if (HoI4ProvinceNumbers.empty())
	{
		return std::nullopt;
	}

	// prefer naval bases
	for (const auto provinceNumber: HoI4ProvinceNumbers)
	{
		if (!navalBaseLocations.contains(provinceNumber))
		{
			continue;
		}

		const auto province = hoi4Provinces.find(provinceNumber);
		if (province == hoi4Provinces.end())
		{
			continue;
		}
		if (!province->second.isLandProvince())
		{
			continue;
		}
		if (impassableProvinces.isProvinceImpassable(provinceNumber))
		{
			continue;
		}

		return provinceNumber;
	}

	// find an appropriate province in priority of the mapping
	for (const auto provinceNumber: HoI4ProvinceNumbers)
	{
		const auto province = hoi4Provinces.find(provinceNumber);
		if (province == hoi4Provinces.end())
		{
			continue;
		}
		if (!province->second.isLandProvince())
		{
			continue;
		}
		if (impassableProvinces.isProvinceImpassable(provinceNumber))
		{
			continue;
		}

		return provinceNumber;
	}

	return std::nullopt;
}


bool HoI4ProvinceNumbersAreValid(std::optional<int> firstNumber, std::optional<int> secondNumber)
{
	return firstNumber && secondNumber && *firstNumber != *secondNumber;
}


constexpr int urban_cost = 1;
constexpr int plains_cost = 2;
constexpr int forest_cost = 3;
constexpr int hills_cost = 3;
constexpr int desert_cost = 5;
constexpr int marsh_cost = 5;
constexpr int jungle_cost = 8;
constexpr int mountain_cost = 8;
constexpr int unhandled_cost = 100;
int getCostForTerrainType(const std::string& terrainType)
{
	if (terrainType == "urban")
	{
		return urban_cost;
	}
	if (terrainType == "plains")
	{
		return plains_cost;
	}
	if (terrainType == "forest")
	{
		return forest_cost;
	}
	if (terrainType == "hills")
	{
		return hills_cost;
	}
	if (terrainType == "desert")
	{
		return desert_cost;
	}
	if (terrainType == "marsh")
	{
		return marsh_cost;
	}
	if (terrainType == "jungle")
	{
		return jungle_cost;
	}
	if (terrainType == "mountain")
	{
		return mountain_cost;
	}

	Log(LogLevel::Warning) << "Unhandled terrain type " << terrainType << ". Please inform the converter team.";
	return unhandled_cost;
}


double getDistanceBetweenProvinces(int provinceOne, int provinceTwo, const Maps::MapData& HoI4MapData)
{
	const auto possibleProvinceOnePoints = HoI4MapData.getProvincePoints(provinceOne);
	if (!possibleProvinceOnePoints)
	{
		return std::numeric_limits<double>::max();
	}
	const auto provinceOneCentermostPoint = possibleProvinceOnePoints->getCentermostPoint();

	const auto possibleProvinceTwoPoints = HoI4MapData.getProvincePoints(provinceTwo);
	if (!possibleProvinceTwoPoints)
	{
		return std::numeric_limits<double>::max();
	}
	const auto provinceTwoCentermostPoint = possibleProvinceTwoPoints->getCentermostPoint();

	const int deltaX = provinceOneCentermostPoint.first - provinceTwoCentermostPoint.first;
	const int deltaY = provinceOneCentermostPoint.second - provinceTwoCentermostPoint.second;
	return std::sqrt(deltaX * deltaX + deltaY * deltaY);
}


std::optional<std::vector<int>> findPath(int startProvince,
	 int endProvince,
	 int vic2StartProvince,
	 int vic2EndProvince,
	 const Mappers::ProvinceMapper& provinceMapper,
	 const Maps::MapData& HoI4MapData,
	 const Maps::ProvinceDefinitions& HoI4ProvinceDefinitions)
{
	std::priority_queue<HoI4::PossiblePath> possibleRailwayPaths;
	std::set reachedProvinces{startProvince};

	const HoI4::PossiblePath startingPath(startProvince);
	possibleRailwayPaths.push(startingPath);

	while (!possibleRailwayPaths.empty() && possibleRailwayPaths.top().getLastProvince() != endProvince)
	{
		auto possibleRailwayPath = possibleRailwayPaths.top();
		possibleRailwayPaths.pop();

		const auto lastProvince = possibleRailwayPath.getLastProvince();
		for (const auto& neighborNumber: HoI4MapData.getNeighbors(lastProvince))
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
			const auto& vic2NeighborNumbers = provinceMapper.getHoI4ToVic2ProvinceMapping(neighborNumber);
			bool neighborIsValid = false;
			for (const auto& vic2NeighborNumber: vic2NeighborNumbers)
			{
				if (vic2NeighborNumber == vic2StartProvince || vic2NeighborNumber == vic2EndProvince)
				{
					neighborIsValid = true;
					break;
				}
			}
			if (!neighborIsValid)
			{
				continue;
			}

			auto newPossibleRailwayPath = possibleRailwayPath;
			newPossibleRailwayPath.addProvince(neighborNumber,
				 getCostForTerrainType(HoI4ProvinceDefinitions.getTerrainType(neighborNumber)) *
					  getDistanceBetweenProvinces(neighborNumber, lastProvince, HoI4MapData));
			possibleRailwayPaths.push(newPossibleRailwayPath);
		}
	}

	if (possibleRailwayPaths.empty())
	{
		return std::nullopt;
	}
	return possibleRailwayPaths.top().getProvinces();
}

} // namespace



HoI4::Railways::Railways(const std::map<int, std::shared_ptr<Vic2::Province>>& Vic2Provinces,
	 const Maps::MapData& Vic2MapData,
	 const Mappers::ProvinceMapper& provinceMapper,
	 const Maps::MapData& HoI4MapData,
	 const Maps::ProvinceDefinitions& HoI4ProvinceDefinitions,
	 const ImpassableProvinces& impassableProvinces,
	 const std::map<int, Province>& hoi4Provinces,
	 const std::set<int>& navalBaseLocations)
{
	Log(LogLevel::Info) << "\tDetermining railways";

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

			const auto& Vic2NeighborProvince = getValidVic2Province(Vic2NeighborProvinceNum, Vic2Provinces);
			if (Vic2NeighborProvince == nullptr)
			{
				continue;
			}

			const int railwayLevel = getRailwayLevel(Vic2Province->getRailLevel(), Vic2NeighborProvince->getRailLevel());
			if (railwayLevel < 1)
			{
				continue;
			}

			const auto HoI4ProvinceNumber = getBestHoI4ProvinceNumber(Vic2ProvinceNum,
				 provinceMapper,
				 impassableProvinces,
				 hoi4Provinces,
				 navalBaseLocations);
			const auto HoI4NeighborProvinceNumber = getBestHoI4ProvinceNumber(Vic2NeighborProvinceNum,
				 provinceMapper,
				 impassableProvinces,
				 hoi4Provinces,
				 navalBaseLocations);
			if (!HoI4ProvinceNumbersAreValid(HoI4ProvinceNumber, HoI4NeighborProvinceNumber))
			{
				continue;
			}

			if (const auto possiblePath = findPath(*HoI4ProvinceNumber,
					  *HoI4NeighborProvinceNumber,
					  Vic2ProvinceNum,
					  Vic2NeighborProvinceNum,
					  provinceMapper,
					  HoI4MapData,
					  HoI4ProvinceDefinitions);
				 possiblePath)
			{
				Railway railway(railwayLevel, *possiblePath);
				railways_.push_back(railway);
				railway_endpoints_.insert(*HoI4ProvinceNumber);
				railway_endpoints_.insert(*HoI4NeighborProvinceNumber);
			}
		}
	}
}