#include "src/V2World/Politics/PartyFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



Vic2::Party::Factory::Factory()
{
	registerKeyword("name", [this](std::istream& theStream) {
		party->name = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("ideology", [this](std::istream& theStream) {
		party->ideology = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("economic_policy", [this](std::istream& theStream) {
		party->economicPolicy = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("trade_policy", [this](std::istream& theStream) {
		party->tradePolicy = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("religious_policy", [this](std::istream& theStream) {
		party->religiousPolicy = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("citizenship_policy", [this](std::istream& theStream) {
		party->citizenshipPolicy = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("war_policy", [this](std::istream& theStream) {
		party->warPolicy = commonItems::singleString{theStream}.getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::Party> Vic2::Party::Factory::getParty(std::istream& theStream)
{
	party = std::make_unique<Party>();
	parseStream(theStream);
	return std::move(party);
}