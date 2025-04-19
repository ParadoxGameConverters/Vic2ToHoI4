#include "src/V2World/Military/UnitFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "external/common_items/ParserHelpers.h"



Vic2::Unit::Factory::Factory()
{
	registerKeyword("name", [this](std::istream& theStream) {
		//unit->name = commonItems::convertWin1252ToUTF8(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("type", [this](std::istream& theStream) {
		unit->type = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("strength", [this](std::istream& theStream) {
		unit->strength = commonItems::singleDouble{theStream}.getDouble();
	});
	registerKeyword("organisation", [this](std::istream& theStream) {
		unit->organization = commonItems::singleDouble{theStream}.getDouble();
	});
	registerKeyword("experience", [this](std::istream& theStream) {
		unit->experience = commonItems::singleDouble{theStream}.getDouble();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::Unit> Vic2::Unit::Factory::getUnit(std::istream& theStream)
{
	unit = std::make_unique<Unit>();
	parseStream(theStream);
	if (unit->type.empty())
	{
		Log(LogLevel::Warning) << "Regiment or Ship " << unit->name << " has no type";
	}
	return std::move(unit);
}