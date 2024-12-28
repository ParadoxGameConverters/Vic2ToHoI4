#ifndef HOI4_LANDMARK_BUILDINGS_H
#define HOI4_LANDMARK_BUILDINGS_H



#include "external/common_items/ConvenientParser.h"
#include "src/Configuration.h"
#include "src/HOI4World/Landmarks/Landmark.h"
#include <map>



namespace HoI4
{

class LandmarkBuildings: commonItems::parser
{
  public:
	explicit LandmarkBuildings(const Configuration& theConfiguration);

	void importDefaultLandmarkBuildings(const Configuration& theConfiguration);
	void registerKeywords();

	[[nodiscard]] const auto& getConstants() const { return constants; }
	[[nodiscard]] const auto& getBuildings() const { return buildings; }
	[[nodiscard]] const auto& getSpawnPoints() const { return spawnPoints; }

	friend std::ostream& operator<<(std::ostream& outStream, const LandmarkBuildings& outLandmarkBuildings);

  private:
	std::map<std::string, double> constants;
	std::map<std::string, std::shared_ptr<Landmark>> buildings;
	std::string spawnPoints;
};

} // namespace HoI4



#endif // HOI4_LANDMARK_BUILDINGS_H