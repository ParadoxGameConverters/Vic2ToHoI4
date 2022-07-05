#include "src/HOI4World/Map/Railways.h"
#include "external/common_items/Log.h"
#include "src/HOI4World/Map/PathPoint.h"
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

		std::vector<int> new_path = path;
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
		std::vector<int> path = new_paths.top();
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
			std::vector<int> reversed_path = potential_new_vic2_possible_path;
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


std::set<int> GetVic2StateCapitals(const std::vector<std::reference_wrapper<const Vic2::State>>& vic2_states)
{
	std::set<int> vic2_state_capitals;
	for (const auto& state: vic2_states)
	{
		if (auto state_capital = state.get().getCapitalProvince(); state_capital)
		{
			vic2_state_capitals.insert(*state_capital);
		}
	}

	return vic2_state_capitals;
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

		if (const auto best_potential_new_path =
				  DetermineBestPotentialNewPath(potential_new_vic2_possible_paths, vic2_provinces, vic2_possible_paths);
			 !best_potential_new_path.empty())
		{
			std::vector<int> reversedPath = best_potential_new_path;
			std::ranges::reverse(reversedPath);
			if (!vic2_possible_paths.contains(reversedPath))
			{
				vic2_possible_paths.insert(best_potential_new_path);
			}
		}
	}

	return vic2_possible_paths;
}


std::map<int, std::string> MapHoi4ProvincesToOwners(const HoI4::States& hoi4_states)
{
	std::map<int, std::string> provinces_to_owners_map;
	for (const auto& state: hoi4_states.getStates() | std::views::values)
	{
		const auto& owner = state.getOwner();
		for (const auto& province: state.getProvinces())
		{
			provinces_to_owners_map.emplace(province, owner);
		}
	}

	return provinces_to_owners_map;
}


