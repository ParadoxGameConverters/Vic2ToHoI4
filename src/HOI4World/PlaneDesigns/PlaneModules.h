#ifndef PLANE_MODULES_H
#define PLANE_MODULES_H



#include "external/common_items/Parser.h"



namespace HoI4
{

class PlaneModules: commonItems::parser
{
  public:
	explicit PlaneModules(std::istream& theStream);

	friend std::ostream& operator<<(std::ostream& output, const PlaneModules& theModules);

  private:
	std::map<std::string, std::string> modules;
};

} // namespace HoI4



#endif // PLANE_MODULES_H