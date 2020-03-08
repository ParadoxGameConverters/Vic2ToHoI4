#include "ShipUpgrades.h"
#include "ParserHelpers.h"



HoI4::ShipUpgrades::ShipUpgrades(std::istream& theStream)
{
	registerRegex("[a-zA-Z0-9_]+", [this](const std::string& upgradeName, std::istream& theStream) {
		const commonItems::singleInt upgradeLevel(theStream);
		upgrades.insert(std::make_pair(upgradeName, upgradeLevel.getInt()));
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}
