#include "MapUtils.h"
#include "HOI4World/States/HoI4State.h"
#include "Log.h"
#include <limits>
#include <ranges>
#include <sstream>



constexpr int mapWidth = 5250;
constexpr int halfMapWidth = mapWidth / 2;



HoI4::MapUtils::MapUtils(const std::map<int, State>& theStates,
	 const std::map<std::string, std::shared_ptr<Country>>& theCountries)
{
	Log(LogLevel::Info) << "Determining HoI4 map information";
	establishProvincePositions();
	determineProvinceOwners(theStates);
	establishDistancesBetweenCountries(theCountries);
}


void HoI4::MapUtils::establishProvincePositions()
{
	std::ifstream positionsFile("Configurables/positions.txt");

	std::string line;
	while (getline(positionsFile, line))
	{
		processPositionLine(line);
	}

	positionsFile.close();
}


void HoI4::MapUtils::processPositionLine(const std::string& line)
{
	const auto lineTokens = tokenizeLine(line);
	if (lineTokens.size() < 5)
	{
		Log(LogLevel::Warning) << "positions.txt line had too few sections: " << line;
		return;
	}

	addProvincePosition(lineTokens);
}


std::vector<std::string> HoI4::MapUtils::tokenizeLine(const std::string& line) const
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


void HoI4::MapUtils::addProvincePosition(const std::vector<std::string>& lineTokens)
{
	auto province = std::stoi(lineTokens[0]);
	auto x = std::stoi(lineTokens[2]);
	auto y = std::stoi(lineTokens[4]);

	provincePositions.insert(std::make_pair(province, Coordinate{.x = x, .y = y}));
}


void HoI4::MapUtils::determineProvinceOwners(const std::map<int, State>& theStates)
{
	for (const auto& state: theStates | std::ranges::views::values)
	{
		for (auto province: state.getProvinces())
		{
			std::string owner = state.getOwner();
			provinceToOwnerMap.insert(std::make_pair(province, owner));
		}
	}
}


void HoI4::MapUtils::establishDistancesBetweenCountries(
	 const std::map<std::string, std::shared_ptr<Country>>& theCountries)
{
	for (const auto& [tagOne, countryOne]: theCountries)
	{
		for (const auto& [tagTwo, countryTwo]: theCountries)
		{
			// no need to know the distance to one's self
			if (tagOne == tagTwo)
			{
				continue;
			}

			// we already found the distance from two to one
			if (const auto itr = distancesBetweenCountries.find(tagTwo); itr != distancesBetweenCountries.end())
			{
				if (const auto itr2 = itr->second.find(tagOne); itr2 != itr->second.end())
				{
					distancesBetweenCountries[tagOne].emplace(tagTwo, itr2->second);
					continue;
				}
			}

			// this is a new distance to calculate
			auto distance = getDistanceBetweenCountries(*countryOne, *countryTwo);
			if (distance)
			{
				distancesBetweenCountries[tagOne].emplace(tagTwo, *distance);
			}
		}
	}
}


std::optional<float> HoI4::MapUtils::getDistanceBetweenCapitals(const Country& country1, const Country& country2)
{
	const auto country1Position = getCapitalPosition(country1);
	const auto country2Position = getCapitalPosition(country2);
	if (!country1Position || !country2Position)
	{
		return std::nullopt;
	}

	return std::sqrt(getDistanceSquaredBetweenPoints(*country1Position, *country2Position));
}


std::optional<HoI4::Coordinate> HoI4::MapUtils::getCapitalPosition(const Country& country) const
{
	if (auto capitalProvince = country.getCapitalProvince(); capitalProvince)
	{
		return getProvincePosition(*capitalProvince);
	}

	return std::nullopt;
}


std::set<int> HoI4::MapUtils::findBorderStates(const Country& country,
	 const Country& neighbor,
	 const std::map<int, int>& provinceToStateIdMapping,
	 const MapData& theMapData,
	 const ProvinceDefinitions& provinceDefinitions) const
{
	std::set<int> borderProvinces;
	for (const auto& province: country.getProvinces())
	{
		for (auto borderProvince: theMapData.getNeighbors(province))
		{
			if (!provinceDefinitions.isLandProvince(borderProvince))
			{
				continue;
			}

			borderProvinces.insert(borderProvince);
		}
	}

	std::set<int> borderStates;
	for (const auto borderProvince: borderProvinces)
	{
		if (const auto provinceAndOwner = provinceToOwnerMap.find(borderProvince);
			 provinceAndOwner != provinceToOwnerMap.end() && provinceAndOwner->second == neighbor.getTag())
		{
			if (const auto provinceAndState = provinceToStateIdMapping.find(borderProvince);
				 provinceAndState != provinceToStateIdMapping.end())
			{
				borderStates.insert(provinceAndState->second);
			}
		}
	}

	return borderStates;
}


