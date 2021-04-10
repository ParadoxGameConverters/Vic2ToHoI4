#include "MapUtils.h"
#include <sstream>



std::optional<double> HoI4::MapUtils::getDistanceBetweenCountries(std::shared_ptr<HoI4::Country> country1,
	 std::shared_ptr<HoI4::Country> country2)
{
	auto distanceBetweenCountries = getDistanceBetweenCapitals(country1, country2);
	std::pair<int, int> capital2Position = getCapitalPosition(country2);

	for (auto province1: country1->getProvinces())
	{
		auto province1Position = getProvincePosition(province1);
		if (auto newDistance = getDistanceBetweenPoints(province1Position, capital2Position);
			 newDistance < distanceBetweenCountries)
		{
			distanceBetweenCountries = newDistance;
			for (auto province2: country2->getProvinces())
			{
				auto province2Position = getProvincePosition(province2);
				if (auto newestDistance = getDistanceBetweenPoints(province1Position, province2Position);
					 newestDistance < distanceBetweenCountries)
				{
					distanceBetweenCountries = newestDistance;
				}
			}
		}
	}

	return distanceBetweenCountries;
}


std::optional<double> HoI4::MapUtils::getDistanceBetweenCapitals(std::shared_ptr<HoI4::Country> country1,
	 std::shared_ptr<HoI4::Country> country2)
{
	if (!bothCountriesHaveCapitals(country1, country2))
	{
		return {};
	}

	std::pair<int, int> country1Position = getCapitalPosition(country1);
	std::pair<int, int> country2Position = getCapitalPosition(country2);

	return getDistanceBetweenPoints(country1Position, country2Position);
}


bool HoI4::MapUtils::bothCountriesHaveCapitals(std::shared_ptr<HoI4::Country> Country1,
	 std::shared_ptr<HoI4::Country> Country2) const
{
	return (Country1->getCapitalState()) && (Country2->getCapitalState());
}


std::pair<int, int> HoI4::MapUtils::getCapitalPosition(std::shared_ptr<HoI4::Country> country)
{
	auto capitalProvince = country->getCapitalProvince();
	if (capitalProvince)
	{
		return getProvincePosition(*capitalProvince);
	}
	else
	{
		return std::make_pair(65536, 65536);
	}
}


std::pair<int, int> HoI4::MapUtils::getProvincePosition(int provinceNum)
{
	if (provincePositions.size() == 0)
	{
		establishProvincePositions();
	}

	auto itr = provincePositions.find(provinceNum);
	return itr->second;
}


void HoI4::MapUtils::establishProvincePositions()
{
	std::ifstream positionsFile("Configurables/positions.txt");
	if (!positionsFile.is_open())
	{
		throw std::runtime_error("Could not open positions.txt");
	}

	std::string line;
	while (getline(positionsFile, line))
	{
		processPositionLine(line);
	}

	positionsFile.close();
}


void HoI4::MapUtils::processPositionLine(const std::string& line)
{
	std::vector<std::string> tokenizedLine = tokenizeLine(line);
	addProvincePosition(tokenizedLine);
}


void HoI4::MapUtils::addProvincePosition(const std::vector<std::string>& tokenizedLine)
{
	int province = std::stoi(tokenizedLine[0]);
	int x = std::stoi(tokenizedLine[2]);
	int y = std::stoi(tokenizedLine[4]);

	provincePositions.insert(std::make_pair(province, std::make_pair(x, y)));
}


std::vector<std::string> HoI4::MapUtils::tokenizeLine(const std::string& line)
{
	std::vector<std::string> parts;
	std::stringstream ss(line);
	std::string tok;
	while (getline(ss, tok, ';'))
	{
		parts.push_back(tok);
	}

	return parts;
}


double HoI4::MapUtils::getDistanceBetweenPoints(std::pair<int, int> point1, std::pair<int, int> point2) const
{
	int xDistance = abs(point2.first - point1.first);
	if (xDistance > 2625)
	{
		xDistance = 5250 - xDistance;
	}

	int yDistance = point2.second - point1.second;

	return sqrt(pow(xDistance, 2) + pow(yDistance, 2));
}