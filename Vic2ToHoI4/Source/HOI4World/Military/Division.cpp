#include "Division.h"
#include <iomanip>



HoI4::DivisionType::DivisionType(const std::string& _name, const std::string& _type, int _location, double _experience):
	name(_name),
	type(_type),
	location(_location),
	experience(_experience)
{
}
