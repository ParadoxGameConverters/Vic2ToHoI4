#ifndef OPERATIVE_NAMES_SET_FACTORY_H
#define OPERATIVE_NAMES_SET_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/OperativeNames/OperativeNamesSet.h"
#include "src/HOI4World/OperativeNames/OperativeNamesSetDetails.h"



namespace HoI4
{

class OperativeNamesSet::Factory: commonItems::parser
{
  public:
	Factory();
	std::unique_ptr<OperativeNamesSet> getOperativeNamesSetFromFile(const std::string& filename);

  private:
	Details operativeNamesSetDetails;
	std::unique_ptr<OperativeNamesSet> operativeNamesSet;
};

} // namespace HoI4



#endif // OPERATIVE_NAMES_SET_FACTORY_H