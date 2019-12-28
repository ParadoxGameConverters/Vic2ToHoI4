#include "ShipModules.h"
#include "ParserHelpers.h"



HoI4::shipModules::shipModules(std::istream& theStream)
{
	registerKeyword(std::regex("[a-zA-Z0-9_]+"), [this](const std::string& moduleSlot, std::istream& theStream){
		const commonItems::singleString module(theStream);
		modules.insert(std::make_pair(moduleSlot, module.getString()));
	});

	parseStream(theStream);
}