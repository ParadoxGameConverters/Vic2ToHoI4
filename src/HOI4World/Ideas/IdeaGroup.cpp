#include "src/HOI4World/Ideas/IdeaGroup.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::IdeaGroup::IdeaGroup(std::string ideaGroupName, std::istream& theStream): name(std::move(ideaGroupName))
{
	registerKeyword("law", [this](std::istream& theStream) {
		const commonItems::singleString lawString(theStream);
		law = (lawString.getString() == "yes");
	});
	registerKeyword("designer", [this](std::istream& theStream) {
		const commonItems::singleString designerString(theStream);
		designer = (designerString.getString() == "yes");
	});
	registerKeyword("use_list_view", [this](std::istream& theStream) {
		const commonItems::singleString designerString(theStream);
		useListView = (designerString.getString() == "yes");
	});
	registerRegex(commonItems::catchallRegex, [this](const std::string& ideaName, std::istream& theStream) {
		const Idea newIdea(ideaName, theStream);
		ideas.push_back(newIdea);
	});

	parseStream(theStream);
	clearRegisteredKeywords();
}


std::optional<HoI4::Idea> HoI4::IdeaGroup::getIdea(const std::string& ideaName) const
{
	for (const auto& idea: ideas)
	{
		if (idea.getName() == ideaName)
		{
			return idea;
		}
	}

	return std::nullopt;
}


void HoI4::IdeaGroup::replaceIdea(const Idea& newIdea)
{
	std::replace_if(
		 ideas.begin(),
		 ideas.end(),
		 [newIdea](const Idea& theIdea) {
			 return theIdea.getName() == newIdea.getName();
		 },
		 newIdea);
}