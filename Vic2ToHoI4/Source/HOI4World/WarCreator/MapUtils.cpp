#include "MapUtils.h"
#include "HOI4World/States/HoI4State.h"
#include "Log.h"
#include <limits>
#include <ranges>
#include <sstream>



HoI4::MapUtils::MapUtils(const std::map<int, State>& theStates)
{
	establishProvincePositions();
	determineProvinceOwners(theStates);
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


std::optional<double> HoI4::MapUtils::getDistanceBetweenCapitals(const Country& country1, const Country& country2) const
{
	const auto country1Position = getCapitalPosition(country1);
	const auto country2Position = getCapitalPosition(country2);
	if (!country1Position || !country2Position)
	{
		return std::nullopt;
	}

	return getDistanceBetweenPoints(*country1Position, *country2Position);
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
	 const std::map<int, State>& states) const
{
	std::multimap<double, int> statesWithDistance;

	for (auto stateID: stateList)
	{
		if (auto state = states.find(stateID); state != states.end())
		{
			double distance = std::numeric_limits<double>::max();
			if (const auto stateCapital = state->second.getVPLocation(); stateCapital)
			{
				const auto stateCapitalLocation = getProvincePosition(*stateCapital);
				distance = pow(location.x - stateCapitalLocation.x, 2) + pow(location.y - stateCapitalLocation.y, 2);
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


std::map<std::string, std::shared_ptr<HoI4::Country>> HoI4::MapUtils::getNearbyCountries(const Country& checkingCountry,
	 const World& theWorld) const
{
	std::map<std::string, std::shared_ptr<HoI4::Country>> neighbors;

	for (const auto& countryItr: theWorld.getCountries())
	{
		auto country = countryItr.second;
		if (country->getCapitalState())
		{
			// IMPROVE
			// need to get further neighbors, as well as countries without capital in an area
			auto distance = getDistanceBetweenCapitals(checkingCountry, *country);
			if (distance && (*distance <= 500) && (country->hasProvinces()))
			{
				neighbors.insert(countryItr);
			}
		}
	}

	return neighbors;
}


std::map<std::string, std::shared_ptr<HoI4::Country>> HoI4::MapUtils::getImmediateNeighbors(
	 const Country& checkingCountry,
	 const MapData& theMapData,
	 const ProvinceDefinitions& provinceDefinitions,
	 const World& theWorld) const
{
	std::map<std::string, std::shared_ptr<HoI4::Country>> neighbors;

	for (auto province: checkingCountry.getProvinces())
	{
		for (int provinceNumber: theMapData.getNeighbors(province))
		{
			if (!provinceDefinitions.isLandProvince(province))
			{
				continue;
			}

			auto provinceToOwnerItr = provinceToOwnerMap.find(provinceNumber);
			if (provinceToOwnerItr == provinceToOwnerMap.end())
			{
				continue;
			}

			auto ownerTag = provinceToOwnerItr->second;
			if (ownerTag == checkingCountry.getTag())
			{
				continue;
			}

			auto countries = theWorld.getCountries();
			if (auto ownerCountry = countries.find(ownerTag); ownerCountry != countries.end())
			{
				neighbors.insert(std::make_pair(ownerTag, ownerCountry->second));
			}
		}
	}

	return neighbors;
}


std::map<std::string, std::shared_ptr<HoI4::Country>> HoI4::MapUtils::findCloseNeighbors(const Country& country,
	 const MapData& theMapData,
	 const ProvinceDefinitions& provinceDefinitions,
	 const World& theWorld) const
{
	std::map<std::string, std::shared_ptr<HoI4::Country>> closeNeighbors;

	for (const auto& neighbor: getNeighbors(country, theMapData, provinceDefinitions, theWorld))
	{
		if ((neighbor.second->getCapitalState()) && (neighbor.first != ""))
		{
			auto distance = getDistanceBetweenCapitals(country, *neighbor.second);
			if (distance && (*distance <= 500))
			{
				closeNeighbors.insert(neighbor);
			}
		}
	}

	return closeNeighbors;
}


std::map<std::string, std::shared_ptr<HoI4::Country>> HoI4::MapUtils::findFarNeighbors(const Country& country,
	 const MapData& theMapData,
	 const ProvinceDefinitions& provinceDefinitions,
	 const World& theWorld) const
{
	std::map<std::string, std::shared_ptr<HoI4::Country>> farNeighbors;

	for (auto neighbor: getNeighbors(country, theMapData, provinceDefinitions, theWorld))
	{
		if (neighbor.second->getCapitalState())
		{
			auto distance = getDistanceBetweenCapitals(country, *neighbor.second);
			if (distance && (*distance > 500))
			{
				farNeighbors.insert(neighbor);
			}
		}
	}

	if (farNeighbors.size() == 0) // find all nearby countries
	{
		for (const auto& otherCountry: theWorld.getCountries())
		{
			if (otherCountry.second->getCapitalState())
			{
				auto distance = getDistanceBetweenCapitals(country, *otherCountry.second);
				if (distance && (*distance <= 1000) && (otherCountry.second->hasProvinces()))
				{
					farNeighbors.insert(otherCountry);
				}
			}
		}
	}

	return farNeighbors;
}


std::map<std::string, std::shared_ptr<HoI4::Country>> HoI4::MapUtils::findCountriesWithin(int distancePx,
	 const Country& country,
	 const MapData& theMapData,
	 const World& theWorld) const
{
	std::map<std::string, std::shared_ptr<HoI4::Country>> closeNeighbors;

	for (const auto& neighbor: theWorld.getCountries())
	{
		if ((neighbor.second->getCapitalState()) && (!neighbor.first.empty()) && (neighbor.second->hasProvinces()))
		{
			const auto& distance = getDistanceBetweenCountries(country, *neighbor.second);
			if (distance && (*distance <= distancePx))
			{
				closeNeighbors.insert(neighbor);
			}
		}
	}

	return closeNeighbors;
}


std::map<double, std::shared_ptr<HoI4::Country>> HoI4::MapUtils::getGPsByDistance(const Country& country,
	 const World& theWorld) const
{
	std::map<double, std::shared_ptr<HoI4::Country>> distanceToGPMap;
	for (auto greatPower: theWorld.getGreatPowers())
	{
		auto distance = getDistanceBetweenCapitals(country, *greatPower);
		if (distance && (*distance < 1200))
		{
			distanceToGPMap.insert(std::make_pair(*distance, greatPower));
		}
	}

	return distanceToGPMap;
}


std::optional<double> HoI4::MapUtils::getDistanceBetweenCountries(const Country& country1,
	 const Country& country2) const
{
	auto distanceBetweenCountries = getDistanceBetweenCapitals(country1, country2);
	const auto capital2Position = getCapitalPosition(country2);
	if (!capital2Position)
	{
		return std::nullopt;
	}

	for (auto province1: country1.getProvinces())
	{
		auto province1Position = getProvincePosition(province1);
		if (auto newDistance = getDistanceBetweenPoints(province1Position, *capital2Position);
			 newDistance < distanceBetweenCountries)
		{
			distanceBetweenCountries = newDistance;
			for (auto province2: country2.getProvinces())
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


HoI4::Coordinate HoI4::MapUtils::getProvincePosition(int provinceNum) const
{
	const auto itr = provincePositions.find(provinceNum);
	return itr->second;
}


double HoI4::MapUtils::getDistanceBetweenPoints(const Coordinate& point1, const Coordinate& point2) const
{
	int xDistance = abs(point2.x - point1.x);
	if (xDistance > 2625)
	{
		xDistance = 5250 - xDistance;
	}

	int yDistance = point2.y - point1.y;

	return sqrt(pow(xDistance, 2) + pow(yDistance, 2));
}


std::map<std::string, std::shared_ptr<HoI4::Country>> HoI4::MapUtils::getNeighbors(const Country& checkingCountry,
	 const MapData& theMapData,
	 const ProvinceDefinitions& provinceDefinitions,
	 const World& theWorld) const
{
	std::map<std::string, std::shared_ptr<HoI4::Country>> neighbors =
		 getImmediateNeighbors(checkingCountry, theMapData, provinceDefinitions, theWorld);
	if (neighbors.size() == 0)
	{
		neighbors = getNearbyCountries(checkingCountry, theWorld);
	}

	return neighbors;
}