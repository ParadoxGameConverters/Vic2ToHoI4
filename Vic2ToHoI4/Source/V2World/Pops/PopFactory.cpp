#include "PopFactory.h"
#include "ParserHelpers.h"



Vic2::Pop::Factory::Factory(const Issues& theIssues): theIssues(theIssues)
{
	registerKeyword("size", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleInt sizeInt(theStream);
		pop->size = sizeInt.getInt();
	});
	registerKeyword("literacy", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleDouble sizeInt(theStream);
		pop->literacy = sizeInt.getDouble();
	});
	registerKeyword("con", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleDouble sizeInt(theStream);
		pop->consciousness = sizeInt.getDouble();
	});
	registerKeyword("mil", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleDouble sizeInt(theStream);
		pop->militancy = sizeInt.getDouble();
	});
	registerKeyword("issues", [this, &theIssues](const std::string& unused, std::istream& theStream) {
		auto equals = getNextTokenWithoutMatching(theStream);
		auto openBrace = getNextTokenWithoutMatching(theStream);

		auto possibleIssue = getNextTokenWithoutMatching(theStream);
		while (possibleIssue != "}")
		{
			auto equalsSign = getNextTokenWithoutMatching(theStream);
			auto issueSupport = getNextTokenWithoutMatching(theStream);

			auto issueName = theIssues.getIssueName(std::stoi(*possibleIssue));
			pop->popIssues.insert(std::make_pair(issueName, std::stof(*issueSupport)));

			possibleIssue = getNextTokenWithoutMatching(theStream);
		}
	});
	registerKeyword("id", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleInt idInt(theStream);
		pop->id = idInt.getInt();
	});
	registerRegex(commonItems::catchallRegex, [this](const std::string& cultureString, std::istream& theStream) {
		// only record the first matching item as culture & religion
		if (pop->culture == "no_culture")
		{
			pop->culture = cultureString;
			const commonItems::singleString religionString(theStream);
			pop->religion = religionString.getString();
		}
		else
		{
			commonItems::ignoreItem(cultureString, theStream);
		}
	});
}


std::unique_ptr<Vic2::Pop> Vic2::Pop::Factory::getPop(const std::string& typeString, std::istream& theStream)
{
	pop = std::make_unique<Pop>();
	pop->type = typeString;

	parseStream(theStream);

	return std::move(pop);
}