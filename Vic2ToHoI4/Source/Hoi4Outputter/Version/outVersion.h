#ifndef HOI4_OUT_VERSION
#define HOI4_OUT_VERSION



#include "../../Mappers/VersionParser/VersionParser.h"
#include <ostream>



namespace HoI4
{

std::ostream& mappers::operator<<(std::ostream& output, const mappers::VersionParser& versionParser);

}



#endif // HOI4_OUT_VERSION