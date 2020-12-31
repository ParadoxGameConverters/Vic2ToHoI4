#include "StateBuildings.h"
#include "CommonRegexes.h"
#include "DockyardProvince.h"
#include "ParserHelpers.h"



HoI4::StateBuildings::StateBuildings(std::istream& theStream)
{
	registerKeyword("industrial_complex", [this](std::istream& theStream) {
		commonItems::singleInt factoryInt(theStream);
		civFactories = factoryInt.getInt();
	});
	registerKeyword("arms_factory", [this](std::istream& theStream) {
		commonItems::singleInt factoryInt(theStream);
		milFactories = factoryInt.getInt();
	});
	registerRegex(R"(\d+)", [this](const std::string& unused, std::istream& theStream) {
		HoI4::DockyardProvince province(theStream);
		dockyards += province.getDockyardsLevel();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}