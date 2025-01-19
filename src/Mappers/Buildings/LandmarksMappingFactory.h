#ifndef LANDMARKS_MAPPING_FACTORY_H
#define LANDMARKS_MAPPING_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/Mappers/Buildings/LandmarksMapping.h"


namespace Mappers
{

class LandmarksMappingFactory: commonItems::parser
{
  public:
	LandmarksMappingFactory();
	LandmarksMapping importMapping(std::istream& theStream);

  private:
	LandmarksMapping landmarksMapping;
};

} // namespace Mappers



#endif // LANDMARKS_MAPPING_FACTORY_H