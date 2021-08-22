#include "AIPeace.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::AiPeace::AiPeace(const std::string& theName, std::istream& theStream): name(theName)
{
	registerKeyword("enable", [this](std::istream& theStream) {
		enable = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("annex_randomness", [this](std::istream& theStream) {
		annexRandomness = commonItems::singleInt(theStream).getInt();
	});
	registerKeyword("liberate_randomness", [this](std::istream& theStream) {
		liberateRandomness = commonItems::singleInt(theStream).getInt();
	});
	registerKeyword("puppet_randomness", [this](std::istream& theStream) {
		puppetRandomness = commonItems::singleInt(theStream).getInt();
	});
	registerKeyword("take_states_randomness", [this](std::istream& theStream) {
		takeStatesRandomness = commonItems::singleInt(theStream).getInt();
	});
	registerKeyword("force_government_randomness", [this](std::istream& theStream) {
		forceGovernmentRandomness = commonItems::singleInt(theStream).getInt();
	});
	registerKeyword("annex", [this](std::istream& theStream) {
		annex = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("liberate", [this](std::istream& theStream) {
		liberate = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("puppet", [this](std::istream& theStream) {
		puppet = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("puppet_all", [this](std::istream& theStream) {
		puppetAll = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("puppet_state", [this](std::istream& theStream) {
		puppetState = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("take_states", [this](std::istream& theStream) {
		takeStates = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("force_government", [this](std::istream& theStream) {
		forceGovernment = commonItems::stringOfItem(theStream).getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}