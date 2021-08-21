#include "AIPeace.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::AiPeace::AiPeace(const std::string& theName, std::istream& theStream): name(theName)
{
	registerKeyword("enable", [this](std::istream& theStream) {
		const commonItems::stringOfItem enableString(theStream);
		enable = enableString.getString();
	});
	registerKeyword("annex_randomness", [this](std::istream& theStream) {
		const commonItems::singleInt randomnessInt(theStream);
		annexRandomness = randomnessInt.getInt();
	});
	registerKeyword("liberate_randomness", [this](std::istream& theStream) {
		const commonItems::singleInt randomnessInt(theStream);
		liberateRandomness = randomnessInt.getInt();
	});
	registerKeyword("puppet_randomness", [this](std::istream& theStream) {
		const commonItems::singleInt randomnessInt(theStream);
		puppetRandomness = randomnessInt.getInt();
	});
	registerKeyword("take_states_randomness", [this](std::istream& theStream) {
		const commonItems::singleInt randomnessInt(theStream);
		takeStatesRandomness = randomnessInt.getInt();
	});
	registerKeyword("force_government_randomness", [this](std::istream& theStream) {
		const commonItems::singleInt randomnessInt(theStream);
		forceGovernmentRandomness = randomnessInt.getInt();
	});
	registerKeyword("annex", [this](std::istream& theStream) {
		const commonItems::stringOfItem annexString(theStream);
		annex = annexString.getString();
	});
	registerKeyword("liberate", [this](std::istream& theStream) {
		const commonItems::stringOfItem liberateString(theStream);
		liberate = liberateString.getString();
	});
	registerKeyword("puppet", [this](std::istream& theStream) {
		const commonItems::stringOfItem puppetString(theStream);
		puppet = puppetString.getString();
	});
	registerKeyword("puppet_all", [this](std::istream& theStream) {
		const commonItems::stringOfItem puppetString(theStream);
		puppetAll = puppetString.getString();
	});
	registerKeyword("puppet_state", [this](std::istream& theStream) {
		const commonItems::stringOfItem puppetString(theStream);
		puppetState = puppetString.getString();
	});
	registerKeyword("take_states", [this](std::istream& theStream) {
		const commonItems::stringOfItem takeStatesString(theStream);
		takeStates = takeStatesString.getString();
	});
	registerKeyword("force_government", [this](std::istream& theStream) {
		const commonItems::stringOfItem forceGovernmentString(theStream);
		forceGovernment = forceGovernmentString.getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}