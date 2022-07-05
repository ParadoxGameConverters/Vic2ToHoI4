#include "src/HOI4World/Map/Railways.h"
#include "external/common_items/Log.h"
#include "src/HOI4World/Map/PossiblePath.h"
#include <cmath>
#include <numeric>
#include <queue>
#include <ranges>



using HoI4::Railway;



namespace
{

constexpr double loop_shortcut_requirement = 3.0;


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


bool IsLandProvince(int vic2_province_num, const std::map<int, std::shared_ptr<Vic2::Province>>& vic2_provinces)
{
	const auto province_itr = vic2_provinces.find(vic2_province_num);
	if (province_itr == vic2_provinces.end())
	{
		return false;
	}

	return province_itr->second->isLandProvince();
}


std::vector<std::vector<int>> GetNextPaths(const std::vector<int>& path,
	 const std::set<int>& valid_vic2_province_numbers,
	 const std::map<int, std::shared_ptr<Vic2::Province>>& vic2_provinces,
	 const Maps::MapData& vic2_map_data,
	 std::set<int>& handled_provinces)
{
	std::vector<std::vector<int>> new_paths;

	const auto last_province = path.back();
	for (const auto& neighbor_number: vic2_map_data.GetNeighbors(last_province))
	{
		if (handled_provinces.contains(neighbor_number))
		{
			continue;
		}
		handled_provinces.insert(neighbor_number);

		if (!IsLandProvince(neighbor_number, vic2_provinces))
		{
			continue;
		}

		auto new_path = path;
		new_path.push_back(neighbor_number);

		new_paths.push_back(new_path);
	}

	return new_paths;
}


std::set<std::vector<int>> DetermineAllVic2PossiblePathsForProvince(int vic2_province_num,
	 const std::set<int>& valid_vic2_province_numbers,
	 const std::map<int, std::shared_ptr<Vic2::Province>>& vic2_provinces,
	 const Maps::MapData& vic2_map_data)
{
	std::set handled_provinces{vic2_province_num};
	std::set<std::vector<int>> potential_new_vic2_possible_paths;

	std::priority_queue<std::vector<int>> new_paths;
	new_paths.push({vic2_province_num});

	while (!new_paths.empty())
	{
		auto path = new_paths.top();
		new_paths.pop();

		for (const auto& new_path:
			 GetNextPaths(path, valid_vic2_province_numbers, vic2_provinces, vic2_map_data, handled_provinces))
		{
			if (valid_vic2_province_numbers.contains(new_path.back()))
			{
				potential_new_vic2_possible_paths.insert(new_path);
			}
			else
			{
				new_paths.push(new_path);
			}
		}
	}

	return potential_new_vic2_possible_paths;
}


int GetProvincePopulation(int province_num, const std::map<int, std::shared_ptr<Vic2::Province>>& vic2_provinces)
{
	const auto potential_last_province_itr = vic2_provinces.find(province_num);
	if (potential_last_province_itr == vic2_provinces.end())
	{
		return 0;
	}
	return potential_last_province_itr->second->getPopulation();
}


std::vector<int> DetermineBestPotentialNewPath(const std::set<std::vector<int>>& potential_new_vic2_possible_paths,
	 const std::map<int, std::shared_ptr<Vic2::Province>>& vic2_provinces,
	 std::set<std::vector<int>>& vic2_possible_paths)
{
	std::vector<int> best_potential_new_path;
	int32_t potential_new_path_score = 0;

	for (const auto& potential_new_vic2_possible_path: potential_new_vic2_possible_paths)
	{
		if (potential_new_vic2_possible_path.size() == 2)
		{
			auto reversed_path = potential_new_vic2_possible_path;
			std::ranges::reverse(reversed_path);
			if (!vic2_possible_paths.contains(reversed_path))
			{
				vic2_possible_paths.insert(potential_new_vic2_possible_path);
			}
			continue;
		}

		const int potential_last_province_num = potential_new_vic2_possible_path.back();
		const int potential_last_province_population = GetProvincePopulation(potential_last_province_num, vic2_provinces);
		if (potential_last_province_population > potential_new_path_score)
		{
			best_potential_new_path = potential_new_vic2_possible_path;
			potential_new_path_score = potential_last_province_population;
		}
	}

	return best_potential_new_path;
}


std::set<std::vector<int>> DetermineVic2PossiblePaths(const std::set<int>& valid_vic2_province_numbers,
	 const std::map<int, std::shared_ptr<Vic2::Province>>& vic2_provinces,
	 const Maps::MapData& vic2_map_data)
{
	std::set<std::vector<int>> vic2_possible_paths;

	for (const auto& vic2_province_num: valid_vic2_province_numbers)
	{
		if (!IsLandProvince(vic2_province_num, vic2_provinces))
		{
			continue;
		}

		const auto potential_new_vic2_possible_paths = DetermineAllVic2PossiblePathsForProvince(vic2_province_num,
			 valid_vic2_province_numbers,
			 vic2_provinces,
			 vic2_map_data);

		const auto best_potential_new_path =
			 DetermineBestPotentialNewPath(potential_new_vic2_possible_paths, vic2_provinces, vic2_possible_paths);
		if (!best_potential_new_path.empty())
		{
			auto reversedPath = best_potential_new_path;
			std::ranges::reverse(reversedPath);
			if (!vic2_possible_paths.contains(reversedPath))
			{
				vic2_possible_paths.insert(best_potential_new_path);
			}
		}
	}

	return vic2_possible_paths;
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
	 const std::set<int>& navalBaseLocations,
	 const std::set<int>& state_capitals)
{
	const auto& HoI4ProvinceNumbers = provinceMapper.getVic2ToHoI4ProvinceMapping(Vic2ProvinceNum);
	if (HoI4ProvinceNumbers.empty())
	{
		return std::nullopt;
	}

	// prefer naval bases
	if (!state_capitals.contains((Vic2ProvinceNum)))
	{
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


double DeterminePathCost(const Maps::ProvinceDefinitions& hoi4_province_definitions,
	 int neighbor_number,
	 int last_province,
	 const std::map<int, std::string>& provinces_to_owners_map,
	 const Maps::MapData& hoi4_map_data)
{
	return getCostForTerrainType(hoi4_province_definitions.getTerrainType(neighbor_number)) *
			 getDistanceBetweenProvinces(neighbor_number, last_province, hoi4_map_data);
}


std::optional<HoI4::PossiblePath> FindPath(int startProvince,
	 int endProvince,
	 const std::vector<int>& vic2Provinces,
	 const Mappers::ProvinceMapper& provinceMapper,
	 const Maps::MapData& HoI4MapData,
	 const Maps::ProvinceDefinitions& HoI4ProvinceDefinitions,
	 const HoI4::ImpassableProvinces& impassableProvinces,
	 const std::map<int, std::string>& provinces_to_owners_map)
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
				 DeterminePathCost(HoI4ProvinceDefinitions,
					  neighborNumber,
					  lastProvince,
					  provinces_to_owners_map,
					  HoI4MapData));
			possibleRailwayPaths.push(newPossibleRailwayPath);
		}
	}

	if (possibleRailwayPaths.empty())
	{
		return std::nullopt;
	}
	return possibleRailwayPaths.top();
}


