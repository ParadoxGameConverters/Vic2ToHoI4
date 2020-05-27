#include "Army.h"
#include "Log.h"
#include "OSCompatibilityLayer.h"
#include "ParserHelpers.h"
#include "Pop.h"



Vic2::Regiment::Regiment(std::istream& theStream)
{
	registerKeyword("name", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString nameString(theStream);
		name = Utils::convertWin1252ToUTF8(nameString.getString());
	});
	registerKeyword("type", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString typeString(theStream);
		type = typeString.getString();
	});
	registerKeyword("strength", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleDouble strengthDouble(theStream);
		strength = strengthDouble.getDouble();
	});
	registerKeyword("organisation", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleDouble organizationDouble(theStream);
		organization = organizationDouble.getDouble();
	});
	registerKeyword("experience", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleDouble experienceDouble(theStream);
		experience = experienceDouble.getDouble();
	});
	registerKeyword("pop", [this](const std::string& unused, std::istream& theStream) {
		commonItems::simpleObject pop_def(theStream);
		pop_id = pop_def.getValueAsInt("id");
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);

	if (type.empty())
	{
		Log(LogLevel::Warning) << "Regiment or Ship " << name << " has no type";
	}
}


bool Vic2::Regiment::isMobilised() const
{
	auto* pop = Vic2::Pop::getByID(pop_id);
	if (pop == nullptr)
	{
		return false;
	}
	if (pop->getType() == "soldiers")
	{
		return false;
	}
	return true;
}


Vic2::Army::Army(const std::string& type, std::istream& theStream): navy(type == "navy")
{
	registerKeyword("name", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString nameString(theStream);
		name = Utils::convertWin1252ToUTF8(nameString.getString());
	});
	registerKeyword("location", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt locationInt(theStream);
		location = locationInt.getInt();
	});
	registerKeyword("regiment", [this](const std::string& unused, std::istream& theStream) {
		Regiment* newRegiment = new Regiment(theStream);
		regiments.push_back(newRegiment);
	});
	registerKeyword("ship", [this](const std::string& unused, std::istream& theStream) {
		Regiment* newShip = new Regiment(theStream);
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