#include "PartiesIssueHelper.h"
#include "ParserHelpers.h"
#include "IssueHelper.h"



Vic2::PartiesIssueHelper::PartiesIssueHelper(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& unused, std::istream& theStream) {
		for (const auto& issue: IssueHelper(theStream).takeIssues())
		{
			issues.push_back(issue);
		}
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}