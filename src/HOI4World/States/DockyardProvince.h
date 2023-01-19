#ifndef DOCKYARD_PROVINCE_H
#define DOCKYARD_PROVINCE_H



#include "external/common_items/ConvenientParser.h"



namespace HoI4
{

class DockyardProvince: commonItems::parser
{
  public:
	explicit DockyardProvince(std::istream& theStream);

	int getDockyardsLevel() const { return dockyardsLevel; }

  private:
	int dockyardsLevel = 0;
};

} // namespace HoI4



#endif // DOCKYARD_PROVINCE_H