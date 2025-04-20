#include "src/HOI4World/FocusTrees/FocusTreeFactory.h"
#include "external/common_items/OSCompatibilityLayer.h"
#include "external/common_items/ParserHelpers.h"
#include "src/HOI4World/HoI4Focus.h"



HoI4FocusTree::Factory::Factory()
{
	registerKeyword("focus_tree", [this](std::istream& theStream) {
	});
	registerKeyword("focus", [this](std::istream& theStream) {
		const auto& newFocus = std::make_shared<HoI4Focus>(theStream);
		imported_focus_tree_->focuses.push_back(newFocus);
	});
	registerRegex(commonItems::catchallRegex, commonItems::ignoreItem);
}


HoI4FocusTree HoI4FocusTree::Factory::importFocusTree(std::filesystem::path filePath)
{
	imported_focus_tree_ = std::make_unique<HoI4FocusTree>();
	parseFile(filePath);
	clearRegisteredKeywords();

	return *imported_focus_tree_;
}