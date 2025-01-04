#ifndef LANDMARKS_MAPPING_H
#define LANDMARKS_MAPPING_H



namespace Mappers
{

struct LandmarksMapping
{
	int location = 0;
	bool built = false;

	std::strong_ordering operator<=>(const LandmarksMapping&) const = default;
};

} // namespace Mappers



#endif // LANDMARKS_MAPPING_H