#include "src/V2World/Issues/IssuesFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "src/Configuration.h"
#include "src/V2World/Issues/IssueCategoryHelper.h"



Vic2::Issues::Factory::Factory()
{
	parser_.registerRegex(commonItems::catchallRegex, [this](const std::string& unused, std::istream& theStream) {
		for (auto& name: IssueCategoryHelper{theStream}.takeIssues())
		{
			issues_->issueNames.push_back(name);
		}
	});
}


std::unique_ptr<Vic2::Issues> Vic2::Issues::Factory::GetIssues(const commonItems::ModFilesystem& mod_filesystem)
{
	issues_ = std::make_unique<Issues>();

	if (const auto& file = mod_filesystem.GetActualFileLocation("/common/issues.txt"); file)
	{
		parser_.parseFile(*file);
	}

	return std::move(issues_);
}