#ifndef LANDMARKS_MAPPING_H
#define LANDMARKS_MAPPING_H


#include <string>



namespace Mappers
{

struct LandmarksMapping
{
	std::string building;
	int location = 0;
	bool built = false;
};

} // namespace Mappers



#endif // LANDMARKS_MAPPING_H