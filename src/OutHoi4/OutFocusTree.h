#ifndef OUT_FOCUS_TREE_H
#define OUT_FOCUS_TREE_H



#include "src/HOI4World/HoI4FocusTree.h"



namespace HoI4
{

void outputFocusTree(const HoI4FocusTree& focusTree, const std::string& filename);
void outputSharedFocuses(const HoI4FocusTree& focusTree, const std::filesystem::path& filename);

} // namespace HoI4



#endif // OUT_FOCUS_TREE_H