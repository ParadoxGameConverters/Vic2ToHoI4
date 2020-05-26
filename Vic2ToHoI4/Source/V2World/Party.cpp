#include "Party.h"
#include "ParserHelpers.h"



Vic2::Party::Party(std::istream& theStream)
{
	registerKeyword("name", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString nameString(theStream);
		name = nameString.getString();
	});
	registerKeyword("ideology", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString ideologyString(theStream);
		ideology = ideologyString.getString();
	});
	registerKeyword("economic_policy", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString policyString(theStream);
		economic_policy = policyString.getString();
	});
	registerKeyword("trade_policy", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString policyString(theStream);
		trade_policy = policyString.getString();
	});
	registerKeyword("religious_policy", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString policyString(theStream);
		religious_policy = policyString.getString();
	});
	registerKeyword("citizenship_policy", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString policyString(theStream);
		citizenship_policy = policyString.getString();
	});
	registerKeyword("war_policy", [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString policyString(theStream);
		warPolicy = policyString.getString();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
}


bool Vic2::operator==(const Vic2::Party& one, const Vic2::Party& other)
{
	return one.getName() == other.getName();
}


bool Vic2::operator<(const Vic2::Party& one, const Vic2::Party& other)
{
	return one.getName() < other.getName();
}