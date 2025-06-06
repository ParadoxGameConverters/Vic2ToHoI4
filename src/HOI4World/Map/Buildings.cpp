#include "src/HOI4World/Map/Buildings.h"
#include "external/common_items/Log.h"
#include "src/Configuration.h"
#include "src/HOI4World/Map/CoastalProvinces.h"
#include "src/HOI4World/Map/Hoi4Building.h"
#include "src/HOI4World/States/HoI4State.h"
#include "src/HOI4World/States/HoI4States.h"
#include "src/Maps/MapData.h"
#include <fstream>



HoI4::Buildings::Buildings(const States& theStates,
	 const CoastalProvinces& theCoastalProvinces,
	 Maps::MapData& theMapData,
	 const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\tCreating buildings";

	importDefaultBuildings(theMapData, theConfiguration);
	placeBuildings(theStates, theCoastalProvinces, theMapData, theConfiguration);
}


void HoI4::Buildings::importDefaultBuildings(Maps::MapData& theMapData, const Configuration& theConfiguration)
{
	std::ifstream buildingsFile(theConfiguration.getHoI4Path() / "map/buildings.txt");
	if (!buildingsFile.is_open())
	{
		throw std::runtime_error("Could not open " + (theConfiguration.getHoI4Path() / "map/buildings.txt").string());
	}

	while (!buildingsFile.eof())
	{
		std::string line;
		getline(buildingsFile, line);
		processLine(line, theMapData);
	}
}


void HoI4::Buildings::processLine(const std::string& line, Maps::MapData& theMapData)
{
	const std::regex pattern("(.+);(.+);(.+);(.+);(.+);(.+);(.+)");
	std::smatch matches;
	if (regex_match(line, matches, pattern))
	{
		if (matches[2] == "arms_factory")
		{
			importDefaultBuilding(matches, defaultArmsFactories, theMapData);
		}
		else if (matches[2] == "industrial_complex")
		{
			importDefaultBuilding(matches, defaultIndustrialComplexes, theMapData);
		}
		else if (matches[2] == "air_base")
		{
			importDefaultBuilding(matches, defaultAirBases, theMapData);
		}
		else if (matches[2] == "naval_base_spawn")
		{
			importDefaultBuilding(matches, defaultNavalBases, theMapData);
		}
		else if (matches[2] == "bunker")
		{
			importDefaultBuilding(matches, defaultBunkers, theMapData);
		}
		else if (matches[2] == "coastal_bunker")
		{
			importDefaultBuilding(matches, defaultCoastalBunkers, theMapData);
		}
		else if (matches[2] == "dockyard")
		{
			importDefaultBuilding(matches, defaultDockyards, theMapData);
		}
		else if (matches[2] == "anti_air_building")
		{
			importDefaultBuilding(matches, defaultAntiAirs, theMapData);
		}
		else if (matches[2] == "synthetic_refinery")
		{
			importDefaultBuilding(matches, defaultSyntheticRefineries, theMapData);
		}
		else if (matches[2] == "nuclear_reactor_spawn")
		{
			importDefaultBuilding(matches, defaultNuclearReactors, theMapData);
		}
		else if (matches[2] == "supply_node")
		{
			importDefaultBuilding(matches, defaultSupplyNodes, theMapData);
		}
		else if (matches[2] == "floating_harbor")
		{
			importDefaultBuilding(matches, defaultFloatingHarbors, theMapData);
		}
		else if (matches[2] == "rocket_site_spawn")
		{
			importDefaultBuilding(matches, defaultRocketSites, theMapData);
		}
	}
}


void HoI4::Buildings::importDefaultBuilding(const std::smatch& matches,
	 defaultPositions& positions,
	 Maps::MapData& theMapData) const
{
	BuildingPosition position;
	position.xCoordinate = stof(matches[3].str());
	position.yCoordinate = stof(matches[4].str());
	position.zCoordinate = stof(matches[5].str());
	position.rotation = stof(matches[6].str());

	auto connectingSeaProvince = stoi(matches[7].str());

	if (auto province = theMapData.GetProvinceNumber(
			  {static_cast<int>(position.xCoordinate), static_cast<int>(position.zCoordinate)});
		 province)
	{
		const auto key = std::make_pair(*province, connectingSeaProvince);
		positions[key] = position;
	}
}


