#include "IdeologicalAdvisors.h"
#include "Advisor.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::IdeologicalAdvisors::IdeologicalAdvisors() noexcept
{
	registerRegex("[a-z_]+", [this](const std::string& ideology, std::istream& theStream) {
		Advisor newAdvisor(ideology, theStream);
		theAdvisors.insert(std::make_pair(ideology, newAdvisor));
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseFile("ideologicalAdvisors.txt");
	clearRegisteredKeywords();
}