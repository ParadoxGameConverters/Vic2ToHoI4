#ifndef SRC_MAPS_MAP_DATA_H
#define SRC_MAPS_MAP_DATA_H



#include "external/common_items/Color.h"
#include "external/common_items/ModLoader/ModFilesystem.h"
#include "src/Maps/ProvinceDefinitions.h"
#include "src/Maps/ProvincePoints.h"
#include <map>
#include <optional>
#include <set>



namespace Maps
{

using BorderPoints = std::vector<Point>;
using BordersWith = std::map<int, BorderPoints>;


class MapData
{
  public:
	MapData(const ProvinceDefinitions& province_definitions, const commonItems::ModFilesystem& mod_filesystem);
	MapData(const ProvinceDefinitions& province_definitions, const std::filesystem::path& path);

	[[nodiscard]] std::set<int> GetNeighbors(int province) const;
	[[nodiscard]] std::optional<Point> GetSpecifiedBorderCenter(int main_province, int neighbor) const;
	[[nodiscard]] std::optional<Point> GetAnyBorderCenter(int province) const;
	[[nodiscard]] std::optional<int> GetProvinceNumber(const Point& point) const;

	[[nodiscard]] std::optional<ProvincePoints> GetProvincePoints(int province_number) const;

  private:
	void ImportProvinces(const commonItems::ModFilesystem& mod_filesystem);
	void ImportProvinces(const std::filesystem::path& path);
	void HandleNeighbor(const commonItems::Color& center_color,
		 const commonItems::Color& other_color,
		 const Point& position);
	void AddNeighbor(int main_province, int neighbor_province);
	void RemoveNeighbor(int main_province, int neighbor_province);
	void AddPointToBorder(int main_province, int neighbor_province, Point position);

	void ImportAdjacencies(const commonItems::ModFilesystem& mod_filesystem);
	void ImportAdjacencies(const std::filesystem::path& path);

	std::map<int, std::set<int>> province_neighbors_;
	std::map<int, BordersWith> borders_;
	std::map<int, ProvincePoints> the_province_points_;

	ProvinceDefinitions province_definitions_;
};

} // namespace Maps



#endif // SRC_MAPS_MAP_DATA_H