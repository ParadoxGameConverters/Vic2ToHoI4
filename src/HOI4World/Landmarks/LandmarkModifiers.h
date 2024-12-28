#ifndef HOI4_LANDMARK_MODIFIERS_H
#define HOI4_LANDMARK_MODIFIERS_H



#include "external/common_items/ConvenientParser.h"



namespace HoI4
{

class LandmarkModifiers: commonItems::parser
{
  public:
	LandmarkModifiers(std::istream& theStream);

  const auto& getEnabledControllers() const { return enabledControllers; }
  const auto& getModifiers() const { return modifiers; }

  private:
  std::vector<std::string> enabledControllers;
  std::string modifiers;
};

} // namespace HoI4



#endif // HOI4_LANDMARK_MODIFIERS_H