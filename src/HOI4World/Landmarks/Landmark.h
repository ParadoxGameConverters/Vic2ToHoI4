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

	void setEnabledControllers(const std::vector<std::string>& tags) { countryModifiers->setEnabledControllers(tags); }

	const auto& getEnabledControllers() const { return countryModifiers->getEnabledControllers(); }
	const auto& getModifiers() const { return countryModifiers->getModifiers(); }

	[[nodiscard]] const auto& getName() { return name; }
	[[nodiscard]] const auto& getProperties() { return properties; }

	friend std::ostream& operator<<(std::ostream& outStream, const Landmark& outLandmark);

  private:
	std::string name;
	std::shared_ptr<LandmarkModifiers> countryModifiers;
	std::vector<std::pair<std::string, std::string>> properties;
};

} // namespace HoI4



#endif // HOI4_LANDMARK_H