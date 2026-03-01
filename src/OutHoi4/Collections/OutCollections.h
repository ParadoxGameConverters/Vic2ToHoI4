#ifndef OUT_COLLECTIONS_H
#define OUT_COLLECTIONS_H



#include "src/HOI4World/Collections/Collection.h"



namespace HoI4
{

void outputCollections(const std::filesystem::path& outputName, const std::vector<Collection>& collections);

} // namespace HoI4



#endif // OUT_COLLECTIONS_H