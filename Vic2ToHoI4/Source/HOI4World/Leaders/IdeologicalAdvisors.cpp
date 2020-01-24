#include "IdeologicalAdvisors.h"
#include "Advisor.h"
#include "ParserHelpers.h"



HoI4::IdeologicalAdvisors::IdeologicalAdvisors() noexcept
{
	registerRegex("[a-z_]+", [this](const std::string& ideology, std::istream& theStream){
		Advisor newAdvisor(ideology, theStream);
		theAdvisors.insert(std::make_pair(ideology, newAdvisor));
	});
	registerRegex("[A-Za-z0-9_]+", commonItems::ignoreItem);

	parseFile("ideologicalAdvisors.txt");
}