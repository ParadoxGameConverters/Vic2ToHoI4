#include "PopFactory.h"
#include "CommonRegexes.h"
#include "Log.h"
#include "ParserHelpers.h"



Vic2::PopFactory::PopFactory(Issues _theIssues): theIssues(std::move(_theIssues))
{
	registerKeyword("size", [this](std::istream& theStream) {
		popOptions.size = commonItems::singleInt{theStream}.getInt();
	});
	registerKeyword("literacy", [this](std::istream& theStream) {
		popOptions.literacy = commonItems::singleDouble{theStream}.getDouble();
	});
	registerKeyword("mil", [this](std::istream& theStream) {
		popOptions.militancy = commonItems::singleDouble{theStream}.getDouble();
	});
	registerKeyword("issues", [this](std::istream& theStream) {
		for (const auto& [issue, value]: commonItems::assignments{theStream}.getAssignments())
		{
			try
			{
				auto issueName = theIssues.getIssueName(std::stoi(issue));
				popOptions.popIssues.insert(std::make_pair(issueName, std::stof(value)));
			}
			catch (...)
			{
				Log(LogLevel::Warning) << "Poorly formatted pop issue: " << issue << "=" << value;
			}
		}
	});

	registerKeyword("id", commonItems::ignoreItem);
	registerKeyword("con", commonItems::ignoreItem);

	registerRegex(commonItems::catchallRegex, [this](const std::string& cultureString, std::istream& theStream) {
		// only the first matching item is actually culture
		if (popOptions.culture == "no_culture")
		{
			popOptions.culture = cultureString;
		}
		commonItems::ignoreItem(cultureString, theStream);
	});
}


Vic2::Pop Vic2::PopFactory::getPop(const std::string& typeString, std::istream& theStream)
{
	popOptions = PopOptions();
	popOptions.type = typeString;

	parseStream(theStream);

	return Pop(popOptions);
}