void HoI4::Buildings::placeBuildings(const States& theStates,
	 const CoastalProvinces& theCoastalProvinces,
	 const Maps::MapData& theMapData,
	 const Configuration& theConfiguration)
{
	const auto& provinceToStateIDMap = theStates.getProvinceToStateIDMap();
	const auto& actualCoastalProvinces = theCoastalProvinces.getCoastalProvinces();

	placeAirports(theStates, theMapData);
	placeAntiAir(theStates, theMapData);
	placeArmsFactories(theStates, theMapData);
	placeBunkers(provinceToStateIDMap, theMapData, theConfiguration);
	placeCoastalBunkers(provinceToStateIDMap, actualCoastalProvinces, theMapData, theConfiguration);
	placeDockyards(theStates, theCoastalProvinces, actualCoastalProvinces, theMapData);
	placeIndustrialComplexes(theStates, theMapData);
	placeNavalBases(provinceToStateIDMap, actualCoastalProvinces, theMapData, theConfiguration);
	placeNuclearReactors(theStates, theMapData);
	placeSyntheticRefineries(theStates, theMapData);
	placeSupplyNodes(provinceToStateIDMap, theMapData, theConfiguration);
	placeFloatingHarbors(provinceToStateIDMap, actualCoastalProvinces, theMapData, theConfiguration);
	placeRocketSites(theStates, theMapData);
}


void HoI4::Buildings::placeArmsFactories(const States& theStates, const Maps::MapData& theMapData)
{
	for (const auto& state: theStates.getStates())
	{
		auto numPlaced = 0;
		for (auto theProvince: state.second.getProvinces())
		{
			auto possibleArmsFactory = defaultArmsFactories.find(std::make_pair(theProvince, 0));
			if (possibleArmsFactory != defaultArmsFactories.end())
			{
				auto position = possibleArmsFactory->second;
				buildings.insert(std::make_pair(state.first, Building(state.first, "arms_factory", position, 0)));
				numPlaced++;

				if (numPlaced > 3)
				{
					break;
				}
			}
		}
		while (numPlaced < 6)
		{
			for (auto theProvince: state.second.getProvinces())
			{
				auto theProvincePoints = theMapData.GetProvincePoints(theProvince);
				if (theProvincePoints)
				{
					const auto centermostPoint = theProvincePoints->getCentermostPoint();
					BuildingPosition thePosition;
					thePosition.xCoordinate = centermostPoint.first;
					thePosition.yCoordinate = 11.0;
					thePosition.zCoordinate = centermostPoint.second;
					thePosition.rotation = 0;
					buildings.insert(std::make_pair(state.first, Building(state.first, "arms_factory", thePosition, 0)));
					numPlaced++;
				}
				else
				{
					Log(LogLevel::Warning) << "Province " << theProvince
												  << " did not have any points. "
													  "Arms factories not fully set in state "
												  << state.first << ".";
					break;
				}

				if (numPlaced >= 6)
				{
					break;
				}
			}
		}
	}
}


void HoI4::Buildings::placeIndustrialComplexes(const States& theStates, const Maps::MapData& theMapData)
{
	for (const auto& state: theStates.getStates())
	{
		auto numPlaced = 0;
		for (auto theProvince: state.second.getProvinces())
		{
			auto possibleIndustrialComplex = defaultIndustrialComplexes.find(std::make_pair(theProvince, 0));
			if (possibleIndustrialComplex != defaultIndustrialComplexes.end())
			{
				auto position = possibleIndustrialComplex->second;
				buildings.insert(std::make_pair(state.first, Building(state.first, "industrial_complex", position, 0)));
				numPlaced++;

				if (numPlaced > 3)
				{
					break;
				}
			}
		}
		while (numPlaced < 6)
		{
			for (auto theProvince: state.second.getProvinces())
			{
				auto theProvincePoints = theMapData.GetProvincePoints(theProvince);
				if (theProvincePoints)
				{
					const auto centermostPoint = theProvincePoints->getCentermostPoint();
					BuildingPosition thePosition;
					thePosition.xCoordinate = centermostPoint.first;
					thePosition.yCoordinate = 11.0;
					thePosition.zCoordinate = centermostPoint.second;
					thePosition.rotation = 0;
					buildings.insert(
						 std::make_pair(state.first, Building(state.first, "industrial_complex", thePosition, 0)));
					numPlaced++;
				}
				else
				{
					Log(LogLevel::Warning) << "Province " << theProvince
												  << " did not have any points. "
													  "Industrial complexes not fully set in state "
												  << state.first << ".";
					break;
				}

				if (numPlaced >= 6)
				{
					break;
				}
			}
		}
	}
}


