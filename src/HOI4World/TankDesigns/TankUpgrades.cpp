#include "TankUpgrades.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::TankUpgrades::TankUpgrades(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& upgradeName, std::istream& theStream) {
		const commonItems::singleInt upgradeLevel(theStream);
		upgrades.insert(std::make_pair(upgradeName, upgradeLevel.getInt()));
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}
