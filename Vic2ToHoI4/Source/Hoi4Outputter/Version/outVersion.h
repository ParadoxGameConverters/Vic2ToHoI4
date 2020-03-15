#ifndef HOI4_OUT_VERSION
#define HOI4_OUT_VERSION



#include "../../Mappers/VersionParser/VersionParser.h"
#include <ostream>



namespace mappers
{

std::ostream& operator<<(std::ostream& output, const VersionParser& versionParser);

}



#endif // HOI4_OUT_VERSION