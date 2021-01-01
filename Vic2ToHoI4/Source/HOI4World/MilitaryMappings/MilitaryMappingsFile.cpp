#include "MilitaryMappingsFile.h"
#include "Log.h"
#include <fstream>



HoI4::militaryMappingsFile::militaryMappingsFile()
{
	Log(LogLevel::Info) << "\tImporting military mappings";
	std::ifstream unitMappingFile("Configurables/unit_mappings.txt");
	if (unitMappingFile.is_open())
	{
		theMilitaryMappings = std::make_unique<allMilitaryMappings>(unitMappingFile);
		unitMappingFile.close();
	}
	else
	{
		throw std::runtime_error{"Could not open Configurables/unit_mappings.txt"};
	}
}