void HoI4::Buildings::placeAirports(const States& theStates, const Maps::MapData& theMapData)
{
	for (const auto& state: theStates.getStates())
	{
		auto airportPlaced = false;
		for (auto theProvince: state.second.getProvinces())
		{
			auto possibleAirbase = defaultAirBases.find(std::make_pair(theProvince, 0));
			if (possibleAirbase != defaultAirBases.end())
			{
				auto position = possibleAirbase->second;
				buildings.insert(std::make_pair(state.first, Building(state.first, "air_base", position, 0)));
				airportPlaced = true;
				break;
			}
		}
		if (!airportPlaced)
		{
			auto theProvince = *state.second.getProvinces().begin();

			auto theProvincePoints = theMapData.GetProvincePoints(theProvince);
			if (theProvincePoints)
			{
				const auto centermostPoint = theProvincePoints->getCentermostPoint();
				BuildingPosition thePosition;
				thePosition.xCoordinate = centermostPoint.first;
				thePosition.yCoordinate = 11.0;
				thePosition.zCoordinate = centermostPoint.second;
				thePosition.rotation = 0;
				buildings.insert(std::make_pair(state.first, Building(state.first, "air_base", thePosition, 0)));
			}
			else
			{
				Log(LogLevel::Warning) << "Province " << theProvince
											  << " did not have any points. "
												  "Airport not set for state "
											  << state.first << ".";
			}
		}
	}
}


void HoI4::Buildings::placeAntiAir(const States& theStates, const Maps::MapData& theMapData)
{
	for (const auto& state: theStates.getStates())
	{
		auto numPlaced = 0;
		for (auto theProvince: state.second.getProvinces())
		{
			auto possibleAntiAir = defaultAntiAirs.find(std::make_pair(theProvince, 0));
			if (possibleAntiAir != defaultAntiAirs.end())
			{
				auto position = possibleAntiAir->second;
				buildings.insert(std::make_pair(state.first, Building(state.first, "anti_air_building", position, 0)));
				numPlaced++;

				if (numPlaced > 3)
				{
					break;
				}
			}
		}
		while (numPlaced < 3)
		{
			for (auto theProvince: state.second.getProvinces())
			{
				auto theProvincePoints = theMapData.GetProvincePoints(theProvince);
				if (theProvincePoints)
				{
					const auto centermostPoint = theProvincePoints->getCentermostPoint();
					BuildingPosition thePosition;
					thePosition.xCoordinate = centermostPoint.first;
					thePosition.yCoordinate = 11.0;
					thePosition.zCoordinate = centermostPoint.second;
					thePosition.rotation = 0;
					buildings.insert(
						 std::make_pair(state.first, Building(state.first, "anti_air_building", thePosition, 0)));
					numPlaced++;
				}
				else
				{
					Log(LogLevel::Warning) << "Province " << theProvince
												  << " did not have any points. "
													  "Anti-air not fully set in state "
												  << state.first << ".";
					break;
				}

				if (numPlaced >= 3)
				{
					break;
				}
			}
		}
	}
}


void HoI4::Buildings::placeNavalBases(const std::map<int, int>& provinceToStateIDMap,
	 const std::map<int, std::vector<int>>& actualCoastalProvinces,
	 const Maps::MapData& theMapData,
	 const Configuration& theConfiguration)
{
	for (const auto& province: actualCoastalProvinces)
	{
		auto provinceToStateMapping = provinceToStateIDMap.find(province.first);
		if (provinceToStateMapping == provinceToStateIDMap.end())
		{
			Log(LogLevel::Warning) << "Could not find state for province " << province.first << ". Naval base not set.";
			continue;
		}

		addNavalBase(provinceToStateMapping->second, province, theMapData, theConfiguration);
	}
}

