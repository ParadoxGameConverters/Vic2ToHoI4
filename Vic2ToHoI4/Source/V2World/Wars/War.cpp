#include "War.h"
#include "ParserHelpers.h"
#include "WarGoal.h"



Vic2::War::War(std::istream& theStream)
{
	registerKeyword("attacker", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString attackerString(theStream);
		attackers.insert(attackerString.getString());
	});
	registerKeyword("original_attacker", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString originalAttackerString(theStream);
		originalAttacker = originalAttackerString.getString();
	});
	registerKeyword("defender", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString defenderString(theStream);
		defenders.insert(defenderString.getString());
	});
	registerKeyword("original_defender", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString originalDefenderString(theStream);
		originalDefender = originalDefenderString.getString();
	});
	registerKeyword("original_wargoal", [this](const std::string& unused, std::istream& theStream) {
		Vic2::WarGoal theWarGoal(theStream);
		CB = theWarGoal.getCB();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}