#include "src/HOI4World/Ideas/IdeasFactory.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/Ideas/IdeaGroup.h"



HoI4::Ideas::Factory::Factory()
{
	registerRegex(commonItems::catchallRegex, [this](const std::string& ideaGroupName, std::istream& theStream) {
		importedIdeas->generalIdeas.emplace_back(IdeaGroup{ideaGroupName, theStream});
	});
}


HoI4::Ideas HoI4::Ideas::Factory::importIdeas(const std::string& filePath)
{
	importedIdeas = std::make_unique<HoI4::Ideas>();
	parseFile(filePath);
	clearRegisteredKeywords();

	return *importedIdeas;
}