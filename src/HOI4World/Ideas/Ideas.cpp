#include "src/HOI4World/Ideas/Ideas.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/Log.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/Ideas/IdeaGroup.h"
#include "src/HOI4World/Ideas/IdeaUpdaters.h"
#include <fstream>



HoI4::Ideas::Ideas(const std::set<std::string>& majorIdeologies) noexcept
{
	Log(LogLevel::Info) << "\tImporting ideas";
	importIdeologicalIdeas(majorIdeologies);
	importGeneralIdeas();

	updateIdeas(majorIdeologies);
}


void HoI4::Ideas::importIdeologicalIdeas(const std::set<std::string>& majorIdeologies)
{
	for (const auto& ideology: majorIdeologies)
	{
		registerRegex(commonItems::catchallRegex,
			 [this, ideology](const std::string& groupName, std::istream& theStream) {
				 ideologicalIdeas[groupName].push_back(IdeaGroup(ideology, theStream));
			 });

		parseFile("Configurables/ideologicalIdeas/" + ideology + ".txt");
		clearRegisteredKeywords();
	}
}


void HoI4::Ideas::importGeneralIdeas()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& ideaGroupName, std::istream& theStream) {
		generalIdeas.emplace_back(IdeaGroup{ideaGroupName, theStream});
	});

	parseFile("Configurables/converterIdeas.txt");
	clearRegisteredKeywords();
}


void HoI4::Ideas::updateIdeas(const std::set<std::string>& majorIdeologies)
{
	Log(LogLevel::Info) << "\tUpdating ideas";

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

	foundGroup = std::find_if(generalIdeas.begin(), generalIdeas.end(), [](auto& theGroup) {
		return (theGroup.getName() == "hidden_ideas");
	});
	updateHiddenIdeas(*foundGroup, majorIdeologies);

	if (auto countryIdeas = ideologicalIdeas.find("country"); countryIdeas != ideologicalIdeas.end())
	{
		foundGroup = std::find_if(countryIdeas->second.begin(), countryIdeas->second.end(), [](auto& theGroup) {
			return (theGroup.getName() == "neutrality");
		});
		updateNeutralIdeas(*foundGroup, majorIdeologies);
	}
}