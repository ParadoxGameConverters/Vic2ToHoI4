#ifndef HOI4_STATES_DEFAULT_STATES_IMPORTER_H
#define HOI4_STATES_DEFAULT_STATES_IMPORTER_H



#include "DefaultState.h"
#include "external/common_items/ConvenientParser.h"
#include <filesystem>
#include <map>



namespace HoI4
{

class DefaultStatesImporter: commonItems::parser
{
  public:
	DefaultStatesImporter();

	std::map<int, DefaultState> ImportDefaultStates(const std::filesystem::path& hoi4Path);

  private:
	int num_ = 0;
	std::map<int, DefaultState> defaultStates_;
};

} // namespace HoI4



#endif // HOI4_STATES_DEFAULT_STATES_IMPORTER_H