int GetBestStartingPoint(int capital,
	 const std::vector<HoI4::PossiblePath>& possible_paths,
	 const std::map<int, HoI4::State>& states)
{
	// record possible endpoints
	std::set<int> possible_endpoints;
	for (const auto& possible_path: possible_paths)
	{
		possible_endpoints.insert(possible_path.GetFirstProvince());
		possible_endpoints.insert(possible_path.GetLastProvince());
	}

	// capital has top priority
	if (possible_endpoints.contains(capital))
	{
		return capital;
	}

	// return highest value vp
	int highest_vp_value = -1;
	std::optional<int> best_vp_location;
	for (const auto& state: states | std::views::values)
	{
		const auto vp_location = state.getVPLocation();
		if (!vp_location)
		{
			continue;
		}
		if (!possible_endpoints.contains(*vp_location))
		{
			continue;
		}

		const int vp_value = state.getVpValue();
		if (vp_value > highest_vp_value)
		{
			highest_vp_value = vp_value;
			best_vp_location = vp_location;
		}
	}
	if (best_vp_location)
	{
		return *best_vp_location;
	}

	// return just any endpoint
	return *possible_endpoints.begin();
}


bool EndpointIsRemovable(int endpoint, const std::set<int>& naval_locations, const std::set<int>& vp_locations)
{
	return !naval_locations.contains(endpoint) && !vp_locations.contains(endpoint);
}

} // namespace


