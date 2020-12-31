#include "WarFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



Vic2::War::Factory::Factory()
{
	registerKeyword("attacker", [this](const std::string& unused, std::istream& theStream) {
		theWar->attackers.insert(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("original_attacker", [this](const std::string& unused, std::istream& theStream) {
		theWar->originalAttacker = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("defender", [this](const std::string& unused, std::istream& theStream) {
		theWar->defenders.insert(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("original_defender", [this](const std::string& unused, std::istream& theStream) {
		theWar->originalDefender = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("original_wargoal", [this](const std::string& unused, std::istream& theStream) {
		theWar->CB = warGoalFactory.getCB(theStream);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::War> Vic2::War::Factory::getWar(std::istream& theStream)
{
	theWar = std::make_unique<War>();

	parseStream(theStream);

	return std::move(theWar);
}