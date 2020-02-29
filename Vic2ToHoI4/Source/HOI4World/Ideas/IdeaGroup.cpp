#include "IdeaGroup.h"
#include "ParserHelpers.h"



HoI4::IdeaGroup::IdeaGroup(const std::string& ideaGroupName, std::istream& theStream):
	name(ideaGroupName)
{
	registerKeyword(std::regex("law"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString lawString(theStream);
		law = (lawString.getString() == "yes");
	});
	registerKeyword(std::regex("designer"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString designerString(theStream);
		designer = (designerString.getString() == "yes");
	});
	registerKeyword(std::regex("[a-zA-Z0-9\\_]+"), [this](const std::string& ideaName, std::istream& theStream){
		Idea newIdea(ideaName, theStream);
		ideas.push_back(newIdea);
	});

	parseStream(theStream);
}


std::optional<HoI4::Idea> HoI4::IdeaGroup::getIdea(const std::string& ideaName) const
{
	for (auto idea: ideas)
	{
		if (idea.getName() == ideaName)
		{
			return idea;
		}
	}

	return {};
}


void HoI4::IdeaGroup::replaceIdea(const Idea& newIdea)
{
	std::replace_if(
		ideas.begin(),
		ideas.end(),
		[newIdea](const Idea& theIdea){ return theIdea.getName() == newIdea.getName(); },
		newIdea
	);
}