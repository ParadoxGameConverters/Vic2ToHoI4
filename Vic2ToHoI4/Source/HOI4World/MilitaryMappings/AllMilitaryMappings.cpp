#include "AllMilitaryMappings.h"
#include <fstream>



HoI4::allMilitaryMappings::allMilitaryMappings(std::istream& theStream)
{
	registerKeyword(std::regex("[a-zA-Z0-9]+"), [this](const std::string& mod, std::istream& theStream)
	{
		militaryMappings newMappings(mod, theStream);
		theMappings.insert(std::make_pair(mod, std::move(newMappings)));
	});

	parseStream(theStream);
}


const HoI4::militaryMappings& HoI4::allMilitaryMappings::getMilitaryMappings(const std::vector<std::string>& Vic2Mods) const
{
	for (const auto& mod: Vic2Mods)
	{
		auto mapping = theMappings.find(mod);
		if (mapping != theMappings.end())
		{
			return mapping->second;
		}
	}

	return theMappings.at("default");
}


HoI4::militaryMappingsFile::militaryMappingsFile()
{
	std::ifstream unitMappingFile("unit_mappings.txt");
	if (unitMappingFile.is_open())
	{
		theMilitaryMappings = std::make_unique<allMilitaryMappings>(unitMappingFile);
		unitMappingFile.close();
	}
	else
	{
		throw std::runtime_error{ "Could not open unit_mappings.txt" };
	}
}