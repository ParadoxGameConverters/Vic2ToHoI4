#include "MapData.h"
#include "Color.h"
#include "Configuration.h"
#include "Log.h"



namespace
{

commonItems::Color getCenterColor(const Maps::Point position, const bitmap_image& provinceMap)
{
	rgb_t color{0, 0, 0};
	provinceMap.get_pixel(position.first, position.second, color);

	return commonItems::Color(std::array<int, 3>{color.red, color.green, color.blue});
}


commonItems::Color getAboveColor(Maps::Point position, const bitmap_image& provinceMap)
{
	if (position.second > 0)
	{
		position.second--;
	}

	rgb_t color{0, 0, 0};
	provinceMap.get_pixel(position.first, position.second, color);

	return commonItems::Color(std::array<int, 3>{color.red, color.green, color.blue});
}


commonItems::Color getBelowColor(Maps::Point position, const unsigned int height, const bitmap_image& provinceMap)
{
	if (position.second < height - 1)
	{
		position.second++;
	}

	rgb_t color{0, 0, 0};
	provinceMap.get_pixel(position.first, position.second, color);

	return commonItems::Color(std::array<int, 3>{color.red, color.green, color.blue});
}


commonItems::Color getLeftColor(Maps::Point position, const unsigned int width, const bitmap_image& provinceMap)
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
	provinceMap.get_pixel(position.first, position.second, color);

	return commonItems::Color(std::array<int, 3>{color.red, color.green, color.blue});
}


commonItems::Color getRightColor(Maps::Point position, const unsigned int width, const bitmap_image& provinceMap)
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
	provinceMap.get_pixel(position.first, position.second, color);

	return commonItems::Color(std::array<int, 3>{color.red, color.green, color.blue});
}

} // namespace


Maps::MapData::MapData(const ProvinceDefinitions& provinceDefinitions, const std::string& path):
	 provinceDefinitions_(provinceDefinitions)
{
	bitmap_image provinceMap(path + "/map/provinces.bmp");
	if (!provinceMap)
	{
		throw std::runtime_error("Could not open " + path + "/map/provinces.bmp");
	}

	importProvinces(provinceMap);
	importAdjacencies(path);
}


void Maps::MapData::importProvinces(const bitmap_image& provinceMap)
{
	const auto height = provinceMap.height();
	const auto width = provinceMap.width();
	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			Point position = {x, y};

			auto centerColor = getCenterColor(position, provinceMap);
			auto aboveColor = getAboveColor(position, provinceMap);
			auto belowColor = getBelowColor(position, height, provinceMap);
			auto leftColor = getLeftColor(position, width, provinceMap);
			auto rightColor = getRightColor(position, width, provinceMap);

			position.second = height - y - 1;
			if (centerColor != aboveColor)
			{
				handleNeighbor(centerColor, aboveColor, position);
			}
			if (centerColor != rightColor)
			{
				handleNeighbor(centerColor, rightColor, position);
			}
			if (centerColor != belowColor)
			{
				handleNeighbor(centerColor, belowColor, position);
			}
			if (centerColor != leftColor)
			{
				handleNeighbor(centerColor, leftColor, position);
			}

			if (auto province = provinceDefinitions_.getProvinceFromColor(centerColor); province)
			{
				pointsToProvinces_.emplace(position, *province);
				if (auto specificProvincePoints = theProvincePoints.find(*province);
					 specificProvincePoints != theProvincePoints.end())
				{
					specificProvincePoints->second.addPoint(position);
				}
				else
				{
					ProvincePoints theNewPoints;
					theNewPoints.addPoint(position);
					theProvincePoints.insert(std::make_pair(*province, theNewPoints));
				}
			}
		}
	}
}


void Maps::MapData::handleNeighbor(const commonItems::Color& centerColor,
	 const commonItems::Color& otherColor,
	 const Point& position)
{
	auto centerProvince = provinceDefinitions_.getProvinceFromColor(centerColor);
	auto otherProvince = provinceDefinitions_.getProvinceFromColor(otherColor);
	if (centerProvince && otherProvince)
	{
		addNeighbor(*centerProvince, *otherProvince);
		addPointToBorder(*centerProvince, *otherProvince, position);
	}
}


