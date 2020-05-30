#include "PartiesIssueHelper.h"
#include "../../../../Fronter/commonItems/ParserHelpers.h"



Vic2::PartiesIssueHelper::PartiesIssueHelper(std::istream& theStream)
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& unused, std::istream& theStream) {
		const IssueHelper helper(theStream);
		issues.push_back(helper);
	});

	parseStream(theStream);
}