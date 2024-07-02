#include "src/Maps/MapData.h"
#include "external/bitmap/bitmap_image.hpp"
#include "external/common_items/Color.h"
#include "external/common_items/Log.h"
#include "src/Configuration.h"



namespace
{

commonItems::Color GetCenterColor(const Maps::Point position, const bitmap_image& province_map)
{
	rgb_t color{0, 0, 0};
	province_map.get_pixel(position.first, position.second, color);

	return commonItems::Color(std::array<int, 3>{color.red, color.green, color.blue});
}


commonItems::Color GetAboveColor(Maps::Point position, const bitmap_image& province_map)
{
	if (position.second > 0)
	{
		position.second--;
	}

	rgb_t color{0, 0, 0};
	province_map.get_pixel(position.first, position.second, color);

	return commonItems::Color(std::array<int, 3>{color.red, color.green, color.blue});
}


commonItems::Color GetBelowColor(Maps::Point position, int height, const bitmap_image& province_map)
{
	if (position.second < height - 1)
	{
		position.second++;
	}

	rgb_t color{0, 0, 0};
	province_map.get_pixel(position.first, position.second, color);

	return commonItems::Color(std::array<int, 3>{color.red, color.green, color.blue});
}


commonItems::Color GetLeftColor(Maps::Point position, int width, const bitmap_image& province_map)
{
	if (position.first > 0)
	{
		position.first--;
	}
	else
	{
		position.first = width - 1;
	}

	rgb_t color{0, 0, 0};
	province_map.get_pixel(position.first, position.second, color);

	return commonItems::Color(std::array<int, 3>{color.red, color.green, color.blue});
}


commonItems::Color GetRightColor(Maps::Point position, int width, const bitmap_image& province_map)
{
	if (position.first < width - 1)
	{
		position.first++;
	}
	else
	{
		position.first = 0;
	}

	rgb_t color{0, 0, 0};
	province_map.get_pixel(position.first, position.second, color);

	return commonItems::Color(std::array<int, 3>{color.red, color.green, color.blue});
}

} // namespace


Maps::MapData::MapData(const ProvinceDefinitions& province_definitions,
	 const commonItems::ModFilesystem& mod_filesystem):
	 province_definitions_(province_definitions)
{
	ImportProvinces(mod_filesystem);
	ImportAdjacencies(mod_filesystem);
}

Maps::MapData::MapData(const ProvinceDefinitions& province_definitions, const std::string& path):
	 province_definitions_(province_definitions)
{
	ImportProvinces(path);
	ImportAdjacencies(path);
}


void Maps::MapData::ImportProvinces(const commonItems::ModFilesystem& mod_filesystem)
{
	const auto path = mod_filesystem.GetActualFileLocation("/map/provinces.bmp");
	if (!path)
	{
		throw std::runtime_error("Could not find /map/provinces.bmp");
	}
	ImportProvinces(*path);
}

void Maps::MapData::ImportProvinces(const std::string& path)
{
	auto full_path = path;
	if (path.find("/map/provinces.bmp") == std::string::npos)
		full_path = path + "/map/provinces.bmp";

	bitmap_image province_map(full_path);
	if (!province_map)
	{
		throw std::runtime_error("Could not open " + full_path + "/map/provinces.bmp");
	}

	const int height = static_cast<int>(province_map.height());
	const int width = static_cast<int>(province_map.width());
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Point position = {x, y};

			auto center_color = GetCenterColor(position, province_map);
			auto above_color = GetAboveColor(position, province_map);
			auto below_color = GetBelowColor(position, height, province_map);
			auto left_color = GetLeftColor(position, width, province_map);
			auto right_color = GetRightColor(position, width, province_map);

			position.second = height - y - 1;
			if (center_color != above_color)
			{
				HandleNeighbor(center_color, above_color, position);
			}
			if (center_color != right_color)
			{
				HandleNeighbor(center_color, right_color, position);
			}
			if (center_color != below_color)
			{
				HandleNeighbor(center_color, below_color, position);
			}
			if (center_color != left_color)
			{
				HandleNeighbor(center_color, left_color, position);
			}

			if (auto province = province_definitions_.getProvinceFromColor(center_color); province)
			{
				if (auto specific_province_points = the_province_points_.find(*province);
					 specific_province_points != the_province_points_.end())
				{
					specific_province_points->second.addPoint(position);
				}
				else
				{
					ProvincePoints the_new_points;
					the_new_points.addPoint(position);
					the_province_points_.insert(std::make_pair(*province, the_new_points));
				}
			}
		}
	}
}


void Maps::MapData::HandleNeighbor(const commonItems::Color& center_color,
	 const commonItems::Color& other_color,
	 const Point& position)
{
	const auto center_province = province_definitions_.getProvinceFromColor(center_color);
	const auto other_province = province_definitions_.getProvinceFromColor(other_color);
	if (center_province && other_province)
	{
		AddNeighbor(*center_province, *other_province);
		AddPointToBorder(*center_province, *other_province, position);
	}
}


