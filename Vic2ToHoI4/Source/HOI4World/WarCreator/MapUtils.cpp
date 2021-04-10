#include "MapUtils.h"
#include <sstream>



HoI4::MapUtils::MapUtils(const World& theWorld)
{
	establishProvincePositions();
	determineProvinceOwners(theWorld);
}


std::optional<double> HoI4::MapUtils::getDistanceBetweenCountries(const Country& country1,
	 const Country& country2) const
{
	auto distanceBetweenCountries = getDistanceBetweenCapitals(country1, country2);
	std::pair<int, int> capital2Position = getCapitalPosition(country2);

	for (auto province1: country1.getProvinces())
	{
		auto province1Position = getProvincePosition(province1);
		if (auto newDistance = getDistanceBetweenPoints(province1Position, capital2Position);
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


std::optional<double> HoI4::MapUtils::getDistanceBetweenCapitals(const Country& country1, const Country& country2) const
{
	if (!bothCountriesHaveCapitals(country1, country2))
	{
		return {};
	}

	std::pair<int, int> country1Position = getCapitalPosition(country1);
	std::pair<int, int> country2Position = getCapitalPosition(country2);

	return getDistanceBetweenPoints(country1Position, country2Position);
}


bool HoI4::MapUtils::bothCountriesHaveCapitals(const Country& Country1, const Country& Country2) const
{
	return (Country1.getCapitalState()) && (Country2.getCapitalState());
}


std::pair<int, int> HoI4::MapUtils::getCapitalPosition(const Country& country) const
{
	auto capitalProvince = country.getCapitalProvince();
	if (capitalProvince)
	{
		return getProvincePosition(*capitalProvince);
	}
	else
	{
		return std::make_pair(65536, 65536);
	}
}


std::pair<int, int> HoI4::MapUtils::getProvincePosition(int provinceNum) const
{
	const auto itr = provincePositions.find(provinceNum);
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
	const std::vector<std::string> tokenizedLine = tokenizeLine(line);
	addProvincePosition(tokenizedLine);
}


void HoI4::MapUtils::addProvincePosition(const std::vector<std::string>& tokenizedLine)
{
	int province = std::stoi(tokenizedLine[0]);
	int x = std::stoi(tokenizedLine[2]);
	int y = std::stoi(tokenizedLine[4]);

	provincePositions.insert(std::make_pair(province, std::make_pair(x, y)));
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


double HoI4::MapUtils::getDistanceBetweenPoints(const std::pair<int, int>& point1,
	 const std::pair<int, int>& point2) const
{
	int xDistance = abs(point2.first - point1.first);
	if (xDistance > 2625)
	{
		xDistance = 5250 - xDistance;
	}

	int yDistance = point2.second - point1.second;

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


void HoI4::MapUtils::determineProvinceOwners(const World& theWorld)
{
	for (const auto& state: theWorld.getStates())
	{
		for (auto province: state.second.getProvinces())
		{
			std::string owner = state.second.getOwner();
			provinceToOwnerMap.insert(std::make_pair(province, owner));
		}
	}
}


std::set<int> HoI4::MapUtils::findBorderState(const Country& country,
	 const Country& neighbor,
	 const World& world,
	 const MapData& theMapData,
	 const ProvinceDefinitions& provinceDefinitions) const
{
	std::set<int> demandedStates;
	std::map<int, int> provinceToStateIdMapping = world.getProvinceToStateIDMap();
	for (const auto& leaderprov: country.getProvinces())
	{
		for (int prov: theMapData.getNeighbors(leaderprov))
		{
			if (!provinceDefinitions.isLandProvince(prov))
			{
				continue;
			}

			if (provinceToOwnerMap.contains(prov))
			{
				std::string owner = provinceToOwnerMap.find(prov)->second;
				if (owner == neighbor.getTag())
				{
					demandedStates.insert(provinceToStateIdMapping[prov]);
				}
			}
		}
	}
	return demandedStates;
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


std::vector<int> HoI4::MapUtils::sortStatesByCapitalDistance(const std::set<int>& stateList,
	 const Country& country,
	 const World& world) const
{
	std::multimap<double, int> statesWithDistance;
	std::pair<int, int> capitalCoords = getCapitalPosition(country);
	std::map<int, HoI4::State> statesMapping = world.getStates();

	for (int stateID: stateList)
	{
		if (auto state = statesMapping.find(stateID); state != statesMapping.end())
		{
			std::optional<int> provCapID = state->second.getVPLocation();
			std::pair<int, int> stateVPCoords;
			if (provCapID)
			{
				stateVPCoords = getProvincePosition(*provCapID);
			}
			else
			{
				stateVPCoords = std::make_pair(65536, 65536);
			}
			double distanceSquared =
				 pow(capitalCoords.first - stateVPCoords.first, 2) + pow(capitalCoords.second - stateVPCoords.second, 2);
			statesWithDistance.insert(std::pair<double, int>(distanceSquared, stateID));
		}
	}

	std::vector<int> sortedStates;
	for (std::pair<double, int> oneStateDistance: statesWithDistance)
	{
		sortedStates.push_back(oneStateDistance.second);
	}
	return sortedStates;
}