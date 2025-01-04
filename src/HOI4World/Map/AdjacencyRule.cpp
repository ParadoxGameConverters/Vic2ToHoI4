#include "src/HOI4World/Map/AdjacencyRule.h"
#include "external/common_items/CommonRegexes.h"
#include "external/common_items/ParserHelpers.h"
#include <algorithm>



HoI4::AdjacencyRule::AdjacencyRule(std::istream& theStream)
{
	registerKeyword("name", [this](std::istream& theStream) {
		name = commonItems::singleString{theStream}.getString();
	});
	registerRegex("contested|enemy|friend|neutral", [this](const std::string& rule, std::istream& theStream) {
		rules[rule] = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("required_provinces", [this](std::istream& theStream) {
		requiredProvinces = commonItems::intList{theStream}.getInts();
	});
	registerKeyword("is_disabled", [this](std::istream& theStream) {
		isDisabledStr = commonItems::stringOfItem{theStream}.getString();
	});
	registerKeyword("icon", [this](std::istream& theStream) {
		icon = commonItems::singleInt{theStream}.getInt();
	});
	registerKeyword("offset", [this](std::istream& theStream) {
		offset = commonItems::doubleList{theStream}.getDoubles();
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);

	parseStream(theStream);
	clearRegisteredKeywords();
}

void HoI4::AdjacencyRule::updateIsDisabledStr(const std::map<int, State>& states)
{
	if (!isDisabledStr)
	{
		return;
	}
	std::string placeholder = "$STATE";
	size_t pos = isDisabledStr->find(placeholder);
	if (pos == std::string::npos)
	{
		return;
	}

	// `icon` contains province ID whose state gets the disabling modifier
	const auto& stateItr = std::find_if(states.begin(), states.end(), [this](const std::pair<int, State>& state) {
		return state.second.getProvinces().contains(this->getIcon());
	});
	if (stateItr == states.end())
	{
		Log(LogLevel::Error) << "Couldn't find state for province " << icon << " to update adjacency rule " << name;
		return;
	}
	const auto& stateId = std::to_string(stateItr->first);

	isDisabledStr->replace(pos, placeholder.size(), stateId);
}

bool HoI4::AdjacencyRule::operator==(const HoI4::AdjacencyRule& other) const
{
	return name == other.name && rules == other.rules && requiredProvinces == other.requiredProvinces &&
			 isDisabledStr == other.isDisabledStr && icon == other.icon && offset == other.offset;
}