void HoI4::Buildings::placeFloatingHarbors(const std::map<int, int>& provinceToStateIDMap,
	 const std::map<int, std::vector<int>>& actualCoastalProvinces,
	 const Maps::MapData& theMapData,
	 const Configuration& theConfiguration)
{
	for (const auto& province: actualCoastalProvinces)
	{
		auto provinceToStateMapping = provinceToStateIDMap.find(province.first);
		if (provinceToStateMapping == provinceToStateIDMap.end())
		{
			Log(LogLevel::Warning) << "Could not find state for province " << province.first
										  << ". Floating Harbor not set.";
			continue;
		}

		addFloatingHarbors(provinceToStateMapping->second, province, theMapData, theConfiguration);
	}
}

void HoI4::Buildings::addFloatingHarbors(int stateID,
	 const std::pair<int, std::vector<int>>& province,
	 const Maps::MapData& theMapData,
	 const Configuration& theConfiguration)
{
	BuildingPosition position;
	auto positionUnset = true;
	auto connectingSeaProvince = 0;
	for (auto seaProvince: province.second)
	{
		// floating harbors are placed on the sea and "connect" to land tiles,
		// so the adjacent sea province column is filled in with the province ID of the land the floating harbor supports
		// they are also in the state of the connected land tile for buildings.txt purposes
		auto defaultFloatingHarbor = defaultFloatingHarbors.find(std::make_pair(seaProvince, province.first));
		if (defaultFloatingHarbor != defaultFloatingHarbors.end())
		{
			position = defaultFloatingHarbor->second;
			connectingSeaProvince = province.first;
			positionUnset = false;
		}
	}

	if (positionUnset)
	{
		connectingSeaProvince = province.first;
		auto possiblePosition = theMapData.GetSpecifiedBorderCenter(province.second[0], province.first);
		if (!possiblePosition)
		{
			Log(LogLevel::Warning) << "Could not find position for province " << province.first
										  << ". Floating Harbor not set.";
			return;
		}

		position.xCoordinate = possiblePosition->first;
		position.yCoordinate = 11.0;
		position.zCoordinate = possiblePosition->second;
		position.rotation = 0.0;

		if (theConfiguration.getDebug())
		{
			Log(LogLevel::Warning) << "The Floating Harbor at province " << province.first
										  << " at "
											  "("
										  << position.xCoordinate << ", " << position.zCoordinate
										  << ") "
											  "did not have a location in default HoI4.";
		}
	}

	buildings.insert(std::make_pair(stateID, Building(stateID, "floating_harbor", position, connectingSeaProvince)));
}

void HoI4::Buildings::placeBunkers(const std::map<int, int>& provinceToStateIDMap,
	 const Maps::MapData& theMapData,
	 const Configuration& theConfiguration)
{
	for (const auto& provinceAndStateID: provinceToStateIDMap)
	{
		addBunker(provinceAndStateID.second, provinceAndStateID.first, theMapData, theConfiguration);
	}
}


