#include "src/HOI4World/Map/Railways.h"
#include "external/common_items/Log.h"
#include "src/HOI4World/Map/PossiblePath.h"
#include <cmath>
#include <numeric>
#include <queue>
#include <ranges>



using HoI4::Railway;


#pragma optimize("",off)
namespace
{

std::set<int> FindValidVic2ProvinceNumbers(const std::vector<std::reference_wrapper<const Vic2::State>>& states)
{
	std::set<int> valid_vic2_province_numbers;

	for (const auto& state: states)
	{
		for (const auto& province_number: state.get().getProvinceNumbers())
		{
			valid_vic2_province_numbers.insert(province_number);
		}
	}

	return valid_vic2_province_numbers;
}


std::set<std::vector<int>> determineVic2PossiblePaths(const std::set<int>& validVic2ProvinceNumbers,
	 const std::map<int, std::shared_ptr<Vic2::Province>>& Vic2Provinces,
	 const Maps::MapData& Vic2MapData)
{
	std::set<std::vector<int>> vic2PossiblePaths;
	for (const auto& vic2ProvinceNum: validVic2ProvinceNumbers)
	{
		const auto provinceItr = Vic2Provinces.find(vic2ProvinceNum);
		if (provinceItr == Vic2Provinces.end())
		{
			continue;
		}
		const auto& vic2Province = provinceItr->second;

		if (!vic2Province->isLandProvince())
		{
			continue;
		}
		std::set handledProvinces{vic2ProvinceNum};

		std::set<std::vector<int>> potentialNewVic2PossiblePaths;

		std::priority_queue<std::vector<int>> newPaths;
		newPaths.push({vic2ProvinceNum});

		while (!newPaths.empty())
		{
			auto path = newPaths.top();
			newPaths.pop();

			const auto lastProvince = path[path.size() - 1];
			for (const auto& neighborNumber: Vic2MapData.GetNeighbors(lastProvince))
			{
				if (handledProvinces.contains(neighborNumber))
				{
					continue;
				}
				handledProvinces.insert(neighborNumber);

				const auto neighborItr = Vic2Provinces.find(neighborNumber);
				if (neighborItr == Vic2Provinces.end())
				{
					continue;
				}
				const auto& neighborProvince = neighborItr->second;
				if (!neighborProvince->isLandProvince())
				{
					continue;
				}

				auto newPath = path;
				newPath.push_back(neighborNumber);
				if (validVic2ProvinceNumbers.contains(neighborNumber))
				{
					potentialNewVic2PossiblePaths.insert(newPath);
				}
				else
				{
					newPaths.push(newPath);
				}
			}
		}

		std::vector<int> bestPotentialNewPath;
		long potentialNewPathScore = 0;
		for (const auto& potentialNewVic2PossiblePath: potentialNewVic2PossiblePaths)
		{
			if (potentialNewVic2PossiblePath.size() == 2)
			{
				auto reversedPath = potentialNewVic2PossiblePath;
				std::ranges::reverse(reversedPath);
				if (!vic2PossiblePaths.contains(reversedPath))
				{
					vic2PossiblePaths.insert(potentialNewVic2PossiblePath);
				}
				continue;
			}

			const int potentialLastProvinceNum = potentialNewVic2PossiblePath[potentialNewVic2PossiblePath.size() - 1];
			const auto potentialLastProvinceItr = Vic2Provinces.find(potentialLastProvinceNum);
			if (potentialLastProvinceItr == Vic2Provinces.end())
			{
				continue;
			}
			const int potentialLastProvincePopulation = potentialLastProvinceItr->second->getPopulation();
			if (potentialLastProvincePopulation > potentialNewPathScore)
			{
				bestPotentialNewPath = potentialNewVic2PossiblePath;
				potentialNewPathScore = potentialLastProvincePopulation;
			}
		}
		if (!bestPotentialNewPath.empty())
		{
			auto reversedPath = bestPotentialNewPath;
			std::ranges::reverse(reversedPath);
			if (!vic2PossiblePaths.contains(reversedPath))
			{
				vic2PossiblePaths.insert(bestPotentialNewPath);
			}
		}
	}

	return vic2PossiblePaths;
}


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


std::vector<std::shared_ptr<Vic2::Province>> getVic2ProvincesFromNumbers(const std::vector<int>& vic2PossiblePath,
	 const std::map<int, std::shared_ptr<Vic2::Province>>& Vic2Provinces)
{
	std::vector<std::shared_ptr<Vic2::Province>> vic2Provinces;
	for (const auto& vic2ProvinceNumber: vic2PossiblePath)
	{
		const auto vic2Province = getValidVic2Province(vic2ProvinceNumber, Vic2Provinces);
		if (vic2Province == nullptr)
		{
			continue;
		}
		vic2Provinces.push_back(vic2Province);
	}

	return vic2Provinces;
}


// For the given length two inputs, these are the outputs
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
int getRailwayLevel(const std::vector<int>& vic2PossiblePath,
	 const std::map<int, std::shared_ptr<Vic2::Province>>& Vic2Provinces)
{
	const auto vic2Provinces = getVic2ProvincesFromNumbers(vic2PossiblePath, Vic2Provinces);
	if (vic2Provinces.size() != vic2PossiblePath.size())
	{
		return 0;
	}

	std::vector<int> railLevels;
	for (const auto& vic2Province: vic2Provinces)
	{
		const auto railLevel = vic2Province->getRailLevel();
		if (railLevel == 0)
		{
			return 0;
		}
		railLevels.push_back(vic2Province->getRailLevel());
	}

	int totalRailLevel = std::accumulate(railLevels.begin(), railLevels.end(), 0);
	totalRailLevel -= 2 * static_cast<int>(railLevels.size());
	const int railLevel = totalRailLevel / static_cast<int>(railLevels.size());

	return std::clamp(railLevel, 0, 3);
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
	const auto possibleProvinceOnePoints = HoI4MapData.GetProvincePoints(provinceOne);
	if (!possibleProvinceOnePoints)
	{
		return std::numeric_limits<double>::max();
	}
	const auto provinceOneCentermostPoint = possibleProvinceOnePoints->getCentermostPoint();

	const auto possibleProvinceTwoPoints = HoI4MapData.GetProvincePoints(provinceTwo);
	if (!possibleProvinceTwoPoints)
	{
		return std::numeric_limits<double>::max();
	}
	const auto provinceTwoCentermostPoint = possibleProvinceTwoPoints->getCentermostPoint();

	const int deltaX = provinceOneCentermostPoint.first - provinceTwoCentermostPoint.first;
	const int deltaY = provinceOneCentermostPoint.second - provinceTwoCentermostPoint.second;
	return std::sqrt(deltaX * deltaX + deltaY * deltaY);
}


std::optional<HoI4::PossiblePath> FindPath(int startProvince,
	 int endProvince,
	 const std::vector<int>& vic2Provinces,
	 const Mappers::ProvinceMapper& provinceMapper,
	 const Maps::MapData& HoI4MapData,
	 const Maps::ProvinceDefinitions& HoI4ProvinceDefinitions,
	 const HoI4::ImpassableProvinces& impassableProvinces)
{
	std::priority_queue<HoI4::PossiblePath> possibleRailwayPaths;
	std::set reachedProvinces{startProvince};

	const HoI4::PossiblePath startingPath(startProvince);
	possibleRailwayPaths.push(startingPath);

	while (!possibleRailwayPaths.empty() && possibleRailwayPaths.top().GetLastProvince() != endProvince)
	{
		auto possibleRailwayPath = possibleRailwayPaths.top();
		possibleRailwayPaths.pop();

		const auto lastProvince = possibleRailwayPath.GetLastProvince();
		for (const auto& neighborNumber: HoI4MapData.GetNeighbors(lastProvince))
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
			if (impassableProvinces.isProvinceImpassable(neighborNumber))
			{
				continue;
			}
			const auto& vic2NeighborNumbers = provinceMapper.getHoI4ToVic2ProvinceMapping(neighborNumber);
			bool neighborIsValid = false;
			for (const auto& vic2NeighborNumber: vic2NeighborNumbers)
			{
				for (const auto& vic2Province: vic2Provinces)
				{
					if (vic2NeighborNumber == vic2Province)
					{
						neighborIsValid = true;
						break;
					}
				}
			}
			if (!neighborIsValid)
			{
				continue;
			}

			auto newPossibleRailwayPath = possibleRailwayPath;
			newPossibleRailwayPath.AddProvince(neighborNumber,
				 getCostForTerrainType(HoI4ProvinceDefinitions.getTerrainType(neighborNumber)) *
					  getDistanceBetweenProvinces(neighborNumber, lastProvince, HoI4MapData));
			possibleRailwayPaths.push(newPossibleRailwayPath);
		}
	}

