#ifndef OUT_LANDMARK_BUILDINGS_H
#define OUT_LANDMARK_BUILDINGS_H



#include "src/HOI4World/Landmarks/LandmarkBuildings.h"



namespace HoI4
{

void outputLandmarkBuildings(const LandmarkBuildings& landmarkBuildings, const std::filesystem::path& outputName);

std::ostream& operator<<(std::ostream& outStream, const LandmarkBuildings& outLandmarkBuildings);

} // namespace HoI4



#endif // OUT_LANDMARK_BUILDINGS_H