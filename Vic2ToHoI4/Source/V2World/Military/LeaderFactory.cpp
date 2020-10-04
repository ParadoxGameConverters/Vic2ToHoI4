#include "LeaderFactory.h"
#include "Log.h"
#include "ParserHelpers.h"
#include "StringUtils.h"



Vic2::Leader::Factory::Factory()
{
	registerKeyword("name", [this](const std::string& unused, std::istream& theStream) {
		leader->name = commonItems::remQuotes(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("type", [this](const std::string& unused, std::istream& theStream) {
		leader->type = commonItems::remQuotes(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("personality", [this](const std::string& unused, std::istream& theStream) {
		leader->personality = commonItems::remQuotes(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("background", [this](const std::string& unused, std::istream& theStream) {
		leader->background = commonItems::remQuotes(commonItems::singleString{theStream}.getString());
	});
	registerKeyword("prestige", [this](const std::string& unused, std::istream& theStream) {
		try
		{
			leader->prestige = commonItems::singleDouble{theStream}.getDouble();
		}
		catch (const std::exception& e)
		{
			LOG(LogLevel::Warning) << "Bad prestige value: " << e.what();
		}
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


std::unique_ptr<Vic2::Leader> Vic2::Leader::Factory::getLeader(std::istream& theStream)
{
	leader = std::make_unique<Leader>();
	parseStream(theStream);
	return std::move(leader);
}