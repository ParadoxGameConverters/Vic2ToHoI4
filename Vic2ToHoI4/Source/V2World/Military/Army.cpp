#include "Army.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"
#include "V2World/Pops/Pop.h"


Vic2::Army::Army(const std::string& type, std::istream& theStream, Unit::Factory& unitFactory)
{
	registerKeyword("name", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString nameString(theStream);
		name = commonItems::convertWin1252ToUTF8(nameString.getString());
	});
	registerKeyword("location", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt locationInt(theStream);
		location = locationInt.getInt();
	});
	registerKeyword("regiment", [this, &unitFactory](const std::string& unused, std::istream& theStream) {
		units.push_back(*unitFactory.getUnit(theStream));
	});
	registerKeyword("ship", [this, &unitFactory](const std::string& unused, std::istream& theStream) {
		units.push_back(*unitFactory.getUnit(theStream));
	});
	registerKeyword("army", [this, &unitFactory](const std::string& type, std::istream& theStream) {
		Army transportedArmy(type, theStream, unitFactory);
		transportedArmies.push_back(transportedArmy);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);

	if (location == -1)
	{
		Log(LogLevel::Warning) << "Army or Navy " << name << " has no location";
	}
}