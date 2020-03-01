#include "IdeaGroup.h"
#include "ParserHelpers.h"



HoI4::IdeaGroup::IdeaGroup(std::string ideaGroupName, std::istream& theStream): name(std::move(ideaGroupName))
{
	registerKeyword("law", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString lawString(theStream);
		law = (lawString.getString() == "yes");
	});
	registerKeyword("designer", [this](const std::string& unused, std::istream& theStream) {
		const commonItems::singleString designerString(theStream);
		designer = (designerString.getString() == "yes");
	});
	registerRegex("[a-zA-Z0-9\\_]+", [this](const std::string& ideaName, std::istream& theStream) {
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