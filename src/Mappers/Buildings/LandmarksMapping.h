#ifndef LANDMARKS_MAPPING_H
#define LANDMARKS_MAPPING_H



namespace Mappers
{

struct LandmarksMapping
{
	int location = 0;
	bool built = false;

	bool operator==(const LandmarksMapping& other) const { return location == other.location && built == other.built; }
};

} // namespace Mappers



#endif // LANDMARKS_MAPPING_H