#include "WarFactory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



Vic2::War::Factory::Factory()
{
	registerKeyword("attacker", [this](std::istream& theStream) {
		options.attackers.insert(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("original_attacker", [this](std::istream& theStream) {
		options.originalAttacker = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("defender", [this](std::istream& theStream) {
		options.defenders.insert(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("original_defender", [this](std::istream& theStream) {
		options.originalDefender = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("original_wargoal", [this](std::istream& theStream) {
		const auto warGoal = warGoalFactory.getWarGoal(theStream);
		options.casusBelli = warGoal.casusBelli;
		options.province = warGoal.province;
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


Vic2::War Vic2::War::Factory::getWar(std::istream& theStream)
{
	options.originalAttacker.clear();
	options.attackers.clear();
	options.originalDefender.clear();
	options.defenders.clear();
	options.casusBelli.clear();
	options.province.reset();

	parseStream(theStream);

	return War(options);
}