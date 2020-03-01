#include "Ideas.h"
#include "IdeaGroup.h"
#include "IdeaUpdaters.h"
#include <fstream>



HoI4::Ideas::Ideas() noexcept
{
	importIdeologicalIdeas();
	importGeneralIdeas();
}


void HoI4::Ideas::importIdeologicalIdeas()
{
	registerRegex("[a-zA-Z0-9_]+", [this](const std::string& ideology, std::istream& theStream) {
		ideologicalIdeas.insert(make_pair(ideology, IdeaGroup(ideology, theStream)));
	});

	parseFile("ideologicalIdeas.txt");
	clearRegisteredKeywords();
}


void HoI4::Ideas::importGeneralIdeas()
{
	registerRegex("[a-zA-Z0-9_]+", [this](const std::string& ideaGroupName, std::istream& theStream) {
		generalIdeas.emplace_back(IdeaGroup{ideaGroupName, theStream});
	});

	parseFile("converterIdeas.txt");
	clearRegisteredKeywords();
}


void HoI4::Ideas::updateIdeas(const std::set<std::string>& majorIdeologies)
{
	auto foundGroup = std::find_if(generalIdeas.begin(), generalIdeas.end(), [](auto& theGroup) {
		return (theGroup.getName() == "mobilization_laws");
	});
	updateMobilizationLaws(*foundGroup, majorIdeologies);

	foundGroup = std::find_if(generalIdeas.begin(), generalIdeas.end(), [](auto& theGroup) {
		return (theGroup.getName() == "economy");
	});
	updateEconomyIdeas(*foundGroup, majorIdeologies);

	foundGroup = std::find_if(generalIdeas.begin(), generalIdeas.end(), [](auto& theGroup) {
		return (theGroup.getName() == "trade_laws");
	});
	updateTradeLaws(*foundGroup, majorIdeologies);

	foundGroup = std::find_if(generalIdeas.begin(), generalIdeas.end(), [](auto& theGroup) {
		return (theGroup.getName() == "country");
	});
	updateGeneralIdeas(*foundGroup, majorIdeologies);
}