struct TreePath
{
	int endpoint;
	double cost;
	// higher is prioritized where we want lower to be, so reverse the meaning of less than
	[[nodiscard]] bool operator<(const TreePath& rhs) const { return cost > rhs.cost; }
};


HoI4::Railways::Railways(const std::map<int, std::shared_ptr<Vic2::Province>>& vic2_provinces,
	 const std::vector<std::reference_wrapper<const Vic2::State>>& vic2_states,
	 const Maps::MapData& vic2_map_data,
	 const Mappers::ProvinceMapper& province_mapper,
	 const Maps::MapData& hoi4_map_data,
	 const Maps::ProvinceDefinitions& hoi4_province_definitions,
	 const ImpassableProvinces& impassable_provinces,
	 const std::map<int, Province>& hoi4_provinces,
	 const std::set<int>& naval_base_locations,
	 const HoI4::States& hoi4_states)
{
	Log(LogLevel::Info) << "\tDetermining railways";

	const auto valid_vic2_province_numbers = FindValidVic2ProvinceNumbers(vic2_states);
	std::set<int> vic2_state_capitals;
	for (const auto& state: vic2_states)
	{
		if (auto state_capital = state.get().getCapitalProvince(); state_capital)
		{
			vic2_state_capitals.insert(*state_capital);
		}
	}
	const auto vic2_province_paths =
		 DetermineVic2PossiblePaths(valid_vic2_province_numbers, vic2_provinces, vic2_map_data);

	std::map<int, std::string> provinces_to_owners_map;
	for (const auto& state: hoi4_states.getStates() | std::views::values)
	{
		const auto& owner = state.getOwner();
		for (const auto& province: state.getProvinces())
		{
			provinces_to_owners_map.emplace(province, owner);
		}
	}

	std::map<std::string, std::vector<PossiblePath>> possible_paths_by_owner;
	std::vector<PossiblePath> border_crossings;
	for (const auto& vic2_province_path: vic2_province_paths)
	{
		const int railway_level = getRailwayLevel(vic2_province_path, vic2_provinces);
		if (railway_level < 1)
		{
			continue;
		}

		int vic2_start_province_number = vic2_province_path[0];
		const auto hoi4_start_province_number = getBestHoI4ProvinceNumber(vic2_start_province_number,
			 province_mapper,
			 impassable_provinces,
			 hoi4_provinces,
			 naval_base_locations,
			 vic2_state_capitals);
		int vic2_end_province_number = vic2_province_path[vic2_province_path.size() - 1];
		const auto hoi4_end_province_number = getBestHoI4ProvinceNumber(vic2_end_province_number,
			 province_mapper,
			 impassable_provinces,
			 hoi4_provinces,
			 naval_base_locations,
			 vic2_state_capitals);
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
				  impassable_provinces,
				  provinces_to_owners_map);
			 possible_path)
		{
			possible_path->SetLevel(railway_level);

			std::string last_province_owner;
			if (const auto& owner = provinces_to_owners_map.find(*hoi4_start_province_number);
				 owner != provinces_to_owners_map.end())
			{
				last_province_owner = owner->second;
			}
			std::string neighbor_owner;
			if (const auto& owner = provinces_to_owners_map.find(*hoi4_end_province_number);
				 owner != provinces_to_owners_map.end())
			{
				neighbor_owner = owner->second;
			}
			if (last_province_owner == neighbor_owner)
			{
				auto possible_paths_owner = possible_paths_by_owner.find(last_province_owner);
				if (possible_paths_owner == possible_paths_by_owner.end())
				{
					possible_paths_by_owner.emplace(std::make_pair(last_province_owner, std::vector{*possible_path}));
				}
				else
				{
					possible_paths_owner->second.push_back(*possible_path);
				}
			}
			else
			{
				border_crossings.push_back(*possible_path);
			}
		}

		const auto hoi4_alternate_start_province_number = getBestHoI4ProvinceNumber(vic2_start_province_number,
			 province_mapper,
			 impassable_provinces,
			 hoi4_provinces,
			 naval_base_locations,
			 {});
		if (hoi4_alternate_start_province_number != hoi4_start_province_number)
		{
			if (auto possible_path = FindPath(*hoi4_start_province_number,
					  *hoi4_alternate_start_province_number,
					  vic2_province_path,
					  province_mapper,
					  hoi4_map_data,
					  hoi4_province_definitions,
					  impassable_provinces,
					  provinces_to_owners_map);
				 possible_path)
			{
				possible_path->SetLevel(railway_level);

				std::string last_province_owner;
				if (const auto& owner = provinces_to_owners_map.find(*hoi4_start_province_number);
					 owner != provinces_to_owners_map.end())
				{
					last_province_owner = owner->second;
				}
				std::string neighbor_owner;
				if (const auto& owner = provinces_to_owners_map.find(*hoi4_alternate_start_province_number);
					 owner != provinces_to_owners_map.end())
				{
					neighbor_owner = owner->second;
				}
				if (last_province_owner == neighbor_owner)
				{
					auto possible_paths_owner = possible_paths_by_owner.find(last_province_owner);
					if (possible_paths_owner == possible_paths_by_owner.end())
					{
						possible_paths_by_owner.emplace(std::make_pair(last_province_owner, std::vector{*possible_path}));
					}
					else
					{
						possible_paths_owner->second.push_back(*possible_path);
					}
				}
				else
				{
					border_crossings.push_back(*possible_path);
				}
			}
		}

		const auto hoi4_alternate_end_province_number = getBestHoI4ProvinceNumber(vic2_end_province_number,
			 province_mapper,
			 impassable_provinces,
			 hoi4_provinces,
			 naval_base_locations,
			 {});
		if (hoi4_alternate_end_province_number != hoi4_end_province_number)
		{
			if (auto possible_path = FindPath(*hoi4_end_province_number,
					  *hoi4_alternate_end_province_number,
					  vic2_province_path,
					  province_mapper,
					  hoi4_map_data,
					  hoi4_province_definitions,
					  impassable_provinces,
					  provinces_to_owners_map);
				 possible_path)
			{
				possible_path->SetLevel(railway_level);

				std::string last_province_owner;
				if (const auto& owner = provinces_to_owners_map.find(*hoi4_end_province_number);
					 owner != provinces_to_owners_map.end())
				{
					last_province_owner = owner->second;
				}
				std::string neighbor_owner;
				if (const auto& owner = provinces_to_owners_map.find(*hoi4_alternate_end_province_number);
					 owner != provinces_to_owners_map.end())
				{
					neighbor_owner = owner->second;
				}
				if (last_province_owner == neighbor_owner)
				{
					auto possible_paths_owner = possible_paths_by_owner.find(last_province_owner);
					if (possible_paths_owner == possible_paths_by_owner.end())
					{
						possible_paths_by_owner.emplace(std::make_pair(last_province_owner, std::vector{*possible_path}));
					}
					else
					{
						possible_paths_owner->second.push_back(*possible_path);
					}
				}
				else
				{
					border_crossings.push_back(*possible_path);
				}
			}
		}
	}

	std::set<int> naval_locations;
	for (const auto& state: hoi4_states.getStates() | std::views::values)
	{
		if (const auto possible_naval_location = state.getMainNavalLocation(); possible_naval_location)
		{
			naval_locations.insert(*possible_naval_location);
		}
	}

	std::map<std::string, int> capitals;
	for (const auto& state: hoi4_states.getStates() | std::views::values)
	{
		if (state.IsCapitalState())
		{
			if (const auto vp_location = state.getVPLocation(); vp_location)
			{
				capitals.emplace(state.getOwner(), *vp_location);
			}
		}
	}

	std::vector<PossiblePath> loop_paths;
	std::vector<PossiblePath> spanning_paths;
	for (const auto& [owner, capital]: capitals)
	{
		auto possible_paths_itr = possible_paths_by_owner.find(owner);
		if (possible_paths_itr == possible_paths_by_owner.end())
		{
			Log(LogLevel::Warning) << "No possible paths for " << owner;
			continue;
		}

		auto possible_paths = possible_paths_itr->second;

		struct point
		{
			int province;
			double cost;
			PossiblePath in_connection;

			[[nodiscard]] bool operator<(const point& rhs) const { return cost > rhs.cost; }
		};

		while (!possible_paths.empty())
		{
			int starting_point = GetBestStartingPoint(capital, possible_paths, hoi4_states.getStates());

			point capital_point{.province = starting_point, .cost = 0.0, .in_connection = PossiblePath(starting_point)};
			std::priority_queue<point> points_to_try;
			points_to_try.push(capital_point);

			std::set<int> really_done_points;
			while (!points_to_try.empty())
			{
				auto point_to_try = points_to_try.top();
				points_to_try.pop();
				if (really_done_points.contains(point_to_try.province))
				{
					continue;
				}

				if (point_to_try.in_connection.GetProvinces().size() > 1)
				{
					spanning_paths.push_back(point_to_try.in_connection);
				}
				really_done_points.insert(point_to_try.province);
				for (const auto& possible_path: possible_paths)
				{
					if (possible_path.GetFirstProvince() == point_to_try.province &&
						 !really_done_points.contains(possible_path.GetLastProvince()))
					{
						point new_point = {.province = possible_path.GetLastProvince(),
							 .cost = point_to_try.cost + possible_path.GetCost(),
							 .in_connection = possible_path};
						points_to_try.emplace(new_point);
					}
					else if (possible_path.GetLastProvince() == point_to_try.province &&
								!really_done_points.contains(possible_path.GetFirstProvince()))
					{
						point new_point = {.province = possible_path.GetFirstProvince(),
							 .cost = point_to_try.cost + possible_path.GetCost(),
							 .in_connection = possible_path};
						points_to_try.emplace(new_point);
					}
				}
			}

			std::vector<PossiblePath> remaining_possible_paths;
			for (auto& path: possible_paths)
			{
				if (really_done_points.contains(path.GetFirstProvince()) &&
					 really_done_points.contains(path.GetLastProvince()))
				{
					loop_paths.push_back(path);
				}
				else
				{
					remaining_possible_paths.push_back(path);
				}
			}
			possible_paths = remaining_possible_paths;
		}
	}

	std::vector<PossiblePath> extra_paths;
	for (const auto& path: border_crossings)
	{
		extra_paths.push_back(path);
	}
	for (const auto& path: loop_paths)
	{
		extra_paths.push_back(path);
	}
	std::sort(extra_paths.begin(), extra_paths.end());
	std::ranges::reverse(extra_paths);

	for (const auto& extra_path: extra_paths)
	{
		double without_cost = std::numeric_limits<double>::max();

		std::set<int> reached_points;
		std::priority_queue<TreePath> points_to_try;
		TreePath initial_path;
		initial_path.endpoint = extra_path.GetFirstProvince();
		points_to_try.push(initial_path);
		while (!points_to_try.empty())
		{
			const auto point_to_try = points_to_try.top();
			points_to_try.pop();
			if (point_to_try.endpoint == extra_path.GetLastProvince())
			{
				without_cost = point_to_try.cost;
				break;
			}

			for (const auto& path: spanning_paths)
			{
				if (path.GetFirstProvince() == point_to_try.endpoint && !reached_points.contains(path.GetLastProvince()))
				{
					TreePath new_path;
					new_path.endpoint = path.GetLastProvince();
					new_path.cost = point_to_try.cost + path.GetCost();
					points_to_try.push(new_path);
					reached_points.insert(path.GetLastProvince());
				}
				if (path.GetLastProvince() == point_to_try.endpoint && !reached_points.contains(path.GetFirstProvince()))
				{
					TreePath new_path;
					new_path.endpoint = path.GetFirstProvince();
					new_path.cost = point_to_try.cost + path.GetCost();
					points_to_try.push(new_path);
					reached_points.insert(path.GetFirstProvince());
				}
			}
		}

		if (without_cost / loop_shortcut_requirement > extra_path.GetCost())
		{
			spanning_paths.push_back(extra_path);
		}
	}

	std::map<int, std::vector<PossiblePath>> endpoints_to_paths;
	for (const auto& path: spanning_paths)
	{
		if (auto [iterator, success] = endpoints_to_paths.emplace(path.GetFirstProvince(), std::vector{path}); !success)
		{
			iterator->second.push_back(path);
		}
		if (auto [iterator, success] = endpoints_to_paths.emplace(path.GetLastProvince(), std::vector{path}); !success)
		{
			iterator->second.push_back(path);
		}
	}

	for (auto& path: spanning_paths)
	{
		const auto provinces = path.GetProvinces();
		for (unsigned int i = 0; i < provinces.size(); ++i)
		{
			if (provinces[i] == path.GetFirstProvince())
			{
				continue;
			}
			if (provinces[i] == path.GetLastProvince())
			{
				continue;
			}

			if (const auto& endpoint_to_path = endpoints_to_paths.find(provinces[i]);
				 endpoint_to_path != endpoints_to_paths.end())
			{
				if (provinces[0] == endpoint_to_path->second[0].GetFirstProvince() ||
					 provinces[0] == endpoint_to_path->second[0].GetLastProvince())
				{
					std::vector<int> new_provinces;
					for (unsigned int j = i; j < provinces.size(); ++j)
					{
						new_provinces.push_back(provinces[j]);
					}
					path.ReplaceProvinces(new_provinces);
					break;
				}
				if (provinces[provinces.size() - 1] == endpoint_to_path->second[0].GetFirstProvince() ||
					 provinces[provinces.size() - 1] == endpoint_to_path->second[0].GetLastProvince())
				{
					std::vector<int> new_provinces;
					for (unsigned int j = 0; j <= i; ++j)
					{
						new_provinces.push_back(provinces[j]);
					}
					path.ReplaceProvinces(new_provinces);
					break;
				}
			}
		}
	}

	std::set<int> vp_locations;
	for (const auto& state: hoi4_states.getStates() | std::views::values)
	{
		if (auto vp_location = state.getVPLocation(); vp_location)
		{
			vp_locations.insert(*vp_location);
		}
	}

	bool paths_removed = false;
	std::vector<PossiblePath> trimmed_paths = spanning_paths;
	do
	{
		paths_removed = false;

		std::map<int, std::vector<PossiblePath>> endpoints_to_paths;
		for (const auto& path: trimmed_paths)
		{
			if (auto [iterator, success] = endpoints_to_paths.emplace(path.GetFirstProvince(), std::vector{path});
				 !success)
			{
				bool path_already_stored = false;
				for (const auto& stored_path: iterator->second)
				{
					if (stored_path == path)
					{
						path_already_stored = true;
						break;
					}
				}
				if (!path_already_stored)
				{
					iterator->second.push_back(path);
				}
			}
			if (auto [iterator, success] = endpoints_to_paths.emplace(path.GetLastProvince(), std::vector{path}); !success)
			{
				bool path_already_stored = false;
				for (const auto& stored_path: iterator->second)
				{
					if (stored_path == path)
					{
						path_already_stored = true;
						break;
					}
				}
				if (!path_already_stored)
				{
					iterator->second.push_back(path);
				}
			}
		}

		trimmed_paths.clear();
		for (const auto& [endpoint, paths]: endpoints_to_paths)
		{
			if (paths.size() == 1 && EndpointIsRemovable(endpoint, naval_locations, vp_locations))
			{
				paths_removed = true;
				continue;
			}
			for (const auto& path: paths)
			{
				if (path.GetFirstProvince() == endpoint)
				{
					const auto connecting_paths = endpoints_to_paths.find(path.GetLastProvince());
					if (connecting_paths == endpoints_to_paths.end())
					{
						paths_removed = true;
						continue;
					}
					if (connecting_paths->second.size() == 1 &&
						 EndpointIsRemovable(path.GetLastProvince(), naval_locations, vp_locations))
					{
						paths_removed = true;
						continue;
					}
					trimmed_paths.push_back(path);
				}
			}
		}
	} while (paths_removed);

	endpoints_to_paths.clear();
	for (const auto& path: trimmed_paths)
	{
		if (auto [iterator, success] = endpoints_to_paths.emplace(path.GetFirstProvince(), std::vector{path}); !success)
		{
			bool path_already_stored = false;
			for (const auto& stored_path: iterator->second)
			{
				if (stored_path == path)
				{
					path_already_stored = true;
					break;
				}
			}
			if (!path_already_stored)
			{
				iterator->second.push_back(path);
			}
		}
		if (auto [iterator, success] = endpoints_to_paths.emplace(path.GetLastProvince(), std::vector{path}); !success)
		{
			bool path_already_stored = false;
			for (const auto& stored_path: iterator->second)
			{
				if (stored_path == path)
				{
					path_already_stored = true;
					break;
				}
			}
			if (!path_already_stored)
			{
				iterator->second.push_back(path);
			}
		}
	}

	trimmed_paths.clear();
	std::set<int> removed_endpoints;
	for (const auto& [endpoint, paths]: endpoints_to_paths)
	{
		if (paths.size() == 2 && EndpointIsRemovable(endpoint, naval_locations, vp_locations) &&
			 paths[0].GetProvinces().size() + paths[1].GetProvinces().size() < 11)
		{
			removed_endpoints.insert(endpoint);
			PossiblePath merged_path(endpoint);


			std::vector<int> merged_provinces;
			if (paths[0].GetFirstProvince() == endpoint)
			{
				for (auto province: paths[0].GetProvinces() | std::views::reverse)
				{
					merged_provinces.push_back(province);
				}
			}
			else
			{
				for (auto province: paths[0].GetProvinces())
				{
					merged_provinces.push_back(province);
				}
			}
			merged_provinces.pop_back();
			if (paths[1].GetFirstProvince() == endpoint)
			{
				for (auto province: paths[1].GetProvinces())
				{
					merged_provinces.push_back(province);
				}
			}
			else
			{
				for (auto province: paths[1].GetProvinces() | std::views::reverse)
				{
					merged_provinces.push_back(province);
				}
			}
			merged_path.ReplaceProvinces(merged_provinces);
			merged_path.SetLevel(std::min(paths[0].GetLevel(), paths[1].GetLevel()));

			trimmed_paths.push_back(merged_path);

			continue;
		}
	}
	for (const auto& [endpoint, paths]: endpoints_to_paths)
	{
		if (removed_endpoints.contains(endpoint))
		{
			continue;
		}
		for (const auto& path: paths)
		{
			if (endpoint == path.GetFirstProvince() && !removed_endpoints.contains(path.GetFirstProvince()) &&
				 !removed_endpoints.contains(path.GetLastProvince()))
			{
				trimmed_paths.push_back(path);
			}
		}
	}

	// todo: possibly avoid placing supply depots on naval bases
	for (const auto& path: trimmed_paths)
	{
		Railway railway(path.GetLevel(), path.GetProvinces());
		railways_.push_back(railway);
		railway_endpoints_.insert(path.GetFirstProvince());
		railway_endpoints_.insert(path.GetLastProvince());
	}
}