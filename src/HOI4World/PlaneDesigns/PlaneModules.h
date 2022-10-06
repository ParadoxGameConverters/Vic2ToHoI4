#ifndef PLANE_MODULES_H
#define PLANE_MODULES_H



#include "external/common_items/Parser.h"



namespace HoI4
{

class PlaneModules: commonItems::parser
{
  public:
	explicit PlaneModules(std::istream& the_stream);

	friend std::ostream& operator<<(std::ostream& output, const PlaneModules& the_modules);

  private:
	std::map<std::string, std::string> modules_;
};

} // namespace HoI4



#endif // PLANE_MODULES_H