void HoI4::Buildings::addNavalBase(int stateID,
	 const std::pair<int, std::vector<int>>& province,
	 const Maps::MapData& theMapData,
	 const Configuration& theConfiguration)
{
	BuildingPosition position;
	auto positionUnset = true;
	auto connectingSeaProvince = 0;
	for (auto seaProvince: province.second)
	{
		auto defaultNavalBase = defaultNavalBases.find(std::make_pair(province.first, seaProvince));
		if (defaultNavalBase != defaultNavalBases.end())
		{
			position = defaultNavalBase->second;
			connectingSeaProvince = seaProvince;
			positionUnset = false;
		}
	}

	if (positionUnset)
	{
		connectingSeaProvince = province.second[0];
		auto possiblePosition = theMapData.GetSpecifiedBorderCenter(province.first, province.second[0]);
		if (!possiblePosition)
		{
			Log(LogLevel::Warning) << "Could not find position for province " << province.first << ". Naval base not set.";
			return;
		}

		position.xCoordinate = possiblePosition->first;
		position.yCoordinate = 11.0;
		position.zCoordinate = possiblePosition->second;
		position.rotation = 0.0;

		if (theConfiguration.getDebug())
		{
			Log(LogLevel::Warning) << "The naval base from " << province.first << " to " << connectingSeaProvince
										  << " at "
											  "("
										  << position.xCoordinate << ", " << position.zCoordinate
										  << ") "
											  "did not have a location in default HoI4.";
		}
	}

	buildings.insert(std::make_pair(stateID, Building(stateID, "naval_base_spawn", position, connectingSeaProvince)));
}


void HoI4::Buildings::addBunker(int stateID,
	 int province,
	 const Maps::MapData& theMapData,
	 const Configuration& theConfiguration)
{
	BuildingPosition position;
	auto positionUnset = true;

	const auto defaultBunker = defaultBunkers.find(std::make_pair(province, 0));
	if (defaultBunker != defaultBunkers.end())
	{
		position = defaultBunker->second;
		positionUnset = false;
	}

	if (positionUnset)
	{
		auto possiblePosition = theMapData.GetAnyBorderCenter(province);
		if (!possiblePosition)
		{
			Log(LogLevel::Warning) << "Could not find position for province " << province << ". Bunker not set.";
			return;
		}

		position.xCoordinate = possiblePosition->first;
		position.yCoordinate = 11.0;
		position.zCoordinate = possiblePosition->second;
		position.rotation = 0.0;

		if (theConfiguration.getDebug())
		{
			Log(LogLevel::Warning) << "The bunker in " << province
										  << " at "
											  "("
										  << position.xCoordinate << ", " << position.zCoordinate
										  << ") "
											  "did not have a location in default HoI4.";
		}
	}

	buildings.insert(std::make_pair(stateID, Building(stateID, "bunker", position, 0)));
}


void HoI4::Buildings::placeCoastalBunkers(const std::map<int, int>& provinceToStateIDMap,
	 const std::map<int, std::vector<int>>& actualCoastalProvinces,
	 const Maps::MapData& theMapData,
	 const Configuration& theConfiguration)
{
	for (const auto& province: actualCoastalProvinces)
	{
		auto provinceToStateMapping = provinceToStateIDMap.find(province.first);
		if (provinceToStateMapping == provinceToStateIDMap.end())
		{
			Log(LogLevel::Warning) << "Could not find state for province " << province.first
										  << ". Coastal bunker not set.";
			continue;
		}

		addCoastalBunker(provinceToStateMapping->second, province, theMapData, theConfiguration);
	}
}


void HoI4::Buildings::addCoastalBunker(int stateID,
	 const std::pair<int, std::vector<int>>& province,
	 const Maps::MapData& theMapData,
	 const Configuration& theConfiguration)
{
	BuildingPosition position;
	auto positionUnset = true;

	const auto defaultBunker = defaultCoastalBunkers.find(std::make_pair(province.first, 0));
	if (defaultBunker != defaultCoastalBunkers.end())
	{
		position = defaultBunker->second;
		positionUnset = false;
	}

	if (positionUnset)
	{
		auto possiblePosition = theMapData.GetSpecifiedBorderCenter(province.first, province.second[0]);
		if (!possiblePosition)
		{
			Log(LogLevel::Warning) << "Could not find position for province " << province.first
										  << ". Coastal bunker not set.";
			return;
		}

		position.xCoordinate = possiblePosition->first;
		position.yCoordinate = 11.0;
		position.zCoordinate = possiblePosition->second;
		position.rotation = 0.0;

		if (theConfiguration.getDebug())
		{
			Log(LogLevel::Warning) << "The coastal bunker in " << province.first
										  << " at "
											  "("
										  << position.xCoordinate << ", " << position.zCoordinate
										  << ") "
											  "did not have a location in default HoI4.";
		}
	}

	buildings.insert(std::make_pair(stateID, Building(stateID, "coastal_bunker", position, 0)));
}


