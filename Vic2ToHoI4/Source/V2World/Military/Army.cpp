#include "Army.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"
#include "V2World/Pops/Pop.h"


Vic2::Army::Army(const std::string& type, std::istream& theStream): navy(type == "navy")
{
	registerKeyword("name", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString nameString(theStream);
		name = commonItems::convertWin1252ToUTF8(nameString.getString());
	});
	registerKeyword("location", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt locationInt(theStream);
		location = locationInt.getInt();
	});
	registerKeyword("regiment", [this](const std::string& unused, std::istream& theStream) {
		Unit* newRegiment = new Unit(theStream);
		regiments.push_back(newRegiment);
	});
	registerKeyword("ship", [this](const std::string& unused, std::istream& theStream) {
		Unit* newShip = new Unit(theStream);
		regiments.push_back(newShip);
	});
	registerKeyword("supplies", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleDouble suppliesDouble(theStream);
		supplies = suppliesDouble.getDouble();
	});
	registerKeyword("at_sea", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt locationInt(theStream);
		atSea = locationInt.getInt();
	});
	registerKeyword("army", [this](const std::string& type, std::istream& theStream) {
		Army transportedArmy(type, theStream);
		transportedArmies.push_back(transportedArmy);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);

	if (location == -1)
	{
		Log(LogLevel::Warning) << "Army or Navy " << name << " has no location";
	}
}