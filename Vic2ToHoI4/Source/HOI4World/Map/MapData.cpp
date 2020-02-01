#include "MapData.h"
#include "../../Mappers/ProvinceDefinitions.h"
#include "../../Color.h"
#include "../../Configuration.h"
#include "Log.h"



HoI4::MapData::MapData() noexcept:
	provinceMap(theConfiguration.getHoI4Path() + "/map/provinces.bmp")
{
	if (!provinceMap)
	{
		LOG(LogLevel::Error) << "Could not open " << theConfiguration.getHoI4Path() << "/map/provinces.bmp";
	}

	unsigned int height = provinceMap.height();
	unsigned int width = provinceMap.width();

	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			point position = { x, y };

			ConverterColor::Color centerColor = getCenterColor(position);
			ConverterColor::Color aboveColor = getAboveColor(position, height);
			ConverterColor::Color belowColor = getBelowColor(position, height);
			ConverterColor::Color leftColor = getLeftColor(position, width);
			ConverterColor::Color rightColor = getRightColor(position, width);

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
					theProvincePoints.insert(make_pair(*province, theNewPoints));
				}
			}
		}
	}
}


ConverterColor::Color HoI4::MapData::getCenterColor(point position)
{
	rgb_t color;
	provinceMap.get_pixel(position.first, position.second, color);

	ConverterColor::Color theColor(ConverterColor::red(color.red), ConverterColor::green(color.green), ConverterColor::blue(color.blue));
	return theColor;
}


ConverterColor::Color HoI4::MapData::getAboveColor(point position, int height)
{
	if (position.second > 0)
	{
		position.second--;
	}

	rgb_t color;
	provinceMap.get_pixel(position.first, position.second, color);

	ConverterColor::Color theColor(ConverterColor::red(color.red), ConverterColor::green(color.green), ConverterColor::blue(color.blue));
	return theColor;
}


ConverterColor::Color HoI4::MapData::getBelowColor(point position, int height)
{
	if (position.second < height - 1)
	{
		position.second++;
	}

	rgb_t color;
	provinceMap.get_pixel(position.first, position.second, color);

	ConverterColor::Color theColor(ConverterColor::red(color.red), ConverterColor::green(color.green), ConverterColor::blue(color.blue));
	return theColor;
}


ConverterColor::Color HoI4::MapData::getLeftColor(point position, int width)
{
	if (position.first > 0)
	{
		position.first--;
	}
	else
	{
		position.first = width - 1;
	}

	rgb_t color;
	provinceMap.get_pixel(position.first, position.second, color);

	ConverterColor::Color theColor(ConverterColor::red(color.red), ConverterColor::green(color.green), ConverterColor::blue(color.blue));
	return theColor;
}


ConverterColor::Color HoI4::MapData::getRightColor(point position, int width)
{
	if (position.first < width - 1)
	{
		position.first++;
	}
	else
	{
		position.first = 0;
	}

	rgb_t color;
	provinceMap.get_pixel(position.first, position.second, color);

	ConverterColor::Color theColor(ConverterColor::red(color.red), ConverterColor::green(color.green), ConverterColor::blue(color.blue));
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


void HoI4::MapData::addNeighbor(int mainProvince, int neighborProvince)
{
	auto centerMapping = provinceNeighbors.find(mainProvince);
	if (centerMapping != provinceNeighbors.end())
	{
		centerMapping->second.insert(neighborProvince);
	}
	else
	{
		std::set<int> neighbors = { neighborProvince };
		provinceNeighbors[mainProvince] = neighbors;
	}
}


void HoI4::MapData::addPointToBorder(int mainProvince, int neighborProvince, point position)
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

	if (border->second.size() == 0)
	{
		border->second.push_back(position);
	}
	else
	{
		auto lastPoint = border->second.back();
		if ((lastPoint.first != position.first) || (lastPoint.second != position.second))
		{
			border->second.push_back(position);
		}
	}
}


set<int> HoI4::MapData::getNeighbors(int province) const
{
	auto neighbors = provinceNeighbors.find(province);
	if (neighbors != provinceNeighbors.end())
	{
		return neighbors->second;
	}
	else
	{
		std::set<int> empty;
		return empty;
	}
}


optional<point> HoI4::MapData::getSpecifiedBorderCenter(int mainProvince, int neighbor) const
{
	auto bordersWithNeighbors = borders.find(mainProvince);
	if (bordersWithNeighbors == borders.end())
	{
		LOG(LogLevel::Warning) << "Province " << mainProvince << " has no borders.";
		return std::nullopt;
	}
	auto border = bordersWithNeighbors->second.find(neighbor);
	if (border == bordersWithNeighbors->second.end())
	{
		LOG(LogLevel::Warning) << "Province " << mainProvince << " does not border " << neighbor << ".";
		return std::nullopt;
	}

	return border->second[(border->second.size() / 2)];
}


optional<point> HoI4::MapData::getAnyBorderCenter(int province) const
{
	auto bordersWithNeighbors = borders.find(province);
	if (bordersWithNeighbors == borders.end())
	{
		LOG(LogLevel::Warning) << "Province " << province << " has no borders.";
		return std::nullopt;
	}
	auto border = bordersWithNeighbors->second.begin();
	if (border == bordersWithNeighbors->second.end())
	{
		LOG(LogLevel::Warning) << "Province " << province << " has no borders.";
		return std::nullopt;
	}

	return border->second[(border->second.size() / 2)];
}


optional<int> HoI4::MapData::getProvinceNumber(double x, double y)
{
	rgb_t color;
	provinceMap.get_pixel(static_cast<unsigned int>(x), (provinceMap.height() - 1) - static_cast<unsigned int>(y), color);
	ConverterColor::Color theColor(ConverterColor::red(color.red), ConverterColor::green(color.green), ConverterColor::blue(color.blue));
	return provinceDefinitions::getProvinceFromColor(theColor);
}


std::optional<HoI4::ProvincePoints> HoI4::MapData::getProvincePoints(int provinceNum) const
{
	auto possiblePoints = theProvincePoints.find(provinceNum);
	if (possiblePoints != theProvincePoints.end())
	{
		return possiblePoints->second;
	}
	else
	{
		return std::nullopt;
	}
}