void Maps::MapData::AddNeighbor(int main_province, int neighbor_province)
{
	if (const auto center_mapping = province_neighbors_.find(main_province); center_mapping != province_neighbors_.end())
	{
		center_mapping->second.insert(neighbor_province);
	}
	else
	{
		const std::set<int> neighbors = {neighbor_province};
		province_neighbors_[main_province] = neighbors;
	}
}


void Maps::MapData::RemoveNeighbor(int main_province, int neighbor_province)
{
	if (const auto center_mapping = province_neighbors_.find(main_province); center_mapping != province_neighbors_.end())
	{
		center_mapping->second.erase(neighbor_province);
	}
}


void Maps::MapData::AddPointToBorder(int main_province, int neighbor_province, const Point position)
{
	auto borders_with_neighbors = borders_.find(main_province);
	if (borders_with_neighbors == borders_.end())
	{
		BordersWith new_borders_with_neighbors;
		borders_.insert(make_pair(main_province, new_borders_with_neighbors));
		borders_with_neighbors = borders_.find(main_province);
	}

	auto border = borders_with_neighbors->second.find(neighbor_province);
	if (border == borders_with_neighbors->second.end())
	{
		BorderPoints new_border;
		borders_with_neighbors->second.insert(make_pair(neighbor_province, new_border));
		border = borders_with_neighbors->second.find(neighbor_province);
	}

	if (border->second.empty())
	{
		border->second.push_back(position);
	}
	else
	{
		if (const auto last_point = border->second.back();
			 (last_point.first != position.first) || (last_point.second != position.second))
		{
			border->second.push_back(position);
		}
	}
}


void Maps::MapData::ImportAdjacencies(const commonItems::ModFilesystem& mod_filesystem)
{
	const auto path = mod_filesystem.GetActualFileLocation("/map/adjacencies.csv");
	if (!path)
	{
		throw std::runtime_error("Could not find /map/adjacencies.csv");
	}
	ImportAdjacencies(*path);
}

void Maps::MapData::ImportAdjacencies(const std::string& path)
{
	auto full_path = path;
	if (path.find("/map/adjacencies.csv") == std::string::npos)
		full_path = path + "/map/adjacencies.csv";

	std::ifstream adjacencies_file(full_path);
	if (!adjacencies_file.is_open())
	{
		throw std::runtime_error("Could not open " + full_path);
	}

	while (!adjacencies_file.eof())
	{
		std::string line;
		getline(adjacencies_file, line);
		if (line.starts_with('#'))
		{
			continue;
		}

		const std::regex pattern("([^;]*);([^;]*);([^;]*)(.*)\r?");
		if (std::smatch matches; regex_match(line, matches, pattern))
		{
			if (matches[1] == "From" || matches[1] == "-1")
			{
				continue;
			}

			if (matches[1].length() == 0)
			{
				continue;
			}
			const int first_province = std::stoi(matches[1]);
			if (matches[2].length() == 0)
			{
				continue;
			}
			const int second_province = std::stoi(matches[2]);
			if (matches[3] != "impassable")
			{
				AddNeighbor(first_province, second_province);
				AddNeighbor(second_province, first_province);
			}
			else
			{
				RemoveNeighbor(first_province, second_province);
				RemoveNeighbor(second_province, first_province);
			}
		}
	}
}


std::set<int> Maps::MapData::GetNeighbors(int province) const
{
	const auto neighbors = province_neighbors_.find(province);
	if (neighbors == province_neighbors_.end())
	{
		return {};
	}

	return neighbors->second;
}


std::optional<Maps::Point> Maps::MapData::GetSpecifiedBorderCenter(int main_province, int neighbor) const
{
	const auto borders_with_neighbors = borders_.find(main_province);
	if (borders_with_neighbors == borders_.end())
	{
		Log(LogLevel::Warning) << "Province " << main_province << " has no borders.";
		return std::nullopt;
	}

	const auto border = borders_with_neighbors->second.find(neighbor);
	if (border == borders_with_neighbors->second.end())
	{
		Log(LogLevel::Warning) << "Province " << main_province << " does not border " << neighbor << ".";
		return std::nullopt;
	}

	return border->second[(border->second.size() / 2)];
}


std::optional<Maps::Point> Maps::MapData::GetAnyBorderCenter(const int province) const
{
	const auto borders_with_neighbors = borders_.find(province);
	if (borders_with_neighbors == borders_.end())
	{
		Log(LogLevel::Warning) << "Province " << province << " has no borders.";
		return std::nullopt;
	}

	const auto border = borders_with_neighbors->second.begin();
	// if a province has borders, by definition they're with some number of neighbors and of some length
	return border->second[(border->second.size() / 2)];
}


std::optional<int> Maps::MapData::GetProvinceNumber(const Point& point) const
{
	const auto i = std::find_if(the_province_points_.begin(), the_province_points_.end(), [point](const auto& province) {
		return province.second.hasPoint(point);
	});
	if (i == the_province_points_.end())
	{
		return std::nullopt;
	}
	return i->first;
}


std::optional<Maps::ProvincePoints> Maps::MapData::GetProvincePoints(int province_num) const
{
	const auto possible_points = the_province_points_.find(province_num);
	if (possible_points == the_province_points_.end())
	{
		return std::nullopt;
	}
	return possible_points->second;
}