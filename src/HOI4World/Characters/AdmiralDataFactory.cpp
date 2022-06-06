#include "AdmiralDataFactory.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"



HoI4::AdmiralDataFactory::AdmiralDataFactory()
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
	registerKeyword("maneuvering_skill", [this](std::istream& input) {
		maneuvering_skill_ = commonItems::getInt(input);
	});
	registerKeyword("coordination_skill", [this](std::istream& input) {
		coordination_skill_ = commonItems::getInt(input);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


HoI4::AdmiralData HoI4::AdmiralDataFactory::importAdmiralData(std::istream& input)
{
	traits_.clear();
	skill_ = 1;
	attack_skill_ = 1;
	defense_skill_ = 1;
	maneuvering_skill_ = 1;
	coordination_skill_ = 1;

	parseStream(input);

	return AdmiralData(traits_, skill_, attack_skill_, defense_skill_, maneuvering_skill_, coordination_skill_);
}