std::shared_ptr<Vic2::Province> GetValidVic2Province(int province_num,
	 const std::map<int, std::shared_ptr<Vic2::Province>>& vic2_provinces)
{
	const auto& itr = vic2_provinces.find(province_num);
	if (itr == vic2_provinces.end())
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


std::vector<std::shared_ptr<Vic2::Province>> GetVic2PathProvincesFromNumbers(const std::vector<int>& vic2_possible_path,
	 const std::map<int, std::shared_ptr<Vic2::Province>>& vic2_provinces)
{
	std::vector<std::shared_ptr<Vic2::Province>> vic2_path_provinces;
	for (const auto& vic2_province_number: vic2_possible_path)
	{
		const auto vic2_province = GetValidVic2Province(vic2_province_number, vic2_provinces);
		if (vic2_province == nullptr)
		{
			continue;
		}
		vic2_path_provinces.push_back(vic2_province);
	}

	return vic2_path_provinces;
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
int GetRailwayLevel(const std::vector<int>& vic2_possible_path,
	 const std::map<int, std::shared_ptr<Vic2::Province>>& vic2_provinces)
{
	const auto vic2_path_provinces = GetVic2PathProvincesFromNumbers(vic2_possible_path, vic2_provinces);
	if (vic2_path_provinces.size() != vic2_possible_path.size())
	{
		return 0;
	}

	std::vector<int> rail_levels;
	for (const auto& vic2_province: vic2_path_provinces)
	{
		const auto rail_level = vic2_province->getRailLevel();
		if (rail_level == 0)
		{
			return 0;
		}
		rail_levels.push_back(vic2_province->getRailLevel());
	}

	int total_rail_level = std::accumulate(rail_levels.begin(), rail_levels.end(), 0);
	total_rail_level -= 2 * static_cast<int>(rail_levels.size());
	const int rail_level = total_rail_level / static_cast<int>(rail_levels.size());

	return std::clamp(rail_level, 0, 3);
}


bool IsValidRailwayEndpoint(int province_number,
	 const std::map<int, HoI4::Province>& hoi4_provinces,
	 const HoI4::ImpassableProvinces& impassable_provinces)
{
	const auto province = hoi4_provinces.find(province_number);
	if (province == hoi4_provinces.end())
	{
		return false;
	}
	if (!province->second.isLandProvince())
	{
		return false;
	}
	if (impassable_provinces.isProvinceImpassable(province_number))
	{
		return false;
	}

	return true;
}


std::optional<int> GetBestHoI4ProvinceNumber(const int vic2_province_num,
	 const Mappers::ProvinceMapper& province_mapper,
	 const HoI4::ImpassableProvinces& impassable_provinces,
	 const std::map<int, HoI4::Province>& hoi4_provinces,
	 const std::set<int>& naval_base_locations,
	 const std::set<int>& state_capitals)
{
	const auto& hoi4_province_numbers = province_mapper.getVic2ToHoI4ProvinceMapping(vic2_province_num);
	if (hoi4_province_numbers.empty())
	{
		return std::nullopt;
	}

	// prefer naval bases unless this is a state capital province
	if (!state_capitals.contains((vic2_province_num)))
	{
		for (const auto province_number: hoi4_province_numbers)
		{
			if (!naval_base_locations.contains(province_number))
			{
				continue;
			}
			if (!IsValidRailwayEndpoint(province_number, hoi4_provinces, impassable_provinces))
			{
				continue;
			}

			return province_number;
		}
	}

	// find an appropriate province in priority of the mapping
	for (const auto province_number: hoi4_province_numbers)
	{
		if (!IsValidRailwayEndpoint(province_number, hoi4_provinces, impassable_provinces))
		{
			continue;
		}

		return province_number;
	}

	return std::nullopt;
}


bool Hoi4ProvinceNumbersAreValid(std::optional<int> first_number, std::optional<int> second_number)
{
	return first_number && second_number && *first_number != *second_number;
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
int GetCostForTerrainType(const std::string& terrain_type)
{
	if (terrain_type == "urban")
	{
		return urban_cost;
	}
	if (terrain_type == "plains")
	{
		return plains_cost;
	}
	if (terrain_type == "forest")
	{
		return forest_cost;
	}
	if (terrain_type == "hills")
	{
		return hills_cost;
	}
	if (terrain_type == "desert")
	{
		return desert_cost;
	}
	if (terrain_type == "marsh")
	{
		return marsh_cost;
	}
	if (terrain_type == "jungle")
	{
		return jungle_cost;
	}
	if (terrain_type == "mountain")
	{
		return mountain_cost;
	}

	Log(LogLevel::Warning) << "Unhandled terrain type " << terrain_type << ". Please inform the converter team.";
	return unhandled_cost;
}


std::optional<Maps::Point> GetCentermostPoint(int province, const Maps::MapData& hoi4_map_data)
{
	const auto possible_province_points = hoi4_map_data.GetProvincePoints(province);
	if (!possible_province_points)
	{
		return std::nullopt;
	}
	return possible_province_points->getCentermostPoint();
}


double GetDistanceBetweenProvinces(int province_one, int province_two, const Maps::MapData& hoi4_map_data)
{
	const auto province_one_centermost_point = GetCentermostPoint(province_one, hoi4_map_data);
	if (!province_one_centermost_point)
	{
		return std::numeric_limits<double>::max();
	}

	const auto province_two_centermost_point = GetCentermostPoint(province_two, hoi4_map_data);
	if (!province_two_centermost_point)
	{
		return std::numeric_limits<double>::max();
	}

	const int delta_x = province_one_centermost_point->first - province_two_centermost_point->first;
	const int delta_y = province_one_centermost_point->second - province_two_centermost_point->second;
	return std::sqrt(delta_x * delta_x + delta_y * delta_y);
}


double DeterminePathCost(const Maps::ProvinceDefinitions& hoi4_province_definitions,
	 int neighbor_number,
	 int last_province,
	 const std::map<int, std::string>& provinces_to_owners_map,
	 const Maps::MapData& hoi4_map_data)
{
	return GetCostForTerrainType(hoi4_province_definitions.getTerrainType(neighbor_number)) *
			 GetDistanceBetweenProvinces(neighbor_number, last_province, hoi4_map_data);
}


void FindNextPaths(const HoI4::PossiblePath& possible_railway_path,
	 const Maps::MapData& hoi4_map_data,
	 const Maps::ProvinceDefinitions& hoi4_province_definitions,
	 const HoI4::ImpassableProvinces& impassable_provinces,
	 const Mappers::ProvinceMapper& province_mapper,
	 const std::vector<int>& vic2_provinces,
	 const std::map<int, std::string>& provinces_to_owners_map,
	 std::set<int>& reached_provinces,
	 std::priority_queue<HoI4::PossiblePath>& possible_railway_paths)
{
	const int last_province = possible_railway_path.GetLastProvince();
	for (const auto& neighbor_number: hoi4_map_data.GetNeighbors(last_province))
	{
		if (reached_provinces.contains(neighbor_number))
		{
			continue;
		}
		reached_provinces.insert(neighbor_number);
		if (!hoi4_province_definitions.isLandProvince(neighbor_number))
		{
			continue;
		}
		if (impassable_provinces.isProvinceImpassable(neighbor_number))
		{
			continue;
		}
		const auto& vic2_neighbor_numbers = province_mapper.getHoI4ToVic2ProvinceMapping(neighbor_number);
		bool neighbor_is_valid = false;
		for (const auto& vic2_neighbor_number: vic2_neighbor_numbers)
		{
			for (const auto& vic2_province: vic2_provinces)
			{
				if (vic2_neighbor_number == vic2_province)
				{
					neighbor_is_valid = true;
					break;
				}
			}
		}
		if (!neighbor_is_valid)
		{
			continue;
		}

		HoI4::PossiblePath new_possible_railway_path = possible_railway_path;
		new_possible_railway_path.AddProvince(neighbor_number,
			 DeterminePathCost(hoi4_province_definitions,
				  neighbor_number,
				  last_province,
				  provinces_to_owners_map,
				  hoi4_map_data));
		possible_railway_paths.push(new_possible_railway_path);
	}
}


std::optional<HoI4::PossiblePath> FindPath(const int start_province,
	 const int end_province,
	 const std::vector<int>& vic2_provinces,
	 const Mappers::ProvinceMapper& province_mapper,
	 const Maps::MapData& hoi4_map_data,
	 const Maps::ProvinceDefinitions& hoi4_province_definitions,
	 const HoI4::ImpassableProvinces& impassable_provinces,
	 const std::map<int, std::string>& hoi4_provinces_to_owners_map)
{
	std::priority_queue<HoI4::PossiblePath> possible_railway_paths;
	std::set reached_provinces{start_province};

	const HoI4::PossiblePath startingPath(start_province);
	possible_railway_paths.push(startingPath);

	while (!possible_railway_paths.empty() && possible_railway_paths.top().GetLastProvince() != end_province)
	{
		HoI4::PossiblePath possible_railway_path = possible_railway_paths.top();
		possible_railway_paths.pop();

		FindNextPaths(possible_railway_path,
			 hoi4_map_data,
			 hoi4_province_definitions,
			 impassable_provinces,
			 province_mapper,
			 vic2_provinces,
			 hoi4_provinces_to_owners_map,
			 reached_provinces,
			 possible_railway_paths);
	}

	if (possible_railway_paths.empty())
	{
		return std::nullopt;
	}
	return possible_railway_paths.top();
}


void BuildAndClassifyPath(const int start_province,
	 const int end_province,
	 const int railway_level,
	 const std::vector<int>& vic2_provinces,
	 const Mappers::ProvinceMapper& province_mapper,
	 const Maps::MapData& hoi4_map_data,
	 const Maps::ProvinceDefinitions& hoi4_province_definitions,
	 const HoI4::ImpassableProvinces& impassable_provinces,
	 const std::map<int, std::string>& hoi4_provinces_to_owners_map,
	 std::map<std::string, std::vector<HoI4::PossiblePath>>& possible_paths_by_owner,
	 std::vector<HoI4::PossiblePath>& border_crossings)
{
	auto possible_path = FindPath(start_province,
		 end_province,
		 vic2_provinces,
		 province_mapper,
		 hoi4_map_data,
		 hoi4_province_definitions,
		 impassable_provinces,
		 hoi4_provinces_to_owners_map);
	if (!possible_path)
	{
		return;
	}

	possible_path->SetLevel(railway_level);

	std::string last_province_owner;
	if (const auto& owner = hoi4_provinces_to_owners_map.find(start_province);
		 owner != hoi4_provinces_to_owners_map.end())
	{
		last_province_owner = owner->second;
	}
	std::string neighbor_owner;
	if (const auto& owner = hoi4_provinces_to_owners_map.find(end_province); owner != hoi4_provinces_to_owners_map.end())
	{
		neighbor_owner = owner->second;
	}
	if (last_province_owner == neighbor_owner)
	{
		if (auto [iterator, success] =
				  possible_paths_by_owner.emplace(std::make_pair(last_province_owner, std::vector{*possible_path}));
			 !success)
		{
			iterator->second.push_back(*possible_path);
		}
	}
	else
	{
		border_crossings.push_back(*possible_path);
	}
}


std::tuple<std::map<std::string, std::vector<HoI4::PossiblePath>>, std::vector<HoI4::PossiblePath>> FindAllHoi4Paths(
	 const std::set<std::vector<int>>& vic2_province_paths,
	 const std::map<int, std::shared_ptr<Vic2::Province>>& vic2_provinces,
	 const Mappers::ProvinceMapper& province_mapper,
	 const HoI4::ImpassableProvinces& impassable_provinces,
	 const std::map<int, HoI4::Province>& hoi4_provinces,
	 const std::set<int>& naval_base_locations,
	 const std::set<int>& vic2_state_capitals,
	 const Maps::MapData& hoi4_map_data,
	 const Maps::ProvinceDefinitions& hoi4_province_definitions,
	 const std::map<int, std::string>& hoi4_provinces_to_owners_map)
{
	std::map<std::string, std::vector<HoI4::PossiblePath>> possible_paths_by_owner;
	std::vector<HoI4::PossiblePath> border_crossings;
	for (const auto& vic2_province_path: vic2_province_paths)
	{
		const int railway_level = GetRailwayLevel(vic2_province_path, vic2_provinces);
		if (railway_level < 1)
		{
			continue;
		}

		const int vic2_start_province_number = vic2_province_path.front();
		const auto hoi4_start_province_number = GetBestHoI4ProvinceNumber(vic2_start_province_number,
			 province_mapper,
			 impassable_provinces,
			 hoi4_provinces,
			 naval_base_locations,
			 vic2_state_capitals);
		const int vic2_end_province_number = vic2_province_path.back();
		const auto hoi4_end_province_number = GetBestHoI4ProvinceNumber(vic2_end_province_number,
			 province_mapper,
			 impassable_provinces,
			 hoi4_provinces,
			 naval_base_locations,
			 vic2_state_capitals);
		if (!Hoi4ProvinceNumbersAreValid(hoi4_start_province_number, hoi4_end_province_number))
		{
			continue;
		}

		BuildAndClassifyPath(*hoi4_start_province_number,
			 *hoi4_end_province_number,
			 railway_level,
			 vic2_province_path,
			 province_mapper,
			 hoi4_map_data,
			 hoi4_province_definitions,
			 impassable_provinces,
			 hoi4_provinces_to_owners_map,
			 possible_paths_by_owner,
			 border_crossings);
		if (const auto hoi4_alternate_start_province_number = GetBestHoI4ProvinceNumber(vic2_start_province_number,
				  province_mapper,
				  impassable_provinces,
				  hoi4_provinces,
				  naval_base_locations,
				  {});
			 hoi4_alternate_start_province_number && *hoi4_alternate_start_province_number != *hoi4_start_province_number)
		{
			BuildAndClassifyPath(*hoi4_start_province_number,
				 *hoi4_alternate_start_province_number,
				 railway_level,
				 vic2_province_path,
				 province_mapper,
				 hoi4_map_data,
				 hoi4_province_definitions,
				 impassable_provinces,
				 hoi4_provinces_to_owners_map,
				 possible_paths_by_owner,
				 border_crossings);
		}

		if (const auto hoi4_alternate_end_province_number = GetBestHoI4ProvinceNumber(vic2_end_province_number,
				  province_mapper,
				  impassable_provinces,
				  hoi4_provinces,
				  naval_base_locations,
				  {});
			 hoi4_alternate_end_province_number && *hoi4_alternate_end_province_number != *hoi4_end_province_number)
		{
			BuildAndClassifyPath(*hoi4_end_province_number,
				 *hoi4_alternate_end_province_number,
				 railway_level,
				 vic2_province_path,
				 province_mapper,
				 hoi4_map_data,
				 hoi4_province_definitions,
				 impassable_provinces,
				 hoi4_provinces_to_owners_map,
				 possible_paths_by_owner,
				 border_crossings);
		}
	}

	return {possible_paths_by_owner, border_crossings};
}


std::set<int> DetermineNavalLocations(const HoI4::States& hoi4_states)
{
	std::set<int> naval_locations;
	for (const auto& state: hoi4_states.getStates() | std::views::values)
	{
		if (const auto possible_naval_location = state.getMainNavalLocation(); possible_naval_location)
		{
			naval_locations.insert(*possible_naval_location);
		}
	}

	return naval_locations;
}


std::map<std::string, int> DetermineHoI4Capitals(const HoI4::States& hoi4_states)
{
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

	return capitals;
}


int GetBestStartingPoint(const int capital,
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


bool EndpointIsRemovable(const int endpoint, const std::set<int>& naval_locations, const std::set<int>& vp_locations)
{
	return !naval_locations.contains(endpoint) && !vp_locations.contains(endpoint);
}


std::vector<HoI4::PossiblePath> LookupOwnersPossiblePaths(const std::string& owner,
	 const std::map<std::string, std::vector<HoI4::PossiblePath>>& possible_paths_by_owner)
{
	const auto possible_paths_itr = possible_paths_by_owner.find(owner);
	if (possible_paths_itr == possible_paths_by_owner.end())
	{
		Log(LogLevel::Warning) << "No possible paths for " << owner;
		return {};
	}

	return possible_paths_itr->second;
}


std::set<int> AddSpanningPaths(const std::vector<HoI4::PossiblePath>& possible_paths,
	 std::priority_queue<HoI4::PathPoint>& points_to_try,
	 std::vector<HoI4::PossiblePath>& spanning_paths)
{
	std::set<int> done_points;
	while (!points_to_try.empty())
	{
		HoI4::PathPoint point_to_try = points_to_try.top();
		points_to_try.pop();
		if (done_points.contains(point_to_try.province))
		{
			continue;
		}

		if (point_to_try.in_connection && point_to_try.in_connection->GetProvinces().size() > 1)
		{
			spanning_paths.push_back(*point_to_try.in_connection);
		}
		done_points.insert(point_to_try.province);
		for (const auto& possible_path: possible_paths)
		{
			if (possible_path.GetFirstProvince() == point_to_try.province &&
				 !done_points.contains(possible_path.GetLastProvince()))
			{
				HoI4::PathPoint new_point = {.province = possible_path.GetLastProvince(),
					 .cost = point_to_try.cost + possible_path.GetCost(),
					 .in_connection = possible_path};
				points_to_try.emplace(new_point);
			}
			else if (possible_path.GetLastProvince() == point_to_try.province &&
						!done_points.contains(possible_path.GetFirstProvince()))
			{
				HoI4::PathPoint new_point = {.province = possible_path.GetFirstProvince(),
					 .cost = point_to_try.cost + possible_path.GetCost(),
					 .in_connection = possible_path};
				points_to_try.emplace(new_point);
			}
		}
	}

	return done_points;
}


std::vector<HoI4::PossiblePath> DetermineLoopPaths(const std::vector<HoI4::PossiblePath>& possible_paths,
	 const std::set<int>& done_points,
	 std::vector<HoI4::PossiblePath>& loop_paths)
{
	std::vector<HoI4::PossiblePath> remaining_possible_paths;
	for (auto& path: possible_paths)
	{
		if (done_points.contains(path.GetFirstProvince()) && done_points.contains(path.GetLastProvince()))
		{
			loop_paths.push_back(path);
		}
		else
		{
			remaining_possible_paths.push_back(path);
		}
	}

	return remaining_possible_paths;
}


std::tuple<std::vector<HoI4::PossiblePath>, std::vector<HoI4::PossiblePath>> ConstructSpanningTree(
	 const std::string& owner,
	 const std::map<std::string, std::vector<HoI4::PossiblePath>>& possible_paths_by_owner,
	 const int capital,
	 const HoI4::States& hoi4_states)
{
	std::vector<HoI4::PossiblePath> loop_paths;
	std::vector<HoI4::PossiblePath> spanning_paths;

	auto possible_paths = LookupOwnersPossiblePaths(owner, possible_paths_by_owner);
	if (possible_paths.empty())
	{
		return {loop_paths, spanning_paths};
	}

	while (!possible_paths.empty())
	{
		int starting_point = GetBestStartingPoint(capital, possible_paths, hoi4_states.getStates());

		HoI4::PathPoint capital_point{.province = starting_point,
			 .cost = 0.0,
			 .in_connection = HoI4::PossiblePath(starting_point)};
		std::priority_queue<HoI4::PathPoint> points_to_try;
		points_to_try.push(capital_point);

		const auto done_points = AddSpanningPaths(possible_paths, points_to_try, spanning_paths);
		possible_paths = DetermineLoopPaths(possible_paths, done_points, loop_paths);
	}

	return {spanning_paths, loop_paths};
}


std::tuple<std::vector<HoI4::PossiblePath>, std::vector<HoI4::PossiblePath>> ConstructSpanningTrees(
	 const std::map<std::string, int>& capitals,
	 const std::map<std::string, std::vector<HoI4::PossiblePath>>& possible_paths_by_owner,
	 const HoI4::States& hoi4_states)
{
	std::vector<HoI4::PossiblePath> loop_paths;
	std::vector<HoI4::PossiblePath> spanning_paths;
	for (const auto& [owner, capital]: capitals)
	{
		const auto [new_spanning_paths, new_loop_paths] =
			 ConstructSpanningTree(owner, possible_paths_by_owner, capital, hoi4_states);
		spanning_paths.insert(spanning_paths.end(), new_spanning_paths.begin(), new_spanning_paths.end());
		loop_paths.insert(loop_paths.end(), new_loop_paths.begin(), new_loop_paths.end());
	}

	return {spanning_paths, loop_paths};
}


std::vector<HoI4::PossiblePath> AssembleExtraPaths(const std::vector<HoI4::PossiblePath>& border_crossings,
	 const std::vector<HoI4::PossiblePath>& loop_paths)
{
	std::vector<HoI4::PossiblePath> extra_paths;
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

	return extra_paths;
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
	 const HoI4::States& hoi4_states)
{
	Log(LogLevel::Info) << "\tDetermining railways";

	const auto valid_vic2_province_numbers = FindValidVic2ProvinceNumbers(vic2_states);
	const auto vic2_state_capitals = GetVic2StateCapitals(vic2_states);
	const auto vic2_province_paths =
		 DetermineVic2PossiblePaths(valid_vic2_province_numbers, vic2_provinces, vic2_map_data);
	const auto hoi4_provinces_to_owners_map = MapHoi4ProvincesToOwners(hoi4_states);

	const auto [possible_paths_by_owner, border_crossings] = FindAllHoi4Paths(vic2_province_paths,
		 vic2_provinces,
		 province_mapper,
		 impassable_provinces,
		 hoi4_provinces,
		 naval_base_locations,
		 vic2_state_capitals,
		 hoi4_map_data,
		 hoi4_province_definitions,
		 hoi4_provinces_to_owners_map);

	const auto naval_locations = DetermineNavalLocations(hoi4_states);
	const auto capitals = DetermineHoI4Capitals(hoi4_states);
	auto [spanning_paths, loop_paths] = ConstructSpanningTrees(capitals, possible_paths_by_owner, hoi4_states);

	for (const auto& extra_path: AssembleExtraPaths(border_crossings, loop_paths))
	{
		double without_cost = std::numeric_limits<double>::max();

		std::set<int> reached_points;
		std::priority_queue<PathPoint> points_to_try;
		PathPoint initial_path = {.province = extra_path.GetFirstProvince()};
		points_to_try.push(initial_path);
		while (!points_to_try.empty())
		{
			const auto point_to_try = points_to_try.top();
			points_to_try.pop();
			if (point_to_try.province == extra_path.GetLastProvince())
			{
				without_cost = point_to_try.cost;
				break;
			}

			for (const auto& path: spanning_paths)
			{
				if (path.GetFirstProvince() == point_to_try.province && !reached_points.contains(path.GetLastProvince()))
				{
					PathPoint new_path = {.province = path.GetLastProvince(), .cost = point_to_try.cost + path.GetCost()};
					points_to_try.push(new_path);
					reached_points.insert(path.GetLastProvince());
				}
				if (path.GetLastProvince() == point_to_try.province && !reached_points.contains(path.GetFirstProvince()))
				{
					PathPoint new_path = {.province = path.GetFirstProvince(), .cost = point_to_try.cost + path.GetCost()};
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

	for (const auto& path: trimmed_paths)
	{
		Railway railway(path.GetLevel(), path.GetProvinces());
		railways_.push_back(railway);
		railway_endpoints_.insert(path.GetFirstProvince());
		railway_endpoints_.insert(path.GetLastProvince());
	}
}

// todo: code cleanup, it's ugly as can be right now