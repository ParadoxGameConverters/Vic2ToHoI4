#ifndef VIC2_BUILDING_READER_H
#define VIC2_BUILDING_READER_H



#include "Parser.h"



namespace Vic2
{

class BuildingReader: commonItems::parser
{
  public:
	BuildingReader();

	int getLevel(std::istream& theStream);

  private:
	int level = 0;
};

} // namespace Vic2



#endif // VIC2_BUILDING_READER_H