#include "Railways.h"
#include "Log.h"



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


std::optional<int> getHoI4ProvinceNumber(int Vic2ProvinceNum, const Mappers::ProvinceMapper& provinceMapper)
{
	const auto& HoI4ProvinceNumbers = provinceMapper.getVic2ToHoI4ProvinceMapping(Vic2ProvinceNum);
	if (HoI4ProvinceNumbers.empty())
	{
		return std::nullopt;
	}

	return HoI4ProvinceNumbers[0];
}


bool HoI4ProvinceNumbersAreValid(std::optional<int> firstNumber, std::optional<int> secondNumber)
{
	return firstNumber && secondNumber && *firstNumber != *secondNumber;
}


std::optional<std::vector<int>> findPath(int startProvince,
	 int endProvince,
	 const Maps::MapData& HoI4MapData,
	 const Maps::ProvinceDefinitions& HoI4ProvinceDefinitions)
{
	std::vector<std::vector<int>> possibleRailwayPaths{{startProvince}};
	std::set reachedProvinces{startProvince};

	while (!possibleRailwayPaths.empty())
	{
		std::vector<int> possibleRailwayPath = possibleRailwayPaths[0];
		if (possibleRailwayPath[possibleRailwayPath.size() - 1] == endProvince)
		{
			break;
		}

		for (const auto& neighborNumber: HoI4MapData.getNeighbors(possibleRailwayPath[possibleRailwayPath.size() - 1]))
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

	if (possibleRailwayPaths.empty())
	{
		return std::nullopt;
	}
	return possibleRailwayPaths[0];
}

} // namespace



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

			const auto& Vic2NeighborProvince = getValidVic2Province(Vic2NeighborProvinceNum, Vic2Provinces);
			if (Vic2NeighborProvince == nullptr)
			{
				continue;
			}

			const int railwayLevel = (Vic2Province->getRailLevel() + Vic2NeighborProvince->getRailLevel()) / 4;
			if (railwayLevel < 1)
			{
				continue;
			}

			const auto HoI4ProvinceNumber = getHoI4ProvinceNumber(Vic2ProvinceNum, provinceMapper);
			const auto HoI4NeighborProvinceNumber = getHoI4ProvinceNumber(Vic2NeighborProvinceNum, provinceMapper);
			if (!HoI4ProvinceNumbersAreValid(HoI4ProvinceNumber, HoI4NeighborProvinceNumber))
			{
				continue;
			}

			if (const auto possiblePath =
					  findPath(*HoI4ProvinceNumber, *HoI4NeighborProvinceNumber, HoI4MapData, HoI4ProvinceDefinitions);
				 possiblePath)
			{
				Railway railway(railwayLevel, *possiblePath);
				railways.push_back(railway);
			}
		}
	}

	return railways;
}