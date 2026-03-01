#include "src/HOI4World/Landmarks/LandmarkBuildings.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Log.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/Landmarks/Landmarks.h"



HoI4::LandmarkBuildings::LandmarkBuildings(const Configuration& theConfiguration)
{
	Log(LogLevel::Info) << "\tImporting landmark buildings";

	importDefaultLandmarkBuildings(theConfiguration);
}

void HoI4::LandmarkBuildings::importDefaultLandmarkBuildings(const Configuration& theConfiguration)
{
	registerKeywords();
	parseFile(theConfiguration.getHoI4Path() / "common/buildings/01_landmark_buildings.txt");
	clearRegisteredKeywords();
}

void HoI4::LandmarkBuildings::registerKeywords()
{
	registerKeyword("buildings", [this](std::istream& theStream) {
		buildings = Landmarks(theStream).getBuildings();
	});
	registerKeyword("spawn_points", [this](std::istream& theStream) {
		spawnPoints = commonItems::stringOfItem{theStream}.getString();
	});
	registerRegex("@[a-z_]+", [this](const std::string& constantName, std::istream& theStream) {
		constants[constantName] = static_cast<float>(commonItems::singleDouble{theStream}.getDouble());
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}

void HoI4::LandmarkBuildings::updateBuildings(const std::map<int, State>& states,
	 const Mappers::LandmarksMapper& landmarksMapper)
{
	std::map<std::string, std::shared_ptr<Landmark>> outBuildings;

	for (const auto& [name, landmark]: buildings)
	{
		if (const auto& mappings = landmarksMapper.getMappings(); !mappings.contains(name))
		{
			Log(LogLevel::Warning) << "No landmark mapping for " << name;
			continue;
		}

		std::set<std::string> ownerTags;
		for (int location: landmarksMapper.getLocations(name))
		{
			const auto& stateItr =
				 std::find_if(states.begin(), states.end(), [location](const std::pair<int, State>& state) {
					 return state.second.getProvinces().contains(location);
				 });
			if (stateItr == states.end())
			{
				Log(LogLevel::Warning) << "Couldn't find state for " << name << " location " << location;
				continue;
			}

			ownerTags.emplace(stateItr->second.getOwner());
		}

		if (ownerTags.empty())
		{
			continue;
		}

		std::vector<std::string> controllers(ownerTags.begin(), ownerTags.end());

		landmark->setEnabledControllers(controllers);
		outBuildings.insert({name, landmark});
	}

	buildings = std::move(outBuildings);
}