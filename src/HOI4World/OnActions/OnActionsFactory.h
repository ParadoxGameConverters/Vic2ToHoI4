#ifndef HOI4_ONACTIONS_FACTORY_H
#define HOI4_ONACTIONS_FACTORY_H



#include "external/common_items/ConvenientParser.h"
#include "src/HOI4World/OnActions/OnActions.h"



namespace HoI4
{

class OnActions::Factory: commonItems::parser
{
  public:
	Factory();

	[[nodiscard]] std::multimap<std::string, std::string> importOnActions(const std::filesystem::path& filePath);

  private:
	std::multimap<std::string, std::string> importedOnActions;
};

} // namespace HoI4



#endif // HOI4_ONACTIONS_FACTORY_H