std::vector<int> HoI4::MapUtils::sortStatesByDistance(const std::set<int>& stateList,
	 const Coordinate& location,
	 const std::map<int, State>& states)
{
	std::multimap<float, int> statesWithDistance;

	for (auto stateID: stateList)
	{
		if (auto state = states.find(stateID); state != states.end())
		{
			auto distance = std::numeric_limits<float>::max();
			if (const auto stateCapital = state->second.getVPLocation(); stateCapital)
			{
				const auto stateCapitalLocation = getProvincePosition(*stateCapital);
				if (stateCapitalLocation)
				{
					distance = getDistanceSquaredBetweenPoints(location, *stateCapitalLocation);
				}
			}

			statesWithDistance.insert(std::make_pair(distance, stateID));
		}
	}

	std::vector<int> sortedStates;
	for (const auto state: statesWithDistance | std::ranges::views::values)
	{
		sortedStates.push_back(state);
	}

	return sortedStates;
}


std::set<std::string> HoI4::MapUtils::getNearbyCountries(const std::string& country, float range) const
{
	const auto countriesAndDistances = distancesBetweenCountries.find(country);
	if (countriesAndDistances == distancesBetweenCountries.end())
	{
		return {};
	}

	std::set<std::string> nearbyCountries;
	for (const auto& [tag, distance]: countriesAndDistances->second)
	{
		if (distance <= range)
		{
			nearbyCountries.insert(tag);
		}
	}

	return nearbyCountries;
}


std::set<std::string> HoI4::MapUtils::getFarCountries(const std::string& country, float range) const
{
	const auto countriesAndDistances = distancesBetweenCountries.find(country);
	if (countriesAndDistances == distancesBetweenCountries.end())
	{
		return {};
	}

	std::set<std::string> nearbyCountries;
	for (const auto& [tag, distance]: countriesAndDistances->second)
	{
		if (distance > range)
		{
			nearbyCountries.insert(tag);
		}
	}

	return nearbyCountries;
}


std::vector<std::string> HoI4::MapUtils::getGPsByDistance(const Country& country,
	 const std::vector<std::shared_ptr<Country>>& greatPowers)
{
	std::map<float, std::shared_ptr<Country>> distanceToGPMap;
	for (const auto& greatPower: greatPowers)
	{
		auto distance = getDistanceBetweenCapitals(country, *greatPower);
		if (distance)
		{
			distanceToGPMap.insert(std::make_pair(*distance, greatPower));
		}
	}

	std::vector<std::string> orderedGreatPowers(distanceToGPMap.size());
	for (const auto& country: distanceToGPMap | std::ranges::views::values)
	{
		orderedGreatPowers.push_back(country->getTag());
	}

	return orderedGreatPowers;
}


std::optional<HoI4::Coordinate> HoI4::MapUtils::getProvincePosition(int provinceNum) const
{
	if (const auto province = provincePositions.find(provinceNum); province != provincePositions.end())
	{
		return province->second;
	}

	return std::nullopt;
}


float HoI4::MapUtils::getDistanceSquaredBetweenPoints(const Coordinate& point1, const Coordinate& point2)
{
	if (const auto distance = provinceDistanceCache.find(std::make_pair(point1, point2));
		 distance != provinceDistanceCache.end())
	{
		return distance->second;
	}

	auto xDistance = static_cast<float>(abs(point2.x - point1.x));
	if (xDistance > halfMapWidth)
	{
		xDistance = mapWidth - xDistance;
	}

	const auto yDistance = static_cast<float>(point2.y - point1.y);

	const auto distance = xDistance * xDistance + yDistance * yDistance;
	provinceDistanceCache[std::make_pair(point1, point2)] = distance;
	provinceDistanceCache[std::make_pair(point2, point1)] = distance;

	return distance;
}


std::optional<float> HoI4::MapUtils::getDistanceBetweenCountries(const Country& country1, const Country& country2)
{
	auto distanceBetweenCapitals = getDistanceBetweenCapitals(country1, country2);
	if (!distanceBetweenCapitals)
	{
		return std::nullopt;
	}

	auto distanceSquared = *distanceBetweenCapitals * *distanceBetweenCapitals;
	for (auto province1: country1.getProvinces())
	{
		auto province1Position = getProvincePosition(province1);
		if (!province1Position)
		{
			continue;
		}

		for (auto province2: country2.getProvinces())
		{
			auto province2Position = getProvincePosition(province2);
			if (!province2Position)
			{
				continue;
			}

			distanceSquared =
				 std::min(distanceSquared, getDistanceSquaredBetweenPoints(*province1Position, *province2Position));
		}
	}

	return std::sqrt(distanceSquared);
}
