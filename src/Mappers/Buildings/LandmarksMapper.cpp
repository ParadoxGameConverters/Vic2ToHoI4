#include "src/Mappers/Buildings/LandmarksMapper.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include "src/Mappers/Buildings/LandmarksMappingFactory.h"



Mappers::LandmarksMapper::LandmarksMapper()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& name, std::istream& theStream) {
		mappings[name] = Mappers::LandmarksMappingFactory().importMapping(theStream);
	});
	parseFile("./Configurables/LandmarksMappings.txt");
	clearRegisteredKeywords();
}

std::set<int> Mappers::LandmarksMapper::getLocations(const std::string& landmark) const
{
	if (mappings.contains(landmark))
	{
		return mappings.at(landmark).locations;
	}

	return {};
}

bool Mappers::LandmarksMapper::getBuilt(const std::string& landmark) const
{
	if (mappings.contains(landmark))
	{
		return mappings.at(landmark).built;
	}

	return false;
}

std::string Mappers::LandmarksMapper::getDlcAllowed(const std::string& landmark) const
{
	// Hardcoding here not to expose it in configurables
	std::map<std::string, std::string> dlcMap{{"landmark_big_ben", "Gotterdammerung"},
		 {"landmark_colosseum", "Gotterdammerung"},
		 {"landmark_cristo_redentor", "Gotterdammerung"},
		 {"landmark_eiffel_tower", "Gotterdammerung"},
		 {"landmark_statue_of_liberty", "Gotterdammerung"},
		 {"landmark_kremlin", "Gotterdammerung"},
		 {"landmark_hofburg_palace", "Gotterdammerung"},
		 {"landmark_berlin_reichstag", "Gotterdammerung"},
		 {"landmark_berlin_volkshalle", "Gotterdammerung"},
		 {"landmark_taj_mahal", "Gotterdammerung"},
		 {"landmark_sadabad_complex", "Gotterdammerung"},
		 {"landmark_hagia_sophia", "Gotterdammerung"},
		 {"landmark_forbidden_city", "No Compromise, No Surrender"},
		 {"landmark_great_wall_section", "No Compromise, No Surrender"},
		 {"landmark_hakko_ichiu", "No Compromise, No Surrender"},
		 {"landmark_nanjing_presidential_palace", "No Compromise, No Surrender"},
		 {"landmark_nanjing_presidential_palace_gen", "No Compromise, No Surrender"},
		 {"landmark_nanjing_presidential_palace_prc", "No Compromise, No Surrender"},
		 {"landmark_national_diet", "No Compromise, No Surrender"},
		 {"landmark_tokyo_imperial_palace", "No Compromise, No Surrender"}};

	if (dlcMap.contains(landmark))
	{
		return "has_dlc = \"" + dlcMap.at(landmark) + "\"";
	}

	return "";
}