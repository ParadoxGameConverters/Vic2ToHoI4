#include "IssueCategoryHelper.h"
#include "CommonRegexes.h"
#include "IssueHelper.h"



Vic2::IssueCategoryHelper::IssueCategoryHelper(std::istream& theStream)
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