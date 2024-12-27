#ifndef HOI4_LANDMARK_MODIFIERS_H
#define HOI4_LANDMARK_MODIFIERS_H



#include "external/common_items/ConvenientParser.h"



namespace HoI4
{

class LandmarkModifiers: commonItems::parser
{
  public:
	LandmarkModifiers(std::istream& theStream);

  const auto& getEnableForControllers() const { return enableForControllers; }
  const auto& getModifiers() const { return modifiers; }

	friend std::ostream& operator<<(std::ostream& outStream, const LandmarkModifiers& outLandmarkModifiers);

  private:
  std::string enableForControllers;
  std::string modifiers;
};

} // namespace HoI4



#endif // HOI4_LANDMARK_MODIFIERS_H