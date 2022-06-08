#include "src/HOI4World/Leaders/IdeologicalAdvisors.h"
#include "src/HOI4World/Leaders/Advisor.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::IdeologicalAdvisors::IdeologicalAdvisors() noexcept
{
	registerRegex("[a-z_]+", [this](const std::string& ideology, std::istream& theStream) {
		Advisor newAdvisor(ideology, theStream);
		theAdvisors.insert(std::make_pair(ideology, newAdvisor));
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseFile("Configurables/ideologicalAdvisors.txt");
	clearRegisteredKeywords();
}