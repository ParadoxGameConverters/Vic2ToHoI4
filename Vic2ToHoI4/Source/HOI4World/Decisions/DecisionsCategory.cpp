#include "DecisionsCategory.h"
#include "CommonRegexes.h"
#include "ParserHelpers.h"



HoI4::DecisionsCategory HoI4::DecisionsCategory::Factory::getDecisionsCategory(const std::string& name,
	 std::istream& theStream)
{
	std::string icon;
	std::string picture;
	std::optional<int> priority;
	std::string allowed;
	std::string visible;
	std::string visibilityType;
	std::vector<std::pair<std::string, std::string>> extraItems;

	registerKeyword("icon", [&icon](const std::string& unused, std::istream& theStream) {
		icon = commonItems::singleString(theStream).getString();
	});
	registerKeyword("picture", [&picture](const std::string& unused, std::istream& theStream) {
		picture = commonItems::singleString(theStream).getString();
	});
	registerKeyword("priority", [&priority](const std::string& unused, std::istream& theStream) {
		priority = commonItems::singleInt(theStream).getInt();
	});
	registerKeyword("allowed", [&allowed](const std::string& unused, std::istream& theStream) {
		allowed = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("visible", [&visible](const std::string& unused, std::istream& theStream) {
		visible = commonItems::stringOfItem(theStream).getString();
	});
	registerKeyword("visibility_type", [&visibilityType](const std::string& unused, std::istream& theStream) {
		visibilityType = commonItems::stringOfItem(theStream).getString();
	});
	registerRegex(commonItems::catchallRegex, [&extraItems](const std::string& itemName, std::istream& theStream) {
		extraItems.push_back(std::make_pair(itemName, commonItems::stringOfItem(theStream).getString()));
	});

	parseStream(theStream);

	return DecisionsCategory{name,
		 std::move(icon),
		 std::move(picture),
		 priority,
		 std::move(allowed),
		 std::move(visible),
		 std::move(visibilityType),
		 std::move(extraItems)};
}