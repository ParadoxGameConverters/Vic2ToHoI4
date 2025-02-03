#ifndef HOI4_FOCUS_TREE_FACTORY_H
#define HOI4_FOCUS_TREE_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/HoI4FocusTree.h"



class HoI4FocusTree::Factory: commonItems::parser
{
  public:
	Factory();

	[[nodiscard]] HoI4FocusTree importFocusTree(std::string_view filePath);

  private:
	std::unique_ptr<HoI4FocusTree> imported_focus_tree_;
};



#endif // HOI4_FOCUS_TREE_FACTORY_H