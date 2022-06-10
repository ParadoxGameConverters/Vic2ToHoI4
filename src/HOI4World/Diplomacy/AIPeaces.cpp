#include "src/HOI4World/Diplomacy/AIPeaces.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include <fstream>



HoI4::AiPeaces::AiPeaces() noexcept
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& peaceName, std::istream& theStream) {
		thePeaces.emplace_back(AiPeace(peaceName, theStream));
	});

	parseFile("Configurables/ai_peaces.txt");
}


void HoI4::AiPeaces::updateAiPeace(const std::string_view name, const std::string& replacementEnable)
{
	auto peaceToUpdate = std::find_if(thePeaces.begin(), thePeaces.end(), [name](auto& thePeace) {
		return (thePeace.getName() == name);
	});
	if (peaceToUpdate != thePeaces.end())
	{
		peaceToUpdate->replaceEnable(replacementEnable);
	}
}