void Maps::MapData::addNeighbor(const int mainProvince, const int neighborProvince)
{
	if (const auto centerMapping = provinceNeighbors.find(mainProvince); centerMapping != provinceNeighbors.end())
	{
		centerMapping->second.insert(neighborProvince);
	}
	else
	{
		const std::set<int> neighbors = {neighborProvince};
		provinceNeighbors[mainProvince] = neighbors;
	}
}


void Maps::MapData::removeNeighbor(const int mainProvince, const int neighborProvince)
{
	if (const auto centerMapping = provinceNeighbors.find(mainProvince); centerMapping != provinceNeighbors.end())
	{
		centerMapping->second.erase(neighborProvince);
	}
}


void Maps::MapData::addPointToBorder(int mainProvince, int neighborProvince, const Point position)
{
	auto bordersWithNeighbors = borders.find(mainProvince);
	if (bordersWithNeighbors == borders.end())
	{
		bordersWith newBordersWithNeighbors;
		borders.insert(make_pair(mainProvince, newBordersWithNeighbors));
		bordersWithNeighbors = borders.find(mainProvince);
	}

	auto border = bordersWithNeighbors->second.find(neighborProvince);
	if (border == bordersWithNeighbors->second.end())
	{
		borderPoints newBorder;
		bordersWithNeighbors->second.insert(make_pair(neighborProvince, newBorder));
		border = bordersWithNeighbors->second.find(neighborProvince);
	}

	if (border->second.empty())
	{
		border->second.push_back(position);
	}
	else
	{
		if (const auto lastPoint = border->second.back();
			 (lastPoint.first != position.first) || (lastPoint.second != position.second))
		{
			border->second.push_back(position);
		}
	}
}


void Maps::MapData::importAdjacencies(const std::string& path)
{
	std::ifstream adjacenciesFile(path + "/map/adjacencies.csv");
	if (!adjacenciesFile.is_open())
	{
		throw std::runtime_error("Could not open " + path + "/map/adjacencies.csv");
	}

	while (!adjacenciesFile.eof())
	{
		std::string line;
		getline(adjacenciesFile, line);
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

			const int firstProvince = std::stoi(matches[1]);
			const int secondProvince = std::stoi(matches[2]);
			if (matches[3] != "impassable")
			{
				addNeighbor(firstProvince, secondProvince);
				addNeighbor(secondProvince, firstProvince);
			}
			else
			{
				removeNeighbor(firstProvince, secondProvince);
				removeNeighbor(secondProvince, firstProvince);
			}
		}
	}
}


std::set<int> Maps::MapData::getNeighbors(const int province) const
{
	const auto neighbors = provinceNeighbors.find(province);
	if (neighbors == provinceNeighbors.end())
	{
		return {};
	}

	return neighbors->second;
}


std::optional<Maps::Point> Maps::MapData::getSpecifiedBorderCenter(const int mainProvince, const int neighbor) const
{
	const auto bordersWithNeighbors = borders.find(mainProvince);
	if (bordersWithNeighbors == borders.end())
	{
		Log(LogLevel::Warning) << "Province " << mainProvince << " has no borders.";
		return std::nullopt;
	}

	const auto border = bordersWithNeighbors->second.find(neighbor);
	if (border == bordersWithNeighbors->second.end())
	{
		Log(LogLevel::Warning) << "Province " << mainProvince << " does not border " << neighbor << ".";
		return std::nullopt;
	}

	return border->second[(border->second.size() / 2)];
}


std::optional<Maps::Point> Maps::MapData::getAnyBorderCenter(const int province) const
{
	const auto bordersWithNeighbors = borders.find(province);
	if (bordersWithNeighbors == borders.end())
	{
		Log(LogLevel::Warning) << "Province " << province << " has no borders.";
		return std::nullopt;
	}

	const auto border = bordersWithNeighbors->second.begin();
	// if a province has borders, by definition they're with some number of neighbors and of some length
	return border->second[(border->second.size() / 2)];
}


std::optional<int> Maps::MapData::getProvinceNumber(const Point& point) const
{
	const auto i = pointsToProvinces_.find(point);
	if (i == pointsToProvinces_.end())
	{
		return std::nullopt;
	}
	return i->second;
}


std::optional<Maps::ProvincePoints> Maps::MapData::getProvincePoints(const int provinceNum) const
{
	const auto possiblePoints = theProvincePoints.find(provinceNum);
	if (possiblePoints == theProvincePoints.end())
	{
		return std::nullopt;
	}
	return possiblePoints->second;
}