	if (possibleRailwayPaths.empty())
	{
		return std::nullopt;
	}
	return possibleRailwayPaths.top();
}

} // namespace



HoI4::Railways::Railways(const std::map<int, std::shared_ptr<Vic2::Province>>& vic2_provinces,
	 const std::vector<std::reference_wrapper<const Vic2::State>>& vic2_states,
	 const Maps::MapData& vic2_map_data,
	 const Mappers::ProvinceMapper& province_mapper,
	 const Maps::MapData& hoi4_map_data,
	 const Maps::ProvinceDefinitions& hoi4_province_definitions,
	 const ImpassableProvinces& impassable_provinces,
	 const std::map<int, Province>& hoi4_provinces,
	 const std::set<int>& naval_base_locations,
	 const std::map<int, State>& hoi4_states)
{
	Log(LogLevel::Info) << "\tDetermining railways";

	const auto valid_vic2_province_numbers = FindValidVic2ProvinceNumbers(vic2_states);
	const auto vic2_province_paths =
		 determineVic2PossiblePaths(valid_vic2_province_numbers, vic2_provinces, vic2_map_data);

	std::vector<PossiblePath> possible_paths;
	for (const auto& vic2_province_path: vic2_province_paths)
	{
		const int railway_level = getRailwayLevel(vic2_province_path, vic2_provinces);
		if (railway_level < 1)
		{
			continue;
		}

		const auto hoi4_start_province_number = getBestHoI4ProvinceNumber(vic2_province_path[0],
			 province_mapper,
			 impassable_provinces,
			 hoi4_provinces,
			 naval_base_locations);
		const auto hoi4_end_province_number = getBestHoI4ProvinceNumber(vic2_province_path[vic2_province_path.size() - 1],
			 province_mapper,
			 impassable_provinces,
			 hoi4_provinces,
			 naval_base_locations);
		if (!HoI4ProvinceNumbersAreValid(hoi4_start_province_number, hoi4_end_province_number))
		{
			continue;
		}

		if (auto possible_path = FindPath(*hoi4_start_province_number,
				  *hoi4_end_province_number,
				  vic2_province_path,
				  province_mapper,
				  hoi4_map_data,
				  hoi4_province_definitions,
				  impassable_provinces);
			 possible_path)
		{
			possible_path->SetLevel(railway_level);
			possible_paths.push_back(*possible_path);
		}
	}

	std::set<int> initial_endpoints;
	for (const auto& state: hoi4_states | std::views::values)
	{
		if (state.IsCapitalState())
		{
			if (const auto vp_location = state.getVPLocation(); vp_location)
			{
				initial_endpoints.insert(*vp_location);
			}
		}
	}

	std::sort(possible_paths.begin(), possible_paths.end());
	std::ranges::reverse(possible_paths);

	std::vector<PossiblePath> loop_paths;
	while (!possible_paths.empty())
	{
		bool added_railways;
		do
		{
			added_railways = false;
			std::vector<PossiblePath> unused_paths;
			for (const auto& path: possible_paths)
			{
				const auto start_province = path.GetFirstProvince();
				const auto end_province = path.GetLastProvince();
				if (railway_endpoints_.contains(start_province) && railway_endpoints_.contains(end_province))
				{
					loop_paths.push_back(path);
				}
				else if (railway_endpoints_.contains(start_province) || railway_endpoints_.contains(end_province) ||
							initial_endpoints.contains(start_province) || initial_endpoints.contains(end_province))
				{
					Railway railway(path.GetLevel(), path.GetProvinces());
					railways_.push_back(railway);
					railway_endpoints_.insert(path.GetFirstProvince());
					railway_endpoints_.insert(path.GetLastProvince());
					added_railways = true;
				}
				else
				{
					unused_paths.push_back(path);
				}
			}
			possible_paths = unused_paths;
		} while (added_railways);

		if (!possible_paths.empty())
		{
			const auto initial_path = possible_paths.begin();
			Railway initial_railway(initial_path->GetLevel(), initial_path->GetProvinces());
			railways_.push_back(initial_railway);
			railway_endpoints_.insert(initial_path->GetFirstProvince());
			railway_endpoints_.insert(initial_path->GetLastProvince());
			possible_paths.erase(possible_paths.begin());
		}
	}
}
#pragma optimize("",on)