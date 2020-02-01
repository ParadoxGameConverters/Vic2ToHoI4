#include "MapData.h"
#include "../../Mappers/ProvinceDefinitions.h"
#include "../../Color.h"
#include "../../Configuration.h"
#include "Log.h"



ConverterColor::Color getCenterColor(point position, bitmap_image& provinceMap);
ConverterColor::Color getAboveColor(point position, bitmap_image& provinceMap);
ConverterColor::Color getBelowColor(point position, int height, bitmap_image& provinceMap);
ConverterColor::Color getLeftColor(point position, int width, bitmap_image& provinceMap);
ConverterColor::Color getRightColor(point position, int width, bitmap_image& provinceMap);


HoI4::MapData::MapData(): provinceMap(theConfiguration.getHoI4Path() + "/map/provinces.bmp")
{
	if (!provinceMap)
	{
		throw std::runtime_error("Could not open " + theConfiguration.getHoI4Path() + "/map/provinces.bmp");
	}

	auto height = provinceMap.height();
	auto width = provinceMap.width();
	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			point position = { x, y };

			auto centerColor = getCenterColor(position, provinceMap);
			auto aboveColor = getAboveColor(position, provinceMap);
			auto belowColor = getBelowColor(position, height, provinceMap);
			auto leftColor = getLeftColor(position, width, provinceMap);
			auto rightColor = getRightColor(position, width, provinceMap);

			position.second = height - position.second - 1;
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

			auto province = provinceDefinitions::getProvinceFromColor(centerColor);
			if (province)
			{
				auto specificProvincePoints = theProvincePoints.find(*province);
				if (specificProvincePoints != theProvincePoints.end())
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


ConverterColor::Color getCenterColor(const point position, bitmap_image& provinceMap)
{
	rgb_t color{ 0,0,0 };
	provinceMap.get_pixel(position.first, position.second, color);

	ConverterColor::Color theColor(
		ConverterColor::red(color.red), 
		ConverterColor::green(color.green), 
		ConverterColor::blue(color.blue)
	);
	return theColor;
}


ConverterColor::Color getAboveColor(point position, bitmap_image& provinceMap)
{
	if (position.second > 0)
	{
		position.second--;
	}

	rgb_t color{ 0,0,0 };
	provinceMap.get_pixel(position.first, position.second, color);

	ConverterColor::Color theColor(
		ConverterColor::red(color.red), 
		ConverterColor::green(color.green), 
		ConverterColor::blue(color.blue));
	return theColor;
}


ConverterColor::Color getBelowColor(point position, const int height, bitmap_image& provinceMap)
{
	if (position.second < height - 1)
	{
		position.second++;
	}

	rgb_t color{ 0,0,0 };
	provinceMap.get_pixel(position.first, position.second, color);

	ConverterColor::Color theColor(
		ConverterColor::red(color.red), 
		ConverterColor::green(color.green), 
		ConverterColor::blue(color.blue)
	);
	return theColor;
}


ConverterColor::Color getLeftColor(point position, const int width, bitmap_image& provinceMap)
{
	if (position.first > 0)
	{
		position.first--;
	}
	else
	{
		position.first = width - 1;
	}

	rgb_t color{ 0,0,0 };
	provinceMap.get_pixel(position.first, position.second, color);

	ConverterColor::Color theColor(
		ConverterColor::red(color.red),
		ConverterColor::green(color.green),
		ConverterColor::blue(color.blue)
	);
	return theColor;
}


ConverterColor::Color getRightColor(point position, const int width, bitmap_image& provinceMap)
{
	if (position.first < width - 1)
	{
		position.first++;
	}
	else
	{
		position.first = 0;
	}

	rgb_t color{ 0,0,0 };
	provinceMap.get_pixel(position.first, position.second, color);

	ConverterColor::Color theColor(
		ConverterColor::red(color.red),
		ConverterColor::green(color.green),
		ConverterColor::blue(color.blue)
	);
	return theColor;
}


void HoI4::MapData::handleNeighbor(
	const ConverterColor::Color& centerColor,
	const ConverterColor::Color& otherColor,
	const point& position
)
{
	auto centerProvince = provinceDefinitions::getProvinceFromColor(centerColor);
	auto otherProvince = provinceDefinitions::getProvinceFromColor(otherColor);
	if (centerProvince && otherProvince)
	{
		addNeighbor(*centerProvince, *otherProvince);
		addPointToBorder(*centerProvince, *otherProvince, position);
	}
}


void HoI4::MapData::addNeighbor(const int mainProvince, const int neighborProvince)
{
	if (auto centerMapping = provinceNeighbors.find(mainProvince); centerMapping != provinceNeighbors.end())
	{
		centerMapping->second.insert(neighborProvince);
	}
	else
	{
		const std::set<int> neighbors = { neighborProvince };
		provinceNeighbors[mainProvince] = neighbors;
	}
}


void HoI4::MapData::addPointToBorder(int mainProvince, int neighborProvince, const point position)
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
		const auto lastPoint = border->second.back();
		if ((lastPoint.first != position.first) || (lastPoint.second != position.second))
		{
			border->second.push_back(position);
		}
	}
}


std::set<int> HoI4::MapData::getNeighbors(const int province) const
{
	if (const auto neighbors = provinceNeighbors.find(province); neighbors != provinceNeighbors.end())
	{
		return neighbors->second;
	}
	else
	{
		std::set<int> empty;
		return empty;
	}
}


std::optional<point> HoI4::MapData::getSpecifiedBorderCenter(const int mainProvince, const int neighbor) const
{
	const auto bordersWithNeighbors = borders.find(mainProvince);
	if (bordersWithNeighbors == borders.end())
	{
		LOG(LogLevel::Warning) << "Province " << mainProvince << " has no borders.";
		return std::nullopt;
	}
	
	const auto border = bordersWithNeighbors->second.find(neighbor);
	if (border == bordersWithNeighbors->second.end())
	{
		LOG(LogLevel::Warning) << "Province " << mainProvince << " does not border " << neighbor << ".";
		return std::nullopt;
	}

	return border->second[(border->second.size() / 2)];
}


std::optional<point> HoI4::MapData::getAnyBorderCenter(const int province) const
{
	const auto bordersWithNeighbors = borders.find(province);
	if (bordersWithNeighbors == borders.end())
	{
		LOG(LogLevel::Warning) << "Province " << province << " has no borders.";
		return std::nullopt;
	}

	const auto border = bordersWithNeighbors->second.begin();
	if (border == bordersWithNeighbors->second.end())
	{
		LOG(LogLevel::Warning) << "Province " << province << " has no borders.";
		return std::nullopt;
	}

	return border->second[(border->second.size() / 2)];
}


std::optional<int> HoI4::MapData::getProvinceNumber(const double x, const double y) const
{
	rgb_t color{0,0,0};
	provinceMap.get_pixel(
		static_cast<unsigned int>(x),
		(provinceMap.height() - 1) - static_cast<unsigned int>(y),
		color
	);
	const ConverterColor::Color theColor(
		ConverterColor::red(color.red),
		ConverterColor::green(color.green),
		ConverterColor::blue(color.blue)
	);
	return provinceDefinitions::getProvinceFromColor(theColor);
}


std::optional<HoI4::ProvincePoints> HoI4::MapData::getProvincePoints(const int provinceNum) const
{
	if (const auto possiblePoints = theProvincePoints.find(provinceNum); possiblePoints != theProvincePoints.end())
	{
		return possiblePoints->second;
	}
	else
	{
		return std::nullopt;
	}
}