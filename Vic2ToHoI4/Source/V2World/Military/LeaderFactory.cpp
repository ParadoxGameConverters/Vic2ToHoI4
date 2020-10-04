#include "LeaderFactory.h"
#include "Log.h"
#include "ParserHelpers.h"



Vic2::Leader::Factory::Factory()
{
	registerKeyword("name", [this](const std::string& unused, std::istream& theStream) {
		leader->name = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("type", [this](const std::string& unused, std::istream& theStream) {
		leader->type = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("personality", [this](const std::string& unused, std::istream& theStream) {
		leader->personality = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("background", [this](const std::string& unused, std::istream& theStream) {
		leader->background = commonItems::singleString{theStream}.getString();
	});
	registerKeyword("prestige", [this](const std::string& unused, std::istream& theStream) {
		leader->prestige = commonItems::singleDouble{theStream}.getDouble();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::Leader> Vic2::Leader::Factory::getLeader(std::istream& theStream)
{
	leader = std::make_unique<Leader>();
	parseStream(theStream);
	return std::move(leader);
}