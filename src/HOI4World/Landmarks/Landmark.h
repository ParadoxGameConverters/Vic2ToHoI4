#ifndef HOI4_LANDMARK_H
#define HOI4_LANDMARK_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/Landmarks/LandmarkModifiers.h"



namespace HoI4
{

class Landmark: commonItems::parser
{
  public:
	Landmark(const std::string& landmarkName, std::istream& theStream);

	const auto& getEnableForControllers() const { return countryModifiers->getEnableForControllers(); }
	const auto& getModifiers() const { return countryModifiers->getModifiers(); }

	[[nodiscard]] const auto& getName() { return name; }
	[[nodiscard]] const auto& getProperties() { return properties; }

	friend std::ostream& operator<<(std::ostream& outStream, const Landmark& outLandmark);

  private:
	std::string name;
	LandmarkModifiers* countryModifiers;
	std::vector<std::pair<std::string, std::string>> properties;
};

} // namespace HoI4



#endif // HOI4_LANDMARK_H