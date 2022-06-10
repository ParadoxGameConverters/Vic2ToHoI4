#include "src/V2World/Diplomacy/RelationsFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



Vic2::Relations::Factory::Factory()
{
	registerKeyword("value", [this](std::istream& theStream) {
		relations->value = commonItems::singleInt{theStream}.getInt();
	});
	registerKeyword("level", [this](std::istream& theStream) {
		relations->level = static_cast<opinionLevel>(commonItems::singleInt{theStream}.getInt());
	});
	registerKeyword("military_access", [this](std::istream& theStream) {
		relations->militaryAccess = (commonItems::singleString{theStream}.getString() == "yes");
	});
	registerKeyword("last_send_diplomat", [this](std::istream& theStream) {
		relations->lastSentDiplomat = date(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("last_war", [this](std::istream& theStream) {
		relations->lastWar = date(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("truce_until", [this](std::istream& theStream) {
		relations->truceUntil = date(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("influence_value", [this](std::istream& theStream) {
		relations->influenceValue = static_cast<int>(commonItems::getDouble(theStream));
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::Relations> Vic2::Relations::Factory::getRelations(std::istream& theStream)
{
	relations = std::make_unique<Relations>();
	parseStream(theStream);
	return std::move(relations);
}