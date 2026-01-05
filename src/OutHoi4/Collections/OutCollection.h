#ifndef OUTHOI4_COLLECTION_H
#define OUTHOI4_COLLECTION_H



#include "src/HOI4World/Collections/Collection.h"
#include <ostream>



namespace HoI4
{

std::ostream& operator<<(std::ostream& out, const Collection& theCollection);

} // namespace HoI4



#endif // OUTHOI4_COLLECTION_H