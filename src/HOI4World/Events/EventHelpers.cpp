#include "src/HOI4World/Events/EventHelpers.h"



std::string HoI4::getElectionsAllowedString(const std::string& ideology)
{
	return (ideology == "democratic") ? "yes\n" : "no\n";
}