void HoI4::Buildings::placeDockyards(const States& theStates,
	 const CoastalProvinces& theCoastalProvinces,
	 std::map<int, std::vector<int>> actualCoastalProvinces,
	 const Maps::MapData& theMapData)
{
	for (const auto& state: theStates.getStates())
	{
		auto dockyardPlaced = false;
		for (auto theProvince: state.second.getProvinces())
		{
			auto possibleDockyard = defaultDockyards.find(std::make_pair(theProvince, 0));
			if (possibleDockyard != defaultDockyards.end())
			{
				auto position = possibleDockyard->second;
				buildings.insert(std::make_pair(state.first, Building(state.first, "dockyard", position, 0)));
				dockyardPlaced = true;
				break;
			}
		}
		if (!dockyardPlaced)
		{
			std::optional<int> theProvince;
			for (auto possibleProvince: state.second.getProvinces())
			{
				if (theCoastalProvinces.isProvinceCoastal(possibleProvince))
				{
					theProvince = possibleProvince;
					break;
				}
			}
			if (theProvince)
			{
				auto connectingSeaProvinces = actualCoastalProvinces.find(*theProvince);
				if (connectingSeaProvinces != actualCoastalProvinces.end())
				{
					auto centermostPoint =
						 theMapData.GetSpecifiedBorderCenter(*theProvince, connectingSeaProvinces->second[0]);
					if (centermostPoint)
					{
						BuildingPosition thePosition;
						thePosition.xCoordinate = centermostPoint->first;
						thePosition.yCoordinate = 11.0;
						thePosition.zCoordinate = centermostPoint->second;
						thePosition.rotation = 0;
						buildings.insert(std::make_pair(state.first, Building(state.first, "dockyard", thePosition, 0)));
					}
					else
					{
						Log(LogLevel::Warning) << "Province " << *theProvince
													  << " did not have any points. "
														  "Dockyard not set for state "
													  << state.first << ".";
					}
				}
			}
		}
	}
}


void HoI4::Buildings::placeSyntheticRefineries(const States& theStates, const Maps::MapData& theMapData)
{
	for (const auto& state: theStates.getStates())
	{
		auto refineryPlaced = false;
		for (auto theProvince: state.second.getProvinces())
		{
			auto possibleRefinery = defaultSyntheticRefineries.find(std::make_pair(theProvince, 0));
			if (possibleRefinery != defaultSyntheticRefineries.end())
			{
				auto position = possibleRefinery->second;
				buildings.insert(std::make_pair(state.first, Building(state.first, "synthetic_refinery", position, 0)));
				refineryPlaced = true;
				break;
			}
		}
		if (!refineryPlaced)
		{
			const auto theProvince = *state.second.getProvinces().begin();
			auto theProvincePoints = theMapData.GetProvincePoints(theProvince);
			if (theProvincePoints)
			{
				const auto centermostPoint = theProvincePoints->getCentermostPoint();
				BuildingPosition thePosition;
				thePosition.xCoordinate = centermostPoint.first;
				thePosition.yCoordinate = 11.0;
				thePosition.zCoordinate = centermostPoint.second;
				thePosition.rotation = 0;
				buildings.insert(std::make_pair(state.first, Building(state.first, "synthetic_refinery", thePosition, 0)));
			}
			else
			{
				Log(LogLevel::Warning) << "Province " << theProvince
											  << " did not have any points. "
												  "Synthetic refinery not set for state "
											  << state.first << ".";
			}
		}
	}
}


