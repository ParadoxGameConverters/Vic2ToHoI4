#include "src/HOI4World/Map/StrategicRegions.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "src/HOI4World/States/HoI4State.h"
#include "src/HOI4World/States/HoI4States.h"
#include <ranges>
#include <set>



namespace
{

[[nodiscard]] std::map<int, int> DetermineUsedRegions(const HoI4::State& state,
	 const std::map<int, int>& province_to_strategic_region_map)
{
	std::map<int, int> used_regions; // region ID -> number of provinces in that region

	for (auto province: state.getProvinces())
	{
		auto mapping = province_to_strategic_region_map.find(province);
		if (mapping == province_to_strategic_region_map.end())
		{
			Log(LogLevel::Warning) << "Province " << province << " had no original strategic region";
			continue;
		}

		if (auto [iterator, success] = used_regions.emplace(mapping->second, 1); !success)
		{
			++iterator->second;
		}
	}

	// hack to make Novgorod a last-choice region to work around this hoi4 bug:
	// https://forum.paradoxplaza.com/forum/threads/crash-due-to-some-strategic-regions.1619874/
	if (used_regions.contains(132))
	{
		used_regions[132] = 1;
	}

	return used_regions;
}


[[nodiscard]] std::optional<int> DetermineMostUsedRegion(const std::map<int, int>& used_regions)
{
	if (!used_regions.empty())
	{
		return std::ranges::max_element(used_regions, [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
			return a.second < b.second;
		})->first;
	}

	return std::nullopt;
}


void AddProvinceToRegion(int region_number, int province_id, std::map<int, HoI4::StrategicRegion>& strategic_regions)
{
	auto region = strategic_regions.find(region_number);
	if (region == strategic_regions.end())
	{
		Log(LogLevel::Warning) << "Strategic region " << region_number << " was not in the list of regions.";
		return;
	}

	region->second.addNewProvince(province_id);
}


[[nodiscard]] std::set<int> DetermineAssignedProvinces(const std::map<int, HoI4::StrategicRegion>& strategic_regions)
{
	std::set<int> assigned_provinces;
	for (const HoI4::StrategicRegion& strategic_region: strategic_regions | std::ranges::views::values)
	{
		for (int province: strategic_region.getNewProvinces())
		{
			assigned_provinces.insert(province);
		}
	}

	return assigned_provinces;
}


void AddSurroundedProvincesToRegions(const std::map<int, int>& original_province_to_strategic_region_map,
	 const std::set<int>& assigned_provinces,
	 const Maps::MapData& hoi4_map_data,
	 const std::map<int, int>& new_province_to_strategic_region_map,
	 std::map<int, HoI4::StrategicRegion>& strategic_regions)
{
	for (const auto& province: original_province_to_strategic_region_map | std::views::keys)
	{
		// this only applies to unassigned provinces
		if (assigned_provinces.contains(province))
		{
			continue;
		}

		bool has_unassigned_neighbor = false;
		std::map<int, int> used_regions; // region ID -> number of provinces in that region
		for (const int neighbor: hoi4_map_data.GetNeighbors(province))
		{
			// unassigned neighbors indicate oceans, which means this case doesn't apply
			if (!assigned_provinces.contains(neighbor))
			{
				has_unassigned_neighbor = true;
				break;
			}

			const auto itr = new_province_to_strategic_region_map.find(neighbor);
			used_regions[itr->second]++;
		}

		if (has_unassigned_neighbor)
		{
			continue;
		}

		if (const auto best_region = DetermineMostUsedRegion(used_regions); best_region)
		{
			AddProvinceToRegion(*best_region, province, strategic_regions);
		}
	}
}


void AddLeftoverProvincesToRegions(const std::set<int>& assigned_provinces,
	 const std::map<int, int>& province_to_strategic_region_map,
	 std::map<int, HoI4::StrategicRegion>& strategic_regions)
{
	for (const auto& [province, strategic_region]: province_to_strategic_region_map)
	{
		if (assigned_provinces.contains(province))
		{
			continue;
		}
		AddProvinceToRegion(strategic_region, province, strategic_regions);
	}
}


void AddProvincesToRegion(int regionNumber,
	 const HoI4::State& state,
	 std::map<int, HoI4::StrategicRegion>& strategic_regions)
{
	for (const auto& province: state.getProvinces())
	{
		AddProvinceToRegion(regionNumber, province, strategic_regions);
	}
}

} // namespace



void HoI4::StrategicRegions::Convert(const States& the_states, const Maps::MapData& hoi4_map_data)
{
	Log(LogLevel::Info) << "\tConverting strategic regions";

	for (const auto& state: the_states.getStates())
	{
		const auto used_regions = DetermineUsedRegions(state.second, original_province_to_strategic_region_map_);
		const auto best_region = DetermineMostUsedRegion(used_regions);
		if (best_region)
		{
			AddProvincesToRegion(*best_region, state.second, strategic_regions_);
		}
	}

	std::map<int, int> temp_province_to_strategic_region_map;
	for (const auto& [region_number, region]: strategic_regions_)
	{
		for (auto province: region.getNewProvinces())
		{
			temp_province_to_strategic_region_map.emplace(province, region_number);
		}
	}

	AddSurroundedProvincesToRegions(original_province_to_strategic_region_map_,
		 DetermineAssignedProvinces(strategic_regions_),
		 hoi4_map_data,
		 temp_province_to_strategic_region_map,
		 strategic_regions_);
	AddLeftoverProvincesToRegions(DetermineAssignedProvinces(strategic_regions_),
		 original_province_to_strategic_region_map_,
		 strategic_regions_);
}



std::unique_ptr<HoI4::StrategicRegions> HoI4::StrategicRegions::Factory::ImportStrategicRegions(
	 const Configuration& configuration)
{
	std::map<int, StrategicRegion> strategic_regions;
	std::map<int, int> province_to_strategic_region_map;

	for (const auto& filename: commonItems::GetAllFilesInFolder(configuration.getHoI4Path() + "/map/strategicregions/"))
	{
		auto new_region = StrategicRegion(filename, configuration);
		strategic_regions.insert(std::make_pair(new_region.getID(), new_region));

		for (auto province: new_region.getOldProvinces())
		{
			province_to_strategic_region_map.insert(std::make_pair(province, new_region.getID()));
		}
	}

	return std::make_unique<StrategicRegions>(std::move(strategic_regions), std::move(province_to_strategic_region_map));
}
