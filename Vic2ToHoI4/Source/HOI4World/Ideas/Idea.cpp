#include "Idea.h"
#include "ParserHelpers.h"



HoI4::Idea::Idea(const std::string& ideaName, std::istream& theStream):
	name(ideaName)
{
	registerKeyword(std::regex("name"), [this](const std::string& unused, std::istream& theStream) {
		commonItems::singleString nameString(theStream);
		altName = nameString.getString();
	});
	registerKeyword(std::regex("cost"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleInt costString(theStream);
		cost = costString.getInt();
	});
	registerKeyword(std::regex("removal_cost"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleInt costString(theStream);
		removalCost = costString.getInt();
	});
	registerKeyword(std::regex("level"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleInt levelString(theStream);
		level = levelString.getInt();
	});
	registerKeyword(std::regex("allowed"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem allowedString(theStream);
		allowed = allowedString.getString();
	});
	registerKeyword(std::regex("allowed_civil_war"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem allowedString(theStream);
		allowedCivilWar = allowedString.getString();
	});
	registerKeyword(std::regex("cancel"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem cancelString(theStream);
		cancel = cancelString.getString();
	});
	registerKeyword(std::regex("available"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem availableString(theStream);
		available = availableString.getString();
	});
	registerKeyword(std::regex("ai_will_do"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem aiWillDoString(theStream);
		aiWillDo = aiWillDoString.getString();
	});
	registerKeyword(std::regex("picture"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem pictureString(theStream);
		picture = pictureString.getString();
	});
	registerKeyword(std::regex("rule"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem ruleString(theStream);
		rule = ruleString.getString();
	});
	registerKeyword(std::regex("modifier"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem modifierString(theStream);
		modifier = modifierString.getString();
	});
	registerKeyword(std::regex("research_bonus"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem researchBonusString(theStream);
		researchBonus = researchBonusString.getString();
	});
	registerKeyword(std::regex("equipment_bonus"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem bonusString(theStream);
		equipmentBonus = bonusString.getString();
	});
	registerKeyword(std::regex("traits"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem traitsString(theStream);
		traits = traitsString.getString();
	});
	registerKeyword(std::regex("on_add"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem onAddString(theStream);
		onAdd = onAddString.getString();
	});
	registerKeyword(std::regex("allowed_to_remove"), [this](const std::string& unused, std::istream& theStream){
		commonItems::stringOfItem allowedString(theStream);
		allowedToRemove = allowedString.getString();
	});
	registerKeyword(std::regex("default"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString defaultString(theStream);
		isDefault = (defaultString.getString() == "yes");
	});
	registerKeyword(std::regex("cancel_if_invalid"), [this](const std::string& unused, std::istream& theStream){
		commonItems::singleString cancelIfInvalidString(theStream);
		cancelIfInvalid = (cancelIfInvalidString.getString() == "yes");
	});

	parseStream(theStream);
}


std::ostream& HoI4::operator<<(std::ostream& outStream, const HoI4::Idea& outIdea)
{
	outStream << "		" << outIdea.name << " = {\n";
	if (!outIdea.altName.empty())
	{
		outStream << "			name = " << outIdea.altName << "\n";
	}
	if (outIdea.cost)
	{
		outStream << "			cost = " << *(outIdea.cost) << "\n";
	}
	if (outIdea.removalCost)
	{
		outStream << "			removal_cost = " << *(outIdea.removalCost) << "\n";
	}
	if (outIdea.level)
	{
		outStream << "			level = " << *(outIdea.level) << "\n";
	}
	if (!outIdea.allowed.empty())
	{
		outStream << "			allowed " << outIdea.allowed << "\n";
	}
	if (!outIdea.allowedCivilWar.empty())
	{
		outStream << "			allowed_civil_war " << outIdea.allowedCivilWar << "\n";
	}
	if (!outIdea.cancel.empty())
	{
		outStream << "			cancel " << outIdea.cancel << "\n";
	}
	if (!outIdea.available.empty())
	{
		outStream << "			available " << outIdea.available << "\n";
	}
	if (!outIdea.aiWillDo.empty())
	{
		outStream << "			ai_will_do " << outIdea.aiWillDo << "\n";
	}
	if (!outIdea.picture.empty())
	{
		outStream << "			picture " << outIdea.picture << "\n";
	}
	if (!outIdea.rule.empty())
	{
		outStream << "			rule " << outIdea.rule << "\n";
	}
	if (!outIdea.modifier.empty())
	{
		outStream << "			modifier " << outIdea.modifier << "\n";
	}
	if (!outIdea.researchBonus.empty())
	{
		outStream << "			research_bonus " << outIdea.researchBonus << "\n";
	}
	if (!outIdea.equipmentBonus.empty())
	{
		outStream << "			equipment_bonus " << outIdea.equipmentBonus << "\n";
	}
	if (!outIdea.traits.empty())
	{
		outStream << "			traits " << outIdea.traits << "\n";
	}
	if (!outIdea.onAdd.empty())
	{
		outStream << "			on_add " << outIdea.onAdd << "\n";
	}
	if (!outIdea.allowedToRemove.empty())
	{
		outStream << "			allowed_to_remove " << outIdea.allowedToRemove << "\n";
	}
	if (outIdea.isDefault)
	{
		outStream << "			default = yes\n";
	}
	if (outIdea.cancelIfInvalid)
	{
		if (*outIdea.cancelIfInvalid)
		{
			outStream << "			cancel_if_invalid = yes\n";
		}
		else
		{
			outStream << "			cancel_if_invalid = no\n";
		}
	}
	outStream << "		}\n";

	return outStream;
}