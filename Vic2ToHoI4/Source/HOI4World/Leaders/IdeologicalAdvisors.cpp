#include "IdeologicalAdvisors.h"
#include "Advisor.h"



HoI4::IdeologicalAdvisors::IdeologicalAdvisors() noexcept
{
	registerKeyword(std::regex("[a-z]+"), [this](const std::string& ideology, std::istream& theStream){
		Advisor newAdvisor(ideology, theStream);
		theAdvisors.insert(std::make_pair(ideology, newAdvisor));
	});

	parseFile("ideologicalAdvisors.txt");
}