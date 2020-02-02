#ifndef OUT_LEGACY_NAME_NAMES_H
#define OUT_LEGACY_NAME_NAMES_H



#include <ostream>
#include <string>



namespace HoI4
{

class NavyNames;

void outLegacyNavyNames(std::ostream& out, const NavyNames& navyNames, std::string_view tag);

}



#endif // OUT_LEGACY_NAME_NAMES_H