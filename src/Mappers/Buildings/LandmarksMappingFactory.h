#ifndef LANDMARKS_MAPPING_FACTORY_H
#define LANDMARKS_MAPPING_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/Mappers/Buildings/LandmarksMapping.h"
#include <memory>


namespace Mappers
{

class LandmarksMappingFactory: commonItems::parser
{
  public:
	LandmarksMappingFactory();
	std::unique_ptr<LandmarksMapping> importMapping(std::istream& theStream);

  private:
	std::unique_ptr<LandmarksMapping> landmarksMapping;
};

} // namespace Mappers



#endif // LANDMARKS_MAPPING_FACTORY_H