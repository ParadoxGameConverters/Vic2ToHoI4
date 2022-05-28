#include "ArmyFactory.h"
#include "CommonRegexes.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"



Vic2::Army::Factory::Factory()
{
	registerKeyword("name", [this](std::istream& theStream) {
		army->name = commonItems::convertWin1252ToUTF8(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("location", [this](std::istream& theStream) {
		army->location = commonItems::singleInt{theStream}.getInt();
	});
	registerKeyword("regiment", [this](std::istream& theStream) {
		army->units.push_back(*unitFactory.getUnit(theStream));
	});
	registerKeyword("ship", [this](std::istream& theStream) {
		army->units.push_back(*unitFactory.getUnit(theStream));
	});
	registerKeyword("army", [this](std::istream& theStream) {
		auto tempArmy = std::move(army);
		tempArmy->transportedArmies.push_back(*getArmy(tempArmy->owner, theStream));
		army = std::move(tempArmy);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::Army> Vic2::Army::Factory::getArmy(std::string owner, std::istream& theStream)
{
	army = std::make_unique<Army>();
	army->owner = std::move(owner);
	parseStream(theStream);
	if (army->location == std::nullopt)
	{
		Log(LogLevel::Warning) << "Army or Navy " << army->name << " has no location";
	}
	return std::move(army);
}