#include "StateBuildings.h"
#include "DockyardProvince.h"
#include "ParserHelpers.h"



HoI4::StateBuildings::StateBuildings(std::istream& theStream)
{
	registerKeyword(std::regex("industrial_complex"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt factoryInt(theStream);
		civFactories = factoryInt.getInt();
	});
	registerKeyword(std::regex("arms_factory"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt factoryInt(theStream);
		milFactories = factoryInt.getInt();
	});
	registerKeyword(std::regex("\\d+"), [this](const std::string& unused, std::istream& theStream) {
		HoI4::DockyardProvince province(theStream);
		dockyards += province.getDockyardsLevel();
	});
	registerKeyword(std::regex("[a-zA-Z0-9_]+"), commonItems::ignoreItem);

	parseStream(theStream);
}