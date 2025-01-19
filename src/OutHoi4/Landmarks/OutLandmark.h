#ifndef OUT_LANDMARK_H
#define OUT_LANDMARK_H



#include "src/HOI4World/Landmarks/Landmark.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& outStream, const Landmark& outLandmark);

} // namespace HoI4



#endif // OUT_LANDMARK_H