#include "Pop.h"
#include "Issues/Issues.h"
#include "Log.h"
#include "ParserHelpers.h"

std::map<int, Vic2::Pop*> Vic2::Pop::pop_map;

Vic2::Pop::Pop(const std::string& typeString, std::istream& theStream, const Issues& theIssues): type(typeString)
{
	registerKeyword(std::regex("size"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt sizeInt(theStream);
		size = sizeInt.getInt();
	});
	registerKeyword(std::regex("literacy"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleDouble sizeInt(theStream);
		literacy = sizeInt.getDouble();
	});
	registerKeyword(std::regex("con"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleDouble sizeInt(theStream);
		consciousness = sizeInt.getDouble();
	});
	registerKeyword(std::regex("mil"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleDouble sizeInt(theStream);
		militancy = sizeInt.getDouble();
	});
	registerKeyword(std::regex("issues"), [this, &theIssues](const std::string& unused, std::istream& theStream) {
		auto equals = getNextTokenWithoutMatching(theStream);
		auto openBrace = getNextTokenWithoutMatching(theStream);

		auto possibleIssue = getNextTokenWithoutMatching(theStream);
		while (possibleIssue != "}")
		{
			auto equalsSign = getNextTokenWithoutMatching(theStream);
			auto issueSupport = getNextTokenWithoutMatching(theStream);

			std::string issueName = theIssues.getIssueName(std::stoi(*possibleIssue));
			popIssues.insert(std::make_pair(issueName, std::stof(*issueSupport)));

			possibleIssue = getNextTokenWithoutMatching(theStream);
		}
	});
	registerKeyword(std::regex("id"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleInt idInt(theStream);
		id = idInt.getInt();
	});
	registerKeyword(std::regex("[a-z\\_]+"), [this](const std::string& cultureString, std::istream& theStream) {
		if (culture == "no_culture")
		{
			culture = cultureString;
			commonItems::singleString religionString(theStream);
			religion = religionString.getString();
		}
		else
		{
			commonItems::ignoreItem(cultureString, theStream);
		}
	});
	registerKeyword(std::regex("[A-Za-z0-9\\_]+"), commonItems::ignoreItem);

	parseStream(theStream);
	pop_map[id] = this;
}


float Vic2::Pop::getIssue(const std::string& issueName) const
{
	auto issue = popIssues.find(issueName);
	if (issue != popIssues.end())
	{
		return issue->second;
	}
	else
	{
		return 0.0f;
	}
}

Vic2::Pop* Vic2::Pop::getByID(int idx)
{
	return pop_map[idx];
}
