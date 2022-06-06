#include "CommanderDataFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::CommanderDataFactory::CommanderDataFactory()
{
	registerKeyword("traits", [this](std::istream& input) {
		traits_ = commonItems::getStrings(input);
	});
	registerKeyword("skill", [this](std::istream& input) {
		skill_ = commonItems::getInt(input);
	});
	registerKeyword("attack_skill", [this](std::istream& input) {
		attack_skill_ = commonItems::getInt(input);
	});
	registerKeyword("defense_skill", [this](std::istream& input) {
		defense_skill_ = commonItems::getInt(input);
	});
	registerKeyword("planning_skill", [this](std::istream& input) {
		planning_skill_ = commonItems::getInt(input);
	});
	registerKeyword("logistics_skill", [this](std::istream& input) {
		logistics_skill_ = commonItems::getInt(input);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


HoI4::CommanderData HoI4::CommanderDataFactory::importCommanderData(std::string_view commanderType, std::istream& input)
{
	if (commanderType == "field_marshal")
	{
		level_ = CommanderLevel::FieldMarshal;
	}
	else
	{
		level_ = CommanderLevel::CorpsCommander;
	}

	traits_.clear();
	skill_ = 1;
	attack_skill_ = 1;
	defense_skill_ = 1;
	planning_skill_ = 1;
	logistics_skill_ = 1;

	parseStream(input);

	return CommanderData(level_, traits_, skill_, attack_skill_, defense_skill_, planning_skill_, logistics_skill_);
}