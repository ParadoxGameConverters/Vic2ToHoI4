#include "src/HOI4World/States/StateBuildings.h"
#include "external/common_items/CommonRegexes.h"
#include "src/HOI4World/States/DockyardProvince.h"
#include "external/common_items/ParserHelpers.h"



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