void HoI4::Buildings::placeNuclearReactors(const States& theStates, const Maps::MapData& theMapData)
{
	for (const auto& state: theStates.getStates())
	{
		auto reactorPlaced = false;
		for (auto theProvince: state.second.getProvinces())
		{
			auto possibleReactor = defaultNuclearReactors.find(std::make_pair(theProvince, 0));
			if (possibleReactor != defaultNuclearReactors.end())
			{
				auto position = possibleReactor->second;
				buildings.insert(std::make_pair(state.first, Building(state.first, "nuclear_reactor_spawn", position, 0)));
				reactorPlaced = true;
				break;
			}
		}
		if (!reactorPlaced)
		{
			const auto theProvince = *state.second.getProvinces().begin();
			auto theProvincePoints = theMapData.GetProvincePoints(theProvince);
			if (theProvincePoints)
			{
				const auto centermostPoint = theProvincePoints->getCentermostPoint();
				BuildingPosition thePosition;
				thePosition.xCoordinate = centermostPoint.first;
				thePosition.yCoordinate = 11.0;
				thePosition.zCoordinate = centermostPoint.second;
				thePosition.rotation = 0;
				buildings.insert(
					 std::make_pair(state.first, Building(state.first, "nuclear_reactor_spawn", thePosition, 0)));
			}
			else
			{
				Log(LogLevel::Warning) << "Province " << theProvince
											  << " did not have any points. "
												  "Nuclear reactor not set for state "
											  << state.first << ".";
			}
		}
	}
}
void HoI4::Buildings::placeSupplyNodes(const std::map<int, int>& provinceToStateIDMap,
	 const Maps::MapData& theMapData,
	 const Configuration& theConfiguration)
{
	for (const auto& provinceAndStateID: provinceToStateIDMap)
	{
		addSupplyNodes(provinceAndStateID.second, provinceAndStateID.first, theMapData, theConfiguration);
	}
}
void HoI4::Buildings::addSupplyNodes(int stateID,
	 int province,
	 const Maps::MapData& theMapData,
	 const Configuration& theConfiguration)
{
	BuildingPosition position;
	auto positionUnset = true;

	const auto defaultSupplyNode = defaultSupplyNodes.find(std::make_pair(province, 0));
	if (defaultSupplyNode != defaultSupplyNodes.end())
	{
		position = defaultSupplyNode->second;
		positionUnset = false;
	}

	if (positionUnset)
	{
		auto possiblePosition = theMapData.GetAnyBorderCenter(province);
		if (!possiblePosition)
		{
			Log(LogLevel::Warning) << "Could not find position for province " << province << ". Supply Node not set.";
			return;
		}

		position.xCoordinate = possiblePosition->first;
		position.yCoordinate = 11.0;
		position.zCoordinate = possiblePosition->second;
		position.rotation = 0.0;

		if (theConfiguration.getDebug())
		{
			Log(LogLevel::Warning) << "The Supply Node in " << province
										  << " at "
											  "("
										  << position.xCoordinate << ", " << position.zCoordinate
										  << ") "
											  "did not have a location in default HoI4.";
		}
	}

	buildings.insert(std::make_pair(stateID, Building(stateID, "supply_node", position, 0)));
}

void HoI4::Buildings::placeRocketSites(const States& theStates, const Maps::MapData& theMapData)
{
	for (const auto& state: theStates.getStates())
	{
		auto rocketSitePlaced = false;
		for (auto theProvince: state.second.getProvinces())
		{
			auto possibleRocketSite = defaultRocketSites.find(std::make_pair(theProvince, 0));
			if (possibleRocketSite != defaultRocketSites.end())
			{
				auto position = possibleRocketSite->second;
				buildings.insert(std::make_pair(state.first, Building(state.first, "rocket_site_spawn", position, 0)));
				rocketSitePlaced = true;
				break;
			}
		}
		if (!rocketSitePlaced)
		{
			const auto theProvince = *state.second.getProvinces().begin();
			auto theProvincePoints = theMapData.GetProvincePoints(theProvince);
			if (theProvincePoints)
			{
				const auto centermostPoint = theProvincePoints->getCentermostPoint();
				BuildingPosition thePosition;
				thePosition.xCoordinate = centermostPoint.first;
				thePosition.yCoordinate = 11.0;
				thePosition.zCoordinate = centermostPoint.second;
				thePosition.rotation = 0;
				buildings.insert(std::make_pair(state.first, Building(state.first, "rocket_site_spawn", thePosition, 0)));
			}
			else
			{
				Log(LogLevel::Warning) << "Province " << theProvince
											  << " did not have any points. "
												  "Rocket site not set for state "
											  << state.first << ".";
			}
		}
	}
}
