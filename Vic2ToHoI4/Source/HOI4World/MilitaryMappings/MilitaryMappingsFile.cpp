#include "MilitaryMappingsFile.h"
#include <fstream>



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