#ifndef LANDMARKS_MAPPER_FACTORY_H
#define LANDMARKS_MAPPER_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/Mappers/Buildings/LandmarksMapper.h"
#include "src/Mappers/Buildings/LandmarksMappingFactory.h"
#include <memory>



namespace Mappers
{

class LandmarksMapper::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<LandmarksMapper> importLandmarksMapper();

  private:
	LandmarksMappingFactory landmarksMappingFactory;
	std::unique_ptr<LandmarksMapper> landmarksMapper;
};

} // namespace Mappers



#endif // LANDMARKS_MAPPER_FACTORY_H