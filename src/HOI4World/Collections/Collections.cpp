#include "src/HOI4World/Collections/Collections.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include <ranges>



HoI4::Collections::Collections()
{
	Log(LogLevel::Info) << "\tImporting collections";

	registerRegex(commonItems::catchallRegex, [this](const std::string& ideology, std::istream& theStream) {
		const Collections& ideologyCollections(theStream);
		for (const auto& collection: ideologyCollections.ideologicalCollections)
		{
			importedCollections[ideology].push_back(collection);
		}
	});
	parseFile(std::filesystem::path("Configurables") / "ideological_collections.txt");
}


HoI4::Collections::Collections(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& id, std::istream& theStream) {
		ideologicalCollections.push_back(Collection(id, theStream));
	});
	parseStream(theStream);
}


void HoI4::Collections::updateCollections(const std::set<std::string>& majorIdeologies)
{
	Log(LogLevel::Info) << "\tUpdating ideological collections";
	for (auto [ideology, collections]: importedCollections)
	{
		if (!majorIdeologies.contains(ideology))
		{
			continue;
		}

		for (auto& collection: collections)
		{
			updateAntiIdeologyControlledStatesMyContinentCollection(ideology, collection, majorIdeologies);
			ideologicalCollections.push_back(collection);
		}
	}
}


void HoI4::Collections::updateAntiIdeologyControlledStatesMyContinentCollection(const std::string& ideology,
	 Collection& collection,
	 const std::set<std::string>& majorIdeologies)
{
	std::map<std::string, std::string> ideologyAdjMap;
	ideologyAdjMap.emplace("democratic", "democratic");
	ideologyAdjMap.emplace("communism", "communist");
	ideologyAdjMap.emplace("fascism", "fascist");
	ideologyAdjMap.emplace("radical", "radical");
	ideologyAdjMap.emplace("absolutist", "absolutist");
	ideologyAdjMap.emplace("neutrality", "unaligned");

	const auto& ideologyAdj = ideologyAdjMap.at(ideology);

	if (collection.getId() == "anti_" + ideologyAdj + "_controlled_states_my_continent")
	{
		std::set<std::string> antiIdeologies;
		for (const auto& antiIdeology: majorIdeologies)
		{
			if (antiIdeology != ideology && antiIdeology != "neutrality")
			{
				antiIdeologies.emplace(antiIdeology);
			}
		}

		std::string nameStr = "COLLECTION_STATES_MY_CONTINENT_CONTROLLED";
		for (const auto& antiIdeology: antiIdeologies)
		{
			std::string uppercaseAntiIdeologyAdj = ideologyAdjMap.at(antiIdeology);
			std::ranges::transform(uppercaseAntiIdeologyAdj, uppercaseAntiIdeologyAdj.begin(), ::toupper);
			nameStr += "_" + uppercaseAntiIdeologyAdj;
		}
		collection.setName(nameStr);

		std::string operatorsStr = "= {\n";
		operatorsStr += "\t\tlimit = {\n";
		operatorsStr += "\t\t\tis_on_same_continent_as = ROOT\n";
		operatorsStr += "\t\t\tcontroller = {\n";
		operatorsStr += "\t\t\t\tOR = {\n";
		for (const auto& antiIdeology: antiIdeologies)
		{
			operatorsStr += "\t\t\t\t\thas_government = " + antiIdeology + "\n";
		}
		operatorsStr += "\t\t\t\t}\n";
		operatorsStr += "\t\t\t}\n";
		operatorsStr += "\t\t}\n";
		operatorsStr += "\t}";
		collection.setOperators